/**
	\file gpu.h
	\brief GPU emulation
	\author Natesh Narain <nnaraindev@gmail.com>
	\date Oct 23 2016
*/

#ifndef GAMEBOYCORE_GPU_H
#define GAMEBOYCORE_GPU_H

#include "gameboycore_api.h"
#include "gameboycore/mmu.h"
#include "gameboycore/pixel.h"

#include <memory>
#include <cstdint>
#include <functional>
#include <array>
#include <iostream>

namespace gb
{
	/**
		\class GPU
		\brief Handle LCD state, compute scanlines and send to an external renderer
		\ingroup API
	*/
	class GAMEBOYCORE_API GPU
	{
	public:
		//! Smart pointer type
		using Ptr = std::unique_ptr<GPU>;

		//! Array on Pixel objects representing a single scan line produced by the GPU
		using Scanline               = std::array<Pixel, 160>;
		/**
			Callback function called by the GPU when it has produced a new scan line
			Provides the Scanline and the line number
		*/
		using RenderScanlineCallback = std::function<void(const Scanline&, int linenum)>;

	public:
		GPU(MMU::Ptr& mmu);
		~GPU();

		/**
			Update the GPU with elasped cycles. Used by the CPU
		*/
		void update(uint8_t cycles, bool ime);
		/**
			Set the host system callback
		*/
		void setRenderCallback(RenderScanlineCallback callback);

	private:
		//! Private Implementation class
		class Impl;
		Impl* impl_;
	};
}

#endif
