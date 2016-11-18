#include "gameboycore/gpu.h"
#include "gameboycore/palette.h"
#include "gameboycore/memorymap.h"
#include "gameboycore/pixel.h"
#include "gameboycore/interrupt_provider.h"
#include "gameboycore/tilemap.h"

#include "bitutil.h"

namespace gb
{
	static constexpr auto HBLANK_CYCLES = 207;
	static constexpr auto VBLANK_CYCLES = 4560;
	static constexpr auto OAM_ACCESS_CYCLES = 83;
	static constexpr auto LCD_TRANSFER_CYCLES = 175;

	static constexpr auto LINE_CYCLES = 456;
	static constexpr auto VBLANK_LINE = 144;
	static constexpr auto LINE_MAX = 153;

	/* Private Implementation */

	class GPU::Impl
	{
	public:
		Impl(const MMU::Ptr& mmu) :
			mmu_(mmu),
			mode_(Mode::OAM),
			is_enabled_(false),
			cycles_to_next_state_(OAM_ACCESS_CYCLES),
			cycle_count_(0),
			line_(0),
			line_count_(0),
			lcdc_(mmu->get(memorymap::LCDC_REGISTER))
		{
			mmu->addWriteHandler(memorymap::LCDC_REGISTER, std::bind(&Impl::configure, this, std::placeholders::_1, std::placeholders::_2));
		}

		void update(uint8_t cycles, bool ime)
		{
			if (!is_enabled_) return;

			// increment cycle count
			cycle_count_ += cycles;

			// check if cycle time for the current state has elapsed
			if (cycle_count_ >= cycles_to_next_state_)
			{
				// reset the cycle time
				cycle_count_ -= cycles_to_next_state_;

				// transition to next LCD driver mode.
				transitionState(ime);
			}

			if (mode_ == Mode::VBLANK)
			{
				line_count_ += cycles;

				if (line_count_ >= LINE_CYCLES)
				{
					line_count_ -= LINE_CYCLES;

					line_ = (line_ + 1) % LINE_MAX;
					mmu_->write((uint8_t)line_, memorymap::LY_REGISTER);

					compareLyToLyc(ime);
					checkInterrupts(mmu_->read(memorymap::LCD_STAT_REGISTER), ime);
				}
			}
		}

		void setRenderCallback(RenderScanlineCallback callback)
		{
			render_scanline_ = callback;
		}

	private:

		void transitionState(bool ime)
		{
			// switch on the current mode and determine the next mode
			switch (mode_)
			{
			case Mode::HBLANK:
				line_ = (line_ + 1) % LINE_MAX;
				compareLyToLyc(ime);

				if (line_ >= VBLANK_LINE)
				{
					mode_ = Mode::VBLANK;
					cycles_to_next_state_ = VBLANK_CYCLES;
				}
				else
				{
					mode_ = Mode::OAM;
					cycles_to_next_state_ = OAM_ACCESS_CYCLES;
				}
				break;
			case Mode::VBLANK:
				// vblank interrupt
				mode_ = Mode::OAM;
				cycles_to_next_state_ = OAM_ACCESS_CYCLES;
				line_ = 0;
				break;
			case Mode::OAM:
				// set new cycle wait time
				mode_ = Mode::LCD;
				cycles_to_next_state_ = LCD_TRANSFER_CYCLES;
				break;
			case Mode::LCD:
				// set new cycle wait time
				mode_ = Mode::HBLANK;
				cycles_to_next_state_ = HBLANK_CYCLES;

				// compute the current scan line
				renderScanline();
				break;
			}

			// get lcd stat register
			auto stat = mmu_->read(memorymap::LCD_STAT_REGISTER);

			// update mode in register
			stat = (stat & ~(0x03)) | (static_cast<uint8_t>(mode_) & 0x03);

			checkInterrupts(stat, ime);

			// update stat register
			mmu_->write(stat, memorymap::LCD_STAT_REGISTER);

			// update LY register
			mmu_->write((uint8_t)line_, memorymap::LY_REGISTER);
		}

		void compareLyToLyc(bool ime)
		{
			auto stat = mmu_->read(memorymap::LCD_STAT_REGISTER);

			auto lyc = mmu_->read(memorymap::LYC_REGISTER);

			if ((uint8_t)line_ == lyc)
			{
				stat |= memorymap::Stat::LYCLY;
			}
			else
			{
				stat &= ~(memorymap::Stat::LYCLY);
			}
		}

		void renderScanline()
		{
			Scanline scanline;
			std::array<uint8_t, 160> color_line;
			TileMap tilemap(*mmu_.get());

			auto background_palette = Palette::get(mmu_->read(memorymap::BGP_REGISTER));

			// get lcd config
			const auto lcdc = mmu_->read(memorymap::LCDC_REGISTER);

			const auto background_enabled = IS_SET(lcdc, memorymap::LCDC::BG_DISPLAY_ON) != 0;
			const auto window_enabled = IS_SET(lcdc, memorymap::LCDC::WINDOW_ON) != 0;
			const auto sprites_enabled = IS_SET(lcdc, memorymap::LCDC::OBJ_ON) != 0;

			// get background tile line
			const auto background = tilemap.getBackground(line_);

			// get window overlay tile line
			const auto window = tilemap.getWindowOverlay(line_);
			const auto wx = mmu_->read(memorymap::WX_REGISTER);
			const auto wy = mmu_->read(memorymap::WY_REGISTER);

			// compute a scan line
			for (auto pixel_idx = 0u; pixel_idx < scanline.size(); ++pixel_idx)
			{
				auto color = 0u;

				if (window_enabled && line_ >= (int)wy && pixel_idx >= (int)(wx - 7))
					color = window[pixel_idx];
				else if (background_enabled)
					color = background[pixel_idx];
				else
					color = 0;

				color_line[pixel_idx] = color;
				scanline[pixel_idx] = background_palette[color];
			}

			if (sprites_enabled)
				tilemap.drawSprites(scanline, color_line, line_);

			// send scan line to the renderer
			if (render_scanline_ && line_ < VBLANK_LINE)
				render_scanline_(scanline, line_);
		}

		void configure(uint8_t value, uint16_t addr)
		{
			bool enable = (value & memorymap::LCDC::ENABLE) != 0;

			if (enable && !is_enabled_) 
			{
				line_ = 0;
				line_count_ = 0;
				cycle_count_ = 0;
			}

			is_enabled_ = enable;

			lcdc_ = value;
		}

		void checkInterrupts(uint8_t stat, bool ime)
		{
			InterruptProvider vblank_provider{ *mmu_.get(), InterruptProvider::Interrupt::VBLANK };
			InterruptProvider stat_provider{ *mmu_.get(), InterruptProvider::Interrupt::LCDSTAT };

			// check the lyc=ly flag
			if (stat & memorymap::Stat::LYCLY)
			{
				if (ime)
					stat_provider.set();
			}

			// check mode selection interrupts
			uint8_t mask = (1 << (3 + static_cast<uint8_t>(mode_)));

			if (stat & mask)
			{
				if (ime)
					stat_provider.set();
			}

			if (mode_ == Mode::VBLANK)
			{
				vblank_provider.set();
			}
		}

	private:
		MMU::Ptr mmu_;

		bool is_enabled_;

		Mode mode_;
		int cycles_to_next_state_;
		int cycle_count_;
		int line_;
		int line_count_;
		uint8_t& lcdc_;
		RenderScanlineCallback render_scanline_;
	};

	/* Public Implementation */

	GPU::GPU(const MMU::Ptr& mmu) :
		impl_(new Impl(mmu))
	{
	}

	GPU::~GPU()
	{
		delete impl_;
	}

	void GPU::update(uint8_t cycles, bool ime)
	{
		impl_->update(cycles, ime);
	}

	void GPU::setRenderCallback(RenderScanlineCallback callback)
	{
		impl_->setRenderCallback(callback);
	}

} // namespace gb