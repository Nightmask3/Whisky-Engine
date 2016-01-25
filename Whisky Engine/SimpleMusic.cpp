#include "SimpleMusic.h"
#include "Source/Manager Library/AudioManager.h"
#include <iostream>

SimpleMusic::SimpleMusic(std::string musicName)
{
	music = new sf::Music;
	if (!music->openFromFile(musicName)){
		std::cout << musicName << " couldn't be opened." << std::endl;
		delete music;
	}

	AudioManager::Inst()->registerMusic(musicName, this);
}

SimpleMusic::~SimpleMusic()
{
	// Will be handled at AudioManager
	//delete music;
}

void SimpleMusic::play()
{
	music->play();
}

void SimpleMusic::pause()
{
	music->pause();
}

void SimpleMusic::stop()
{
	music->stop();
}

void SimpleMusic::setVolume(float volume)
{
	music->setVolume(volume);
}

void SimpleMusic::setPitch(float pitch)
{
	music->setPitch(pitch);
}

void SimpleMusic::setPosition(float x, float y, float z)
{
	music->setPosition(x, y, z);
}

void SimpleMusic::setRelativeToListener(bool relative)
{
	music->setRelativeToListener(relative);
}

void SimpleMusic::setMinDistance(float distance)
{
	music->setMinDistance(distance);
}

void SimpleMusic::setAttenuation(float attenuation)
{
	music->setAttenuation(attenuation);
}

void SimpleMusic::setLoop(bool loop)
{
	music->setLoop(loop);
}

float SimpleMusic::getPitch()
{
	return music->getPitch();
}

bool SimpleMusic::isRelativeToListener()
{
	return music->isRelativeToListener();
}

float SimpleMusic::getMinDistance()
{
	return music->getMinDistance();
}

float SimpleMusic::getAttenuation()
{
	return music->getAttenuation();
}

bool SimpleMusic::getLoop()
{
	return music->getLoop();
}
