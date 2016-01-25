#include "AudioSource.h"

AudioSource::AudioSource(std::string audioSource) :mAudioSource_(audioSource){}

void AudioSource::setAudioSource(std::string audioSource)
{
	mAudioSource_ = audioSource;
}
