#ifndef GAMEBOY_AUDIO_H
#define GAMEBOY_AUDIO_H

#include <SFML/Audio.hpp>

#include <gameboycore/apu.h>

#include <array>
#include <vector>

/**
	Play Audio from gameboy core
*/
class Audio : public sf::SoundStream
{
public:
	Audio() : 
		current_buffer_(0),
		default_audio_{0, 0}
	{
		initialize(gb::APU::CHANNEL_COUNT, gb::APU::SAMPLE_RATE);
	}

	~Audio()
	{
	}

	void apuCallback(int16_t left, int16_t right)
	{
		buffers_[current_buffer_].push_back(left);
		buffers_[current_buffer_].push_back(right);
	}

private:
	virtual bool onGetData(Chunk& data) override
	{
		// get current collected samples
		auto& samples = buffers_[current_buffer_];

		if (samples.size() > 0)
		{
			data.samples = &samples[0];
			data.sampleCount = samples.size();

			// move to next audio buffer
			current_buffer_ = (current_buffer_ + 1) % buffers_.size();

			// clear contents of this buffer
			buffers_[current_buffer_].clear();
		}
		else
		{
			data.samples = &default_audio_[0];
			data.sampleCount = default_audio_.size();
		}

		return true;
	}

	virtual void onSeek(sf::Time timeOffset) override
	{
		// unsupported
	}

private:
	std::array<std::vector<sf::Int16>, 2> buffers_;
	int current_buffer_;

	std::vector<sf::Int16> default_audio_;
};

#endif // GAMEBOY_AUDIO_H
