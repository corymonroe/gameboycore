
/**
	@author Natesh Narain <nnaraindev@gmail.com>
*/


#ifndef GAMEBOY_DISPLAY_H
#define GAMEBOY_DISPLAY_H

#include "gameboy/mmu.h"
#include "gameboy/tile.h"
#include "gameboy/sprite.h"
#include "gameboy/lcd_controller.h"

#include <cstdint>
#include <vector>
#include <array>

namespace gb
{
	/**
		\brief Class that knows how to read Tile RAM in the Gameboy memory map
	*/
	class TileRAM
	{
	public:
		static const unsigned int NUM_TILES = 192;
		static const unsigned int TILE_SIZE = 16;

		using TileRow  = std::array<uint8_t, 8>;
		using TileLine = std::array<TileRow, 20>;

	public:
		// TODO: remove this constructor
		TileRAM(MMU& mmu);
		~TileRAM();

		Tile getTile(uint8_t tilenum) const;
		Tile getSpriteTile(const Sprite& sprite) const;
		std::vector<Tile> getTiles();

		TileRow getRow(uint8_t tilenum, bool umode);

		template<typename T>
		uint16_t getTileAddress(int32_t base_addr, uint8_t tilenum) const
		{
			return (uint16_t)(base_addr + ((T)tilenum * TILE_SIZE));
		}

	private:
		void setRow(Tile& tile, uint8_t msb, uint8_t lsb, int row) const;

		Tile flipV(const Tile& old) const;
		Tile flipH(const Tile& old) const;

	private:
		uint8_t* tile_ram_;
		MMU& mmu_;
	};

}

#endif // GAMEBOY_DISPLAY_H
