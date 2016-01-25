#ifndef SIMPLE_AUDIO_SOURCE_H
#define SIMPLE_AUDIO_SOURCE_H

#include "AudioSource.h"
#include "SFML/Audio/SoundBuffer.hpp"

class SimpleAudioSource : public AudioSource
{
public:
	SimpleAudioSource(std::string audioSourceKey);
	~SimpleAudioSource();
	sf::SoundBuffer* getBuffer() const { return buffer; }
private:
	sf::SoundBuffer* buffer;
};

#endif
