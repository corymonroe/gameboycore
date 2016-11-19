/**
	\file memorymap.h
	\brief Constants that define the CPU memory map
	\author Natesh Narain <nnaraindev@gmail.com>
*/

#ifndef GAMEBOYCORE_MEMORYMAP_H
#define GAMEBOYCORE_MEMORYMAP_H

namespace gb{
	//! Defines values for specific locations in the Gameboy memory map
	namespace memorymap{
		enum {
			PERMANENT_ROM_BANK_START = 0x0000, ///<

			INTERRUPT_HANDLER_VBLANK = 0x0040,
			INTERRUPT_HANDLER_LCDSTAT = 0x0048,
			INTERRUPT_HANDLER_TIMER = 0x0050,
			INTERRUPT_HANDLER_SERIAL = 0x0058,
			INTERRUPT_HANDLER_JOYPAD = 0x0060,

			PROGRAM_START = 0x0100,

			NINTENDO_LOGO_START = 0x0104,
			NINTENDO_LOGO_END = 0x0133,

			GAME_TITLE_START = 0x0134,
			GAME_TITLE_END = 0x013E,

			GAME_DESTINATION_START = 0x013F,
			GAME_DESTINATION_END = 0x0142,

			COLOR_COMPATABILITY = 0x0143,

			NEW_LICENSE_START = 0x0144,
			NEW_LICENSE_END = 0x0145,

			SGB_COMPATABILITY = 0x0146,

			CART_TYPE = 0x0147,

			CART_ROM_SIZE = 0x0148,
			CART_RAM_SIZE = 0x0149,

			DETINATION_CODE = 0x014A,

			OLD_LICENSE = 0x014B,

			MASK_ROM_VERSION = 0x014C,

			COMPLEMENT_CHECKSUM = 0x014D,

			CHECKSUM_START = 0x014E,
			CHECKSUM_END = 0x014F,

			PERMANENT_ROM_BANK_END = 0x3FFF,

			SWITCHABLE_ROM_BANK_START = 0x4000,
			SWITCHABLE_ROM_BANK_END = 0x7FFF,

			CHARACTER_RAM_START = 0x8000,
			CHARACTER_RAM_END = 0x97FF,

			BG_MAP_DATA_1_START = 0x9800,
			BG_MAP_DATA_1_END = 0x9BFF,

			BG_MAP_DATA_2_START = 0x9C00,
			BG_MAP_DATA_2_END = 0x9FFF,

			CART_RAM_BANK_START = 0xA000,
			CART_RAM_BANK_END = 0xBFFF,

			WORK_RAM_BANK_0_START = 0xC000,
			WORK_RAM_BANK_0_END = 0xCFFF,

			WORK_RAM_BANK_1_START = 0xD000,
			WORK_RAM_BANK_1_END = 0xDFFF,

			OAM_START = 0xFE00,
			OAM_END = 0xFE9F,

			JOYPAD_REGISTER = 0xFF00,

			SB_REGISTER = 0xFF01,
			SC_REGISTER = 0xFF02,

			DIVIDER_LO_REGISTER = 0xFF03,
			DIVIDER_REGISER = 0xFF04,

			TIMER_COUNTER_REGISTER = 0xFF05,
			TIMER_MODULO_REGISTER = 0xFF06,
			TIMER_CONTROLLER_REGISTER = 0xFF07,

			NR10_REGISTER = 0xFF10, // Channel 1 Sweep
			NR11_REGISTER = 0xFF11, // Channel 1 Sound length/Wave Pattern
			NR12_REGISTER = 0xFF12, // Channel 1 Volume Envelop
			NR13_REGISTER = 0xFF13, // Channel 1 Frequency LOW
			NR14_REGISTER = 0xFF14, // Channel 1 Frequency HIGH

			NR20_REGISTER = 0xFF15, // UNUSED
			NR21_REGISTER = 0xFF16, // Channel 2 Sound length/Wave Pattern
			NR22_REGISTER = 0xFF17, // Channel 2 Volume Envelop
			NR23_REGISTER = 0xFF18, // Channel 2 Frequency LOW
			NR24_REGISTER = 0xFF19, // Channel 2 Frequency HIGH

			NR30_REGISTER = 0xFF1A, // Channel 3 ON/OFF
			NR31_REGISTER = 0xFF1B, // Channel 3 Sound length
			NR32_REGISTER = 0xFF1C, // Channel 3 Select Output Level
			NR33_REGISTER = 0xFF1D, // Channel 3 Frequency LOW
			NR34_REGISTER = 0xFF1E, // Channel 3 Frequency HIGH

			NR41_REGISTER = 0xFF20, // Channel 4 Sound length
			NR42_REGISTER = 0xFF21, // Channel 4 Volume Envelope
			NR43_REGISTER = 0xFF22, // Channel 4 Polynomial Counter
			NR44_REGISTER = 0xFF23, // Channel 4 Counter/consecutive selection

			NR50_REGISTER = 0xFF24, // Sound Control Register ON/OFF / Volume Control
			NR51_REGISTER = 0xFF25, // Output terminal selection
			NR52_REGISTER = 0xFF26, // Sound On/Off

			WAVE_PATTERN_RAM_START = 0xFF30,
			WAVE_PATTERN_RAM_END   = 0xFF3F,

			LCDC_REGISTER     = 0xFF40,
			LCD_STAT_REGISTER = 0xFF41,
			SCY_REGISTER      = 0xFF42,
			SCX_REGISTER      = 0xFF43,
			LY_REGISTER       = 0xFF44,
			LYC_REGISTER      = 0xFF45,

			BGP_REGISTER = 0xFF47,
			OBP0_REGISTER = 0xFF48,
			OBP1_REGISTER = 0xFF49,

			WY_REGISTER = 0xFF4A,
			WX_REGISTER = 0xFF4B,

			KEY1_REGISER            = 0xFF4D,

			DMA_REGISTER            = 0xFF46,

			HIGH_RAM_START          = 0xFF80,
			HIGH_RAM_END            = 0xFFFE,

			INTERRUPT_ENABLE        = 0xFFFF,
			INTERRUPT_FLAG          = 0xFF0F
		};

		//! LCDC Register bit masks
		enum LCDC
		{
			ENABLE                = (1 << 7), ///< LCD Controller enable
			WINDOW_CODE_AREA      = (1 << 6), ///< Window map area selection
			WINDOW_ON             = (1 << 5), ///< Window enable
			CHARACTER_DATA        = (1 << 4), ///< Character map
			BG_CODE_AREA          = (1 << 3), ///< Background map area selection
			OBJ_8x16              = (1 << 2), ///< Sprite composition mode
			OBJ_ON                = (1 << 1), ///< Sprite enable
			BG_DISPLAY_ON         = (1 << 0)  ///< Background enable
		};

		//! LCDC Status Register bit masks
		enum Stat
		{
			LYCLY = (1 << 2) ///< LY=LYC flag
		};
	}
}

#endif // GAMEBOYCORE_MEMORYMAP_H
