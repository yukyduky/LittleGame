#pragma once
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <string>
#include <SFML\Audio.hpp>
#include <array>
#include <deque>

namespace SOUND {
	enum NAME { GUNSHOT, SIZE };
}
namespace MUSIC {
	enum NAME { INGAME, SIZE };
}

class SoundManager
{
private:
	bool repeatMusic;
	std::array<sf::SoundBuffer, SOUND::SIZE> sounds;
	std::array<std::string, MUSIC::SIZE> musicFilenames;
	std::deque<sf::Sound> soundQueue;
	sf::Music currentMusic;
public:
	virtual int loadSound(std::string filename, SOUND::NAME name);
	virtual int loadMusic(std::string filename);
	virtual int mapMusic(std::string filename, MUSIC::NAME name);
	virtual void update();
	virtual void play(MUSIC::NAME name);
	virtual void play(SOUND::NAME name);
	virtual void stop(MUSIC::NAME name);
	virtual void stop(SOUND::NAME name);
	virtual void pause(MUSIC::NAME name);
	virtual void pause(SOUND::NAME name);
	virtual void adjustMaster(size_t volume);
	virtual void adjustMusic(size_t volume);
	virtual void adjustEffects(size_t volume);

	virtual void setRepeatMusic(bool repeat);
};

#endif // !SOUNDMANAGER_H
