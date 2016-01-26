#ifndef SIMPLE_MUSIC_H
#define SIMPLE_MUSIC_H

#include "IMusic.h"
#include "SFML/Audio/Music.hpp"

class SimpleMusic : public IMusic
{
public:
	SimpleMusic(std::string musicName);
	~SimpleMusic();

	virtual void play() override;

	virtual void pause() override;

	virtual void stop() override;

	virtual void setVolume(float volume) override;

	virtual void setPitch(float pitch) override;

	virtual void setPosition(float x, float y, float z) override;

	virtual void setRelativeToListener(bool relative) override;

	virtual void setMinDistance(float distance) override;

	virtual void setAttenuation(float attenuation) override;

	virtual void setLoop(bool loop) override;

	virtual float getPitch() override;

	virtual bool isRelativeToListener() override;

	virtual float getMinDistance() override;

	virtual float getAttenuation() override;

	virtual bool getLoop() override;
private:
	sf::Music* music;
};

#endif
