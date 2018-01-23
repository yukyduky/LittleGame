#pragma once
#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <string>
#include <SFML\Audio.hpp>
#include <vector>

namespace SOUND {
	enum NAME { GUNSHOT };
}
namespace MUSIC {
	enum NAME { INGAME };
}

class SoundManager
{
private:
	bool repeatMusic;
	
public:
	void loadSound(std::string filename);
	void loadMusic(std::string filename);
	void playSound(SOUND::NAME name);
	void playMusic(MUSIC::NAME name);
	void setRepeatMusic(bool repeat);
};

#endif // !SOUNDMANAGER_H
