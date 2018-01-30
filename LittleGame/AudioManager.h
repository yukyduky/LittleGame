#pragma once
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <string>
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
	bool repeatMusic;
	std::array<sf::SoundBuffer, SOUND::SIZE> sounds;
	std::array<std::string, MUSIC::SIZE> musicFilenames;
	//Queue isnt neccesary and the game will play the sound instantly
	std::deque<sf::Sound> soundQueue;
	sf::Music currentMusic;
	//Sound object that will play the sound
	sf::Sound currentSound;

	int volume = 100;
public:
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
	void stop(MUSIC::NAME name);
	void stop(SOUND::NAME name);
	void pause(MUSIC::NAME name);
	void pause(SOUND::NAME name);
	void adjustMaster(size_t volume);
	void adjustMusic(size_t volume);
	void adjustEffects(size_t volume);

	void setRepeatMusic(bool repeat);
};

#endif // !SOUNDMANAGER_H
