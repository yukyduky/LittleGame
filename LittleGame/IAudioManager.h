#pragma once
#ifndef IAUDIOMANAGER_H
#define IAUDIOMANAGER_H

#include <string>

/* ---:HOW TO ADD NEW MUSIC OR SOUND:---
1. Add a enum in the right namespace down below
2. Go into audioManager.cpp and init() 
3. Use the loadSound for sound (or mapMusic for music) function to add the audio the array
	3.1 Binds the enum to the right filepath
4. Use play to change music or play up a sound
*/



namespace SOUND {
	enum NAME { AHEM, GULP, BEEP0, BEEP1, BEEP2, BEEP3, BEEP4, SIZE };
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
	virtual void adjustMaster(int volume) = 0;
	virtual void adjustMaster(bool value) = 0;
	//Changes music to parameter (0-100)
	virtual void adjustMusic(int volume) = 0;
	//Changes sound to parameter (0-100)
	virtual void adjustEffects(int volume) = 0;

	virtual void setRepeatMusic(bool repeat) = 0;
	virtual void cleanUp() = 0;
};

#endif // !IAUDIOMANAGER_H
