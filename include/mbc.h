

#ifndef MBC
#define MBC

/**
	Supporting MBC1 through MBC5 with external RAM 
*/

#define ROM_ONLY            0x00
#define MBC1                0x01
#define MBC1_RAM            0x02
#define MBC1_RAM_BAT        0x03
#define MBC2                0x05
#define MBC2_BAT            0x06
#define ROM_RAM             0x08
#define ROM_RAM_BAT         0x09
#define MMM01               0x0B
#define MMM01_RAM           0x0C
#define MMM01_RAM_BAT       0x0D
#define MBC3_TIME_BAT       0x0F
#define MBC3_TIME_RAM_BAT   0x10
#define MBC3                0x11
#define MBC3_RAM            0x12
#define MBC3_RAM_BAT        0x13
#define MBC4                0x15
#define MBC4_RAM            0x16
#define MBC4_RAM_BAT        0x17
#define MBC5                0x19
#define MBC5_RAM            0x1A
#define MBC5_RAM_BAT        0x1B
#define MBC5_RUMBLE         0x1C
#define MBC5_RUMBLE_RAM     0x1D
#define MBC5_RUMBLE_RAM_BAT 0x1E

//! Memory Bank Controller
typedef struct{
	uint8_t cartType;
	size_t nBanks;
	uint8_t** banks;
	int currentBank;
}GBMemoryBankController;

void initMBC(GBMemoryBankController*);

#endif
