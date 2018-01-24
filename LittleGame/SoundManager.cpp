#include "SoundManager.h"



int SoundManager::loadSound(std::string filename, SOUND::NAME name)
{
	int error = 0;
	if (!this->sounds[name].loadFromFile(filename)) {
		error = -1;
	}
	return error;
}

int SoundManager::loadMusic(std::string filename)
{
	int error = 0;
	if (!this->currentMusic.openFromFile(filename)) {
		error = -1;
	}
	return error;
}

int SoundManager::mapMusic(std::string filename, MUSIC::NAME name)
{
	int error = 0;
	if (this->loadMusic(filename) == 0) {
		this->musicFilenames[name] = filename;
	}
	return error;
}

void SoundManager::update()
{

}

void SoundManager::play(MUSIC::NAME name)
{
	this->cur
	this->currentMusic.play(this->musicFilenames[name]);
}

void SoundManager::play(SOUND::NAME name)
{
	this->soundQueue.push_back(sf::Sound(this->sounds[name]));
}

void SoundManager::stop(MUSIC::NAME name)
{
	this->currentMusic.stop();
}

void SoundManager::stop(SOUND::NAME name)
{
}

void SoundManager::pause(MUSIC::NAME name)
{
}

void SoundManager::pause(SOUND::NAME name)
{
}

void SoundManager::adjustMaster(size_t volume)
{
}

void SoundManager::adjustMusic(size_t volume)
{
}

void SoundManager::adjustEffects(size_t volume)
{
}

void SoundManager::setRepeatMusic(bool repeat)
{
	this->repeatMusic = repeat;
}
