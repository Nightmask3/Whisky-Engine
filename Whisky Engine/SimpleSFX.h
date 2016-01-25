#ifndef SIMPLE_SFX_H
#define SIMPLE_SFX_H

#include "SFX.h"
#include "SFML/Audio/Sound.hpp"

class SimpleSFX : public SFX
{
public:
	SimpleSFX(std::string sfxKey);
	~SimpleSFX();

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

	virtual void setCurrentSFXName(string newCurrentSFXName) override;

private:
	sf::Sound* mSfxPlayer_;
};

#endif

