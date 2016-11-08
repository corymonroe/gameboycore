/**
	\author Natesh Narain <nnaraindev@gmail.com>
	\date   Nov 3 2016
*/

#ifndef GAMEBOY_NOISE_H
#define GAMEBOY_NOISE_H

#include "gameboy/mmu.h"
#include "gameboy/memorymap.h"

#include <cstdint>

namespace gb
{
	/**
		\class Noise
		\brief Generate white noise
	*/
	class Noise : public Channel
	{
	public:
		Noise(MMU::Ptr& mmu) : 
			mmu_(mmu),
			sound_length_(mmu->get(memorymap::NR41_REGISTER)),
			envelope_    (mmu->get(memorymap::NR42_REGISTER)),
			frequency_   (mmu->get(memorymap::NR43_REGISTER)),
			counter_     (mmu->get(memorymap::NR44_REGISTER))
		{
		}

		~Noise()
		{
		}

	private:
		MMU::Ptr& mmu_;

		uint8_t& sound_length_;
		uint8_t& envelope_;
		uint8_t& frequency_;
		uint8_t& counter_;
	};
}

#endif // GAMEBOY_NOISE_H
