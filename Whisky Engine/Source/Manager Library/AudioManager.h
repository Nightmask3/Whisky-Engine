#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <map>
#include <string>

#include "../../IMusic.h"
#include "../../SFX.h"
#include "../../AudioSource.h"
#include "../Component Library/Audio.h"
#include "../../SimpleMusic.h"
#include "../../SimpleAudioSource.h"
#include "../../SimpleSFX.h"
class IMusic;
class SFX;
class GameObject;
class AudioSource;
class Audio;
/*
	This class is used for Client's interaction with Audio module.
	Client will use AudioManager's respective methods to register sound effects or gameplay music files.
	After registration, Client will be able to work on the sfx/music registered.
*/
class AudioManager
{
public:
	static AudioManager* Inst();

	// Used for adding Music to it's respective map using the key value
	// GameObject pointer is used to register the owner of the music
	void registerMusic(std::string musicKey, IMusic* music);
	// Used for adding SFX to it's respective map
	void registerSFX(Audio* audioComponent, SFX* sfx);
	// Used for adding audio source to it's respective map
	void registerAudioSource(std::string source, AudioSource* audioSource);
	// Used for returning the Music associated with the musicKey
	IMusic* findMusic(std::string musicKey);
	// Used for returning the SFX associated with the audioComponent
	SFX* findSFX(Audio* audioComponent);
	// Used for returning the audio source associated with the audioSource
	AudioSource* findAudioSource(std::string audioSource);
	// Used for removing the Music associated with the musicKey
	void removeMusic(std::string musicKey);
	// Used for removing the SFX associated with the sfxName
	void removeSFX(Audio* audioComponent);
	// Used for removing the audio source associated with the audioSource
	void removeAudioSource(std::string audioSource);
	// Used for removing all the registered Music.
	// Added to be used while unloading a level.
	void removeAllMusic();
	// Used for removing all the registered SFX.
	// Added to be used while unloading a level.
	void removeAllSFX();
	// Used for removing all the registered SFX.
	// Added to be used while unloading a level.
	void removeAllAudioSource();

private:
	AudioManager();
	~AudioManager();

	std::map<std::string, IMusic*> mRegisteredMusic_;
	std::map<Audio*, SFX*> mRegisteredSFX_;
	std::map<std::string, AudioSource*> mRegisteredAudioSource_;

	static AudioManager* _pInstance;

};

#endif

