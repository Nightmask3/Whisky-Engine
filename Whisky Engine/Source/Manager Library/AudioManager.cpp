#include "AudioManager.h"


#include <iostream>

AudioManager* AudioManager::_pInstance = NULL;

AudioManager* AudioManager::Inst()
{
	if (_pInstance == NULL) _pInstance = new AudioManager();
	return _pInstance;
}

void AudioManager::registerMusic(std::string musicKey, IMusic* music)
{
	mRegisteredMusic_.insert(std::make_pair(musicKey, music));
}

void AudioManager::registerSFX(Audio* audioComponent, SFX* sfx)
{
	mRegisteredSFX_.insert(std::make_pair(audioComponent, sfx));
}

void AudioManager::registerAudioSource(std::string source, AudioSource* audioSource)
{
	mRegisteredAudioSource_.insert(std::make_pair(source, audioSource));
}

IMusic* AudioManager::findMusic(std::string musicKey)
{
	IMusic* retVal = nullptr;

	try{
		retVal = mRegisteredMusic_.at(musicKey);
	}
	catch (std::out_of_range &e){
		std::cout << "There is no Music associated with this key: " << e.what() << std::endl;
	}
	return retVal;
}

SFX* AudioManager::findSFX(Audio* audioComponent)
{
	SFX* retVal = nullptr;

	try{
		retVal = mRegisteredSFX_.at(audioComponent);
	}
	catch (std::out_of_range &e){
		std::cout << "There is no SFX associated with this key: " << e.what() << std::endl;
	}
	return retVal;
}

AudioSource* AudioManager::findAudioSource(std::string audioSource)
{
	AudioSource* retVal = nullptr;

	try{
		retVal = mRegisteredAudioSource_.at(audioSource);
	}
	catch (std::out_of_range &e){
		std::cout << "There is no audio source associated with this key: " << e.what() << std::endl;
	}
	return retVal;
}

void AudioManager::removeMusic(std::string musicKey)
{
	mRegisteredMusic_.erase(musicKey);
}


void AudioManager::removeSFX(Audio* audioComponent)
{
	mRegisteredSFX_.erase(audioComponent);
}

void AudioManager::removeAudioSource(std::string audioSource)
{
	mRegisteredAudioSource_.erase(audioSource);
}

void AudioManager::removeAllMusic()
{
	//delete each pointer individually
	for (auto element : mRegisteredMusic_){
		delete element.second;
	}

	//then clear the map
	mRegisteredMusic_.clear();
}

void AudioManager::removeAllSFX()
{
	//delete each pointer individually
	for (auto element : mRegisteredSFX_){
		delete element.second;
	}

	//then clear the map
	mRegisteredSFX_.clear();
}

void AudioManager::removeAllAudioSource()
{
	//delete each pointer individually
	for (auto element : mRegisteredAudioSource_){
		delete element.second;
	}

	//then clear the map
	mRegisteredAudioSource_.clear();
}

AudioManager::AudioManager()
{
	std::cout << "Audio Manager is initialized." << std::endl;
}


AudioManager::~AudioManager()
{
	removeAllMusic();
	removeAllSFX();
	removeAllAudioSource();
}
