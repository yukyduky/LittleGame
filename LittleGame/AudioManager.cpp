#include "AudioManager.h"


int AudioManager::init()
{
	
	int error = 0;

	error += this->loadSound(std::string("include/Sound/ahem_x.wav"), SOUND::AHEM);
	error += this->loadSound(std::string("include/Sound/gulp_x.wav"), SOUND::GULP);
	error += this->loadSound(std::string("include/Sound/beep0.wav"), SOUND::BEEP0);
	error += this->loadSound(std::string("include/Sound/beep1.wav"), SOUND::BEEP1);
	error += this->loadSound(std::string("include/Sound/beep2.wav"), SOUND::BEEP2);
	error += this->loadSound(std::string("include/Sound/beep3.wav"), SOUND::BEEP3);
	error += this->loadSound(std::string("include/Sound/beep4.wav"), SOUND::BEEP4);

	error += this->mapMusic(std::string("include/Sound/OPM-OST.ogg"), MUSIC::ONEPUNCH);

	this->adjustEffects(this->soundVolume);
	this->adjustMusic(this->musicVolume);

	// What MUSICSTATE the game is in, declared as LEVEL1 in current version
	this->currState = MUSICSTATE::LEVEL1;

	return error;
}

int AudioManager::loadSound(std::string filename, SOUND::NAME name)
{
	int error = 0;
	if (this->sounds[name].loadFromFile(filename)) {
		this->soundQueue[name].setBuffer(this->sounds[name]);
	}
	else
	{
		error = -1;
	}
	return error;
}

int AudioManager::loadMusic(std::string filename)
{
	int error = 0;
	//if (!this->currentMusic.openFromFile(filename)) {
	//	error = -1;
	//}
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
}

void AudioManager::play(MUSIC::NAME name)
{
	this->currentMusic[currState].openFromFile(this->musicFilenames[name]);
	this->currentMusic[currState].play();
}

void AudioManager::play(SOUND::NAME name)
{
	this->soundQueue[name].play();
}

void AudioManager::stop(MUSIC::NAME name)
{
	this->currentMusic[currState].stop();
}

void AudioManager::stop(SOUND::NAME name)
{
}

void AudioManager::pause(MUSIC::NAME name)
{
	this->currentMusic[currState].pause();
}

void AudioManager::pause(SOUND::NAME name)
{
}

void AudioManager::adjustMaster(size_t volume)
{
	this->adjustEffects(volume);

	this->adjustMusic(volume);
}

void AudioManager::adjustMusic(size_t volume)
{
	for (size_t i = 0; i < MUSICSTATE::SIZE; i++)
	{
		this->currentMusic[i].setVolume(this->musicVolume);
	}
}

void AudioManager::adjustEffects(size_t volume)
{
	this->currentSound.setVolume(this->soundVolume);
}

void AudioManager::setRepeatMusic(bool repeat)
{
	this->repeatMusic = repeat;
}

void AudioManager::cleanUp()
{
	//this->soundQueue.clear();
	for (int i = 0; i < this->sounds.size(); i++) {
		sounds[i].~SoundBuffer();
	}
	for (int i = 0; i < this->musicFilenames.size(); i++) {
		musicFilenames[i].clear();
	}
	for (int i = 0; i < this->currentMusic.size(); i++) {
		this->currentMusic[i].~Music();
	}
	this->currentSound.~Sound();

}
