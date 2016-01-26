#include "Audio.h"
#include "../Manager Library/AudioManager.h"
#include "../Entity Library/GameObject.h"
#include "../../IMusic.h"
#include "../../SFX.h"
#include "../../AudioSource.h"

#include "../../Engine.h"

Audio::Audio() : Component(Component::AUDIO, "Audio")
{
}


Audio::~Audio()
{
}

void Audio::Update()
{
	if (INP->IsKeyTriggered(KeyCode::Space))
		(mOwner_->GetComponent<Audio>())->play("greatmusic.ogg");
	
	if (INP->IsKeyTriggered(KeyCode::S))
		(mOwner_->GetComponent<Audio>())->stop("greatmusic.ogg");

	if (INP->IsKeyTriggered(KeyCode::P))
		(mOwner_->GetComponent<Audio>())->play("scream.wav");

}

void Audio::HandleMessage(Message*)
{

}

void Audio::play(string key)
{
	if (AudioSource* audioSource = AM->findAudioSource(key)){
		SFX* mySfx = AM->findSFX(this);
		mySfx->play();
	}
	else if (IMusic* music = AM->findMusic(key)){
		music->play();
	}
}

void Audio::pause(string key)
{
	if (AudioSource* audioSource = AM->findAudioSource(key)){
		SFX* mySfx = AM->findSFX(this);
		mySfx->pause();
	}
	else if (IMusic* music = AM->findMusic(key)){
		music->pause();
	}
}

void Audio::stop(string key)
{
	if (AudioSource* audioSource = AM->findAudioSource(key)){
		SFX* mySfx = AM->findSFX(this);
		mySfx->stop();
	}
	else if (IMusic* music = AM->findMusic(key)){
		music->stop();
	}
}

void Audio::setVolume(string key, float volume)
{
	if (AudioSource* audioSource = AM->findAudioSource(key)){
		SFX* mySfx = AM->findSFX(this);
		mySfx->setVolume(volume);
	}
	else if (IMusic* music = AM->findMusic(key)){
		music->setVolume(volume);
	}
}

void Audio::setPitch(string key, float pitch)
{
	if (AudioSource* audioSource = AM->findAudioSource(key)){
		SFX* mySfx = AM->findSFX(this);
		mySfx->setPitch(pitch);
	}
	else if (IMusic* music = AM->findMusic(key)){
		music->setPitch(pitch);
	}
}

void Audio::setPosition(string key, float x, float y, float z)
{
	if (AudioSource* audioSource = AM->findAudioSource(key)){
		SFX* mySfx = AM->findSFX(this);
		mySfx->setPosition(x, y, z);
	}
	else if (IMusic* music = AM->findMusic(key)){
		music->setPosition(x, y, z);
	}
}

void Audio::setRelativeToListener(string key, bool relative)
{
	if (AudioSource* audioSource = AM->findAudioSource(key)){
		SFX* mySfx = AM->findSFX(this);
		mySfx->setRelativeToListener(relative);
	}
	else if (IMusic* music = AM->findMusic(key)){
		music->setRelativeToListener(relative);
	}
}

void Audio::setMinDistance(string key, float distance)
{
	if (AudioSource* audioSource = AM->findAudioSource(key)){
		SFX* mySfx = AM->findSFX(this);
		mySfx->setMinDistance(distance);
	}
	else if (IMusic* music = AM->findMusic(key)){
		music->setMinDistance(distance);
	}
}

void Audio::setAttenuation(string key, float attenuation)
{
	if (AudioSource* audioSource = AM->findAudioSource(key)){
		SFX* mySfx = AM->findSFX(this);
		mySfx->setAttenuation(attenuation);
	}
	else if (IMusic* music = AM->findMusic(key)){
		music->setAttenuation(attenuation);
	}
}

void Audio::setLoop(string key, bool loop)
{
	if (AudioSource* audioSource = AM->findAudioSource(key)){
		SFX* mySfx = AM->findSFX(this);
		mySfx->setLoop(loop);
	}
	else if (IMusic* music = AM->findMusic(key)){
		music->setLoop(loop);
	}
}

float Audio::getPitch(string key)
{
	float pitch = 0.0f;

	if (AudioSource* audioSource = AM->findAudioSource(key)){
		SFX* mySfx = AM->findSFX(this);
		pitch = mySfx->getPitch();
	}
	else if (IMusic* music = AM->findMusic(key)){
		pitch = music->getPitch();
	}

	return pitch;
}

bool Audio::isRelativeToListener(string key)
{
	bool relative =false;

	if (AudioSource* audioSource = AM->findAudioSource(key)){
		SFX* mySfx = AM->findSFX(this);
		relative = mySfx->isRelativeToListener();
	}
	else if (IMusic* music = AM->findMusic(key)){
		relative = music->isRelativeToListener();
	}

	return relative;
}

float Audio::getMinDistance(string key)
{
	float minDistance = 0.0f;

	if (AudioSource* audioSource = AM->findAudioSource(key)){
		SFX* mySfx = AM->findSFX(this);
		minDistance = mySfx->getMinDistance();
	}
	else if (IMusic* music = AM->findMusic(key)){
		minDistance = music->getMinDistance();
	}

	return minDistance;
}

float Audio::getAttenuation(string key)
{
	float attenuation = 0.0f;

	if (AudioSource* audioSource = AM->findAudioSource(key)){
		SFX* mySfx = AM->findSFX(this);
		attenuation = mySfx->getAttenuation();
	}
	else if (IMusic* music = AM->findMusic(key)){
		attenuation = music->getAttenuation();
	}

	return attenuation;
}

bool Audio::getLoop(string key)
{
	bool loop = false;

	if (AudioSource* audioSource = AM->findAudioSource(key)){
		SFX* mySfx = AM->findSFX(this);
		loop = mySfx->getLoop();
	}
	else if (IMusic* music = AM->findMusic(key)){
		loop = music->getLoop();
	}

	return loop;
}

