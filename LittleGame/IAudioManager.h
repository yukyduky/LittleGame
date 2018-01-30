#pragma once
#ifndef ISOUNDMANAGER_H
#define ISOUNDMANAGER_H

namespace SOUND {
	enum NAME { AHEM, GUNSHOT, SIZE };
}
namespace MUSIC {
	enum NAME { INGAME, SIZE };
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
	virtual int loadMusic(std::string filename) = 0;
	virtual int mapMusic(std::string filename, MUSIC::NAME name) = 0;
	//Plays all sounds in soundQueue, called in each frame.
	virtual void update() = 0;
	virtual void play(MUSIC::NAME name) = 0;
	//Puts a sound into soundQueue
	virtual void play(SOUND::NAME name) = 0;
	virtual void stop(MUSIC::NAME name) = 0;
	virtual void stop(SOUND::NAME name) = 0;
	virtual void pause(MUSIC::NAME name) = 0;
	virtual void pause(SOUND::NAME name) = 0;
	virtual void adjustMaster(size_t volume) = 0;
	virtual void adjustMusic(size_t volume) = 0;
	virtual void adjustEffects(size_t volume) = 0;

	virtual void setRepeatMusic(bool repeat) = 0;
};

#endif // !ISOUNDMANAGER_H
