#ifndef MUSIC_H
#define MUSIC_H

#include <iostream>

using std::string;

class IMusic
{
public:
	IMusic();
	~IMusic();

	// To play the audio matched with "key"
	// If called after "pause" then resumes it
	virtual void play() = 0;

	// To pause the audio matched with "key"
	virtual void pause() = 0;

	// To stop the audio matched with "key"
	virtual void stop() = 0;

	// Used for setting the volume of the audio defined matched with "key"
	virtual void setVolume(float volume) = 0;

	// Used for setting the pitch of the audio defined matched with "key"
	virtual void setPitch(float pitch) = 0;

	// Used for setting the position of the audio defined matched with "key"
	virtual void setPosition(float x, float y, float z) = 0;

	// Used for setting the relativity of the audio defined matched with "key"
	virtual void setRelativeToListener(bool relative) = 0;

	// Used for setting the minimum distance of the audio defined matched with "key"
	virtual void setMinDistance(float distance) = 0;

	// Used for setting the attenuation of the audio defined matched with "key"
	virtual void setAttenuation(float attenuation) = 0;

	// Used for setting the loop condition of the audio defined matched with "key"
	virtual void setLoop(bool loop) = 0;

	// Used for getting the pitch of the audio defined matched with "key"
	virtual float getPitch() = 0;

	// Used for getting the relativity of the audio defined matched with "key"
	virtual bool isRelativeToListener() = 0;

	// Used for getting the minimum distance of the audio defined matched with "key"
	virtual float getMinDistance() = 0;

	// Used for getting the attenuation of the audio defined matched with "key"
	virtual float getAttenuation() = 0;

	// Used for getting the loop condition of the audio defined matched with "key"
	virtual bool getLoop() = 0;
};

#endif

