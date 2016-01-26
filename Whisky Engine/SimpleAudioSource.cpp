#include "SimpleAudioSource.h"
#include "Source/Manager Library/AudioManager.h"
#include <iostream>

SimpleAudioSource::SimpleAudioSource(std::string audioSourceKey) : AudioSource(audioSourceKey)
{
	buffer = new sf::SoundBuffer();
	if (!buffer->loadFromFile(audioSourceKey)){
		std::cout << audioSourceKey << " couldn't be loaded." << std::endl;
		delete buffer;
	}

	AudioManager::Inst()->registerAudioSource(audioSourceKey, this);
}

SimpleAudioSource::~SimpleAudioSource()
{
}