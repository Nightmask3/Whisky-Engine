#ifndef AUDIO_SOURCE_H
#define AUDIO_SOURCE_H

#include <string>

class AudioSource
{
public:
	AudioSource(std::string audioSource);
	virtual void setAudioSource(std::string audioSource);
	virtual ~AudioSource(){};
private:
	std::string mAudioSource_;
};

#endif

