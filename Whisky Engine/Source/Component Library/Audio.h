#ifndef AUDIO_H
#define AUDIO_H

#include "Component.h"
#include "SFML/Audio/Sound.hpp"

using std::string;

class GameObject;

class Audio : public Component
{
public:
	Audio();
	~Audio();

	virtual void Update() override;
	virtual void HandleMessage(Message*) override;

	// To play the audio matched with "key"
	// If called after "pause" then resumes it
	void play(string key);

	// To pause the audio matched with "key"
	void pause(string key);

	// To stop the audio matched with "key"
	void stop(string key);

	// Used for setting the volume of the audio defined matched with "key"
	void setVolume(string key, float volume);

	// Used for setting the pitch of the audio defined matched with "key"
	void setPitch(string key, float pitch);

	// Used for setting the position of the audio defined matched with "key"
	void setPosition(string key, float x, float y, float z);

	// Used for setting the relativity of the audio defined matched with "key"
	void setRelativeToListener(string key, bool relative);

	// Used for setting the minimum distance of the audio defined matched with "key"
	void setMinDistance(string key, float distance);

	// Used for setting the attenuation of the audio defined matched with "key"
	void setAttenuation(string key, float attenuation);

	// Used for setting the loop condition of the audio defined matched with "key"
	void setLoop(string key, bool loop);

	// Used for getting the pitch of the audio defined matched with "key"
	float getPitch(string key);

	// Used for getting the relativity of the audio defined matched with "key"
	bool isRelativeToListener(string key);

	// Used for getting the minimum distance of the audio defined matched with "key"
	float getMinDistance(string key);

	// Used for getting the attenuation of the audio defined matched with "key"
	float getAttenuation(string key);

	// Used for getting the loop condition of the audio defined matched with "key"
	bool getLoop(string key);

	//TODO: IMPLEMENT AFTER GLM IMPLEMENTATION
	//void setPosition(string key, Vector3D position); 
	//Vector3D getPosition(string key);

	//TODO: IMPLEMENT IF NEEDED
	//sf::Time getDuration(std::string key);
	//sf::Time getPlayingOffset(string key);
	//void setPlayingOffset(sf::Time offset);
	//sf::Status getStatus();
private:
	/*typedef void noArgs(void);

	void noArgsRoutine(string key, noArgs);*/
};

#endif

