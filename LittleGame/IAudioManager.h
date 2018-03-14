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
	enum NAME {
		AHEM, GULP, METAL_0, METAL_1, CLICK,
		ABILITY0_GLYPH0, ABILITY0_GLYPH2,
		ABILITY1_GLYPH0, ABILITY1_GLYPH1, ABILITY1_GLYPH2, ABILITY1_GLYPH3,
		ABILITY2_GLYPH0_THROW, ABILITY2_GLYPH0_EXPLOSION, ABILITY2_GLYPH1_EXPLOSION, ABILITY2_GLYPH2_ARMED, ABILITY2_GLYPH2_EXPLOSION, ABILITY2_GLYPH3_EXPLOSION,
		ABILITY3_GLYPH0, ABILITY3_GLYPH1,
		ABILITY4_GLYPH0, ABILITY4_GLYPH1, ABILITY4_GLYPH2,
		TRIANGLESLICE,
		ENEMYATTACK_1, ENEMYATTACK_2, ENEMYATTACK_3, ENEMYATTACK_4,
		ENEMYATTACK_5, ENEMYATTACK_6, ENEMYATTACK_7, ENEMYATTACK_8,
		ENEMYATTACK_9, ENEMYATTACK_10, ENEMYATTACK_11,
		ATTACKGRUNT_1, ATTACKGRUNT_2, ATTACKGRUNT_3, ATTACKGRUNT_4,
		ATTACKGRUNT_5, ATTACKGRUNT_6, ATTACKGRUNT_7, ATTACKGRUNT_8,
		ATTACKGRUNT_9,
		ENEMYDEATH_1, ENEMYDEATH_2, ENEMYDEATH_3, ENEMYDEATH_4, ENEMYDEATH_5,
		GENERATORHIT, GENERATORDESTROYED, ELECTRIFIEDEFFECT, HEATEDEFFECT, SLOWEFFECT,
		SIZE };
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
	virtual void stopAll() = 0;
	virtual void stopMusic() = 0;
	virtual void stopSound() = 0;
	virtual void pause(MUSIC::NAME name) = 0;
	virtual void pause(SOUND::NAME name) = 0;
	virtual void adjustMaster(bool value) = 0;
	//Changes both sound and music to parameter (0-100)
	virtual void adjustMaster(float volume) = 0;
	//Changes music to parameter (0-100)
	virtual void adjustMusic(float volume) = 0;
	//Changes sound to parameter (0-100)
	virtual void adjustEffects(float volume) = 0;

	virtual void setRepeatMusic(bool repeat) = 0;
	virtual void cleanUp() = 0;
};

#endif // !IAUDIOMANAGER_H
