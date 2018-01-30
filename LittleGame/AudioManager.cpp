#include "AudioManager.h"

int AudioManager::init()
{
	int error = 0;

	error += this->loadSound(std::string("include/Sound/ahem_x.wav"), SOUND::AHEM);

	this->currentSound.setVolume(this->volume);
	return error;
}

int AudioManager::loadSound(std::string filename, SOUND::NAME name)
{
	int error = 0;
	if (!this->sounds[name].loadFromFile(filename)) {
		error = -1;
	}
	return error;
}

int AudioManager::loadMusic(std::string filename)
{
	int error = 0;
	if (!this->currentMusic.openFromFile(filename)) {
		error = -1;
	}
	return error;
}

int AudioManager::mapMusic(std::string filename, MUSIC::NAME name)
{
	int error = 0;
	if (this->loadMusic(filename) == 0) {
		this->musicFilenames[name] = filename;
	}
	return error;
}

void AudioManager::update()
{

	for (size_t i = 0; i < this->soundQueue.size(); i++)
	{
		this->soundQueue[i].play();
	}
	this->soundQueue.clear();
}

void AudioManager::play(MUSIC::NAME name)
{
//	this->cur
//	this->currentMusic.play(this->musicFilenames[name]);
}

void AudioManager::play(SOUND::NAME name)
{
	//Used to add sound to the queue but not used in current version
	//this->soundQueue.push_back(sf::Sound(this->sounds[name]));
	//this->soundQueue.back().setVolume(this->volume);

	this->currentSound.setBuffer(this->sounds[name]);
	this->currentSound.play();
}

void AudioManager::stop(MUSIC::NAME name)
{
	this->currentMusic.stop();
}

void AudioManager::stop(SOUND::NAME name)
{
}

void AudioManager::pause(MUSIC::NAME name)
{
}

void AudioManager::pause(SOUND::NAME name)
{
}

void AudioManager::adjustMaster(size_t volume)
{
}

void AudioManager::adjustMusic(size_t volume)
{
}

void AudioManager::adjustEffects(size_t volume)
{
}

void AudioManager::setRepeatMusic(bool repeat)
{
	this->repeatMusic = repeat;
}