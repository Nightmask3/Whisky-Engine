#include "SimpleSFX.h"
#include "Source/Manager Library/AudioManager.h"
#include "SimpleAudioSource.h"
#include <iostream>

SimpleSFX::SimpleSFX(std::string sfxKey) : SFX(sfxKey)
{
	mSfxPlayer_ = new sf::Sound();
	setCurrentSFXName(sfxKey);
}

SimpleSFX::~SimpleSFX()
{
	//will be handled at AudioManager
}

void SimpleSFX::play()
{
	//TODO add setPosition here with the parameters taken from owner->transform component if isRelativeToListener
	mSfxPlayer_->play();
}

void SimpleSFX::pause()
{
	mSfxPlayer_->pause();
}

void SimpleSFX::stop()
{
	mSfxPlayer_->stop();
}

void SimpleSFX::setVolume(float volume)
{
	mSfxPlayer_->setVolume(volume);
}

void SimpleSFX::setPitch(float pitch)
{
	mSfxPlayer_->setPitch(pitch);
}

void SimpleSFX::setPosition(float x, float y, float z)
{
	mSfxPlayer_->setPosition(x, y, z);
}

void SimpleSFX::setRelativeToListener(bool relative)
{
	mSfxPlayer_->setRelativeToListener(relative);
}

void SimpleSFX::setMinDistance(float distance)
{
	mSfxPlayer_->setMinDistance(distance);
}

void SimpleSFX::setAttenuation(float attenuation)
{
	mSfxPlayer_->setAttenuation(attenuation);
}

void SimpleSFX::setLoop(bool loop)
{
	mSfxPlayer_->setLoop(loop);
}

float SimpleSFX::getPitch()
{
	return mSfxPlayer_->getPitch();
}

bool SimpleSFX::isRelativeToListener()
{
	return mSfxPlayer_->isRelativeToListener();
}

float SimpleSFX::getMinDistance()
{
	return mSfxPlayer_->getMinDistance();
}

float SimpleSFX::getAttenuation()
{
	return mSfxPlayer_->getAttenuation();
}

bool SimpleSFX::getLoop()
{
	return mSfxPlayer_->getLoop();
}

void SimpleSFX::setCurrentSFXName(string newCurrentSFXName)
{
	SFX::setCurrentSFXName(newCurrentSFXName);
	AudioSource* baseAudioSource = AudioManager::Inst()->findAudioSource(newCurrentSFXName);
	
	// using dynamic_cast because baseAudioSource may not exist
	SimpleAudioSource* simpleAudioSource = dynamic_cast<SimpleAudioSource*>(baseAudioSource);
	if (simpleAudioSource && mSfxPlayer_){
		mSfxPlayer_->setBuffer(* (simpleAudioSource->getBuffer()) );
	}
}
