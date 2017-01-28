/**
	\file apu.h
	\brief Audio Emulation
	\author Natesh Narain <nnaraindev@gmail.com>
	\date Nov 3 2016
	\defgroup Audio
*/


#ifndef GAMEBOYCORE_APU_H
#define GAMEBOYCORE_APU_H

#include "gameboycore/gameboycore_api.h"
#include "gameboycore/mmu.h"

#include <memory>
#include <functional>

namespace gb
{
	/**
		\class APU
		\brief Emulate Gameboy sound functions
		\ingroup API
		\ingroup Audio
	*/
	class GAMEBOYCORE_API APU
	{
	public:
		enum
		{
			CHANNEL_COUNT = 2,   ///< Number of audio channels the APU provides (Stereo sound: left, right)
			SAMPLE_RATE = 44100  ///< Audio sample rate
		};
	public:
		//! Smart pointer type
		typedef std::unique_ptr<APU> Ptr;
		//! Callback used to provide audio to the host system
		typedef std::function<void(uint16_t, uint16_t)> AudioSampleCallback;

	public:

		APU(MMU::Ptr& mmu);
		APU(const APU&) = delete;
		~APU();

		/**
			Update APU with the elasped cycles. For use by the CPU
		*/
		void update(uint8_t cycles);
		/**
			Set the host callback
		*/
		void setAudioSampleCallback(AudioSampleCallback callback);

	private:
		class Impl;
		Impl* impl_;
	};
}

#endif
