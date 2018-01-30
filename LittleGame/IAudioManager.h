#pragma once
#ifndef ISOUNDMANAGER_H
#define ISOUNDMANAGER_H

namespace SOUND {
	enum NAME { AHEM, GUNSHOT, SIZE };
}
namespace MUSIC {
	enum NAME { ONEPUNCH, SIZE };
}
namespace MUSICSTATE {
	enum NAME { LEVEL1, MENU, SIZE };
}

class IAudioManager
{
public:
	/*
	1. Loads in all music and sound
	2. Returns the amount of failed loads as negativ value
	*/
	virtual int init() = 0;
	//Adds a posible sound
	virtual int loadSound(std::string filename, SOUND::NAME name) = 0;
	//Not used
	virtual int loadMusic(std::string filename) = 0;
	//Set the translation from NAME to FILENAME
	virtual int mapMusic(std::string filename, MUSIC::NAME name) = 0;
	//Plays all sounds in soundQueue, called in each frame.
	virtual void update() = 0;
	//Plays the file that has been maped to NAME by mapMusic()
	virtual void play(MUSIC::NAME name) = 0;
	//Puts a sound into soundQueue
	virtual void play(SOUND::NAME name) = 0;
	virtual void stop(MUSIC::NAME name) = 0;
	virtual void stop(SOUND::NAME name) = 0;
	virtual void pause(MUSIC::NAME name) = 0;
	virtual void pause(SOUND::NAME name) = 0;
	//Changes both sound and music to parameter (0-100)
	virtual void adjustMaster(size_t volume) = 0;
	//Changes music to parameter (0-100)
	virtual void adjustMusic(size_t volume) = 0;
	//Changes sound to parameter (0-100)
	virtual void adjustEffects(size_t volume) = 0;

	virtual void setRepeatMusic(bool repeat) = 0;
};

#endif // !ISOUNDMANAGER_H
