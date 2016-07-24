
#include "gameboy/gameboy.h"

namespace gb
{
    Gameboy::Gameboy()
    {
    }

    void Gameboy::update()
    {
		cpu_.tick();
    }

    void Gameboy::loadROM(uint8_t* rom, uint32_t size)
    {
        MMU& mmu = cpu_.getMMU();
        mmu.load(rom, size);
    }

	bool Gameboy::isDone() const
	{
		return cpu_.isHalted();
	}
}
