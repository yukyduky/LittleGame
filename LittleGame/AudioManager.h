#pragma once
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SFML\Audio.hpp>
#include <array>
#include <deque>
#include "IAudioManager.h"

/*	---:INFO:---
Sound: Plays sound from the buffer, more lightweght
Music: Streams from a file, saves memory
*/

class AudioManager : public IAudioManager
{
private:
	bool repeatMusic = true;
	std::array<sf::SoundBuffer, SOUND::SIZE> sounds;
	std::array<std::string, MUSIC::SIZE> musicFilenames;
	//Queue isnt neccesary and the game will play the sound instantly
	std::array<sf::Sound, SOUND::SIZE> soundQueue;
	std::array<sf::Music, MUSICSTATE::SIZE> currentMusic;
	//Sound object that will play the sound
	sf::Sound currentSound;

	float soundVolume = 10.0f;
	float musicVolume = 3.0f;

	// What MUSICSTATE the game is in, declared as LEVEL1 in current version
	size_t currState = 0;
public:
	AudioManager();
	~AudioManager() {}
	//Loads in all music and sound
	int init();
	//Adds a posible sound
	int loadSound(std::string filename, SOUND::NAME name);
	int loadMusic(std::string filename);
	int mapMusic(std::string filename, MUSIC::NAME name);
	//Plays all sounds in soundQueue, called in each frame.
	//Not in current version
	void update();
	void play(MUSIC::NAME name);
	//Plays the sound once per call
	void play(SOUND::NAME name);
	void stopAll();
	void stopMusic();
	void stopSound();
	void pause(MUSIC::NAME name);
	void pause(SOUND::NAME name);
	// true = audio up
	void adjustMaster(bool value);
	void adjustMaster(float volume);
	void adjustMusic(float volume);
	void adjustEffects(float volume);

	void setRepeatMusic(bool repeat);

	void cleanUp();
};

#endif // !SOUNDMANAGER_H
