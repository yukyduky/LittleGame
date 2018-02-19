#include "AudioManager.h"


AudioManager::AudioManager()
{

}

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

	error += this->loadSound(std::string("include/Sound/EnemyAttack_1.wav"), SOUND::ENEMYATTACK_1);
	error += this->loadSound(std::string("include/Sound/EnemyAttack_2.wav"), SOUND::ENEMYATTACK_2);
	error += this->loadSound(std::string("include/Sound/EnemyAttack_3.wav"), SOUND::ENEMYATTACK_3);
	error += this->loadSound(std::string("include/Sound/EnemyAttack_4.wav"), SOUND::ENEMYATTACK_4);
	error += this->loadSound(std::string("include/Sound/EnemyAttack_5.wav"), SOUND::ENEMYATTACK_5);
	error += this->loadSound(std::string("include/Sound/EnemyAttack_6.wav"), SOUND::ENEMYATTACK_6);
	error += this->loadSound(std::string("include/Sound/EnemyAttack_7.wav"), SOUND::ENEMYATTACK_7);
	error += this->loadSound(std::string("include/Sound/EnemyAttack_8.wav"), SOUND::ENEMYATTACK_8);
	error += this->loadSound(std::string("include/Sound/EnemyAttack_9.wav"), SOUND::ENEMYATTACK_9);
	error += this->loadSound(std::string("include/Sound/EnemyAttack_10.wav"), SOUND::ENEMYATTACK_10);
	error += this->loadSound(std::string("include/Sound/EnemyAttack_11.wav"), SOUND::ENEMYATTACK_11);

	error += this->loadSound(std::string("include/Sound/AttackGrunt_1.wav"), SOUND::ATTACKGRUNT_1);
	error += this->loadSound(std::string("include/Sound/AttackGrunt_2.wav"), SOUND::ATTACKGRUNT_2);
	error += this->loadSound(std::string("include/Sound/AttackGrunt_3.wav"), SOUND::ATTACKGRUNT_3);
	error += this->loadSound(std::string("include/Sound/AttackGrunt_4.wav"), SOUND::ATTACKGRUNT_4);
	error += this->loadSound(std::string("include/Sound/AttackGrunt_5.wav"), SOUND::ATTACKGRUNT_5);
	error += this->loadSound(std::string("include/Sound/AttackGrunt_6.wav"), SOUND::ATTACKGRUNT_6);
	error += this->loadSound(std::string("include/Sound/AttackGrunt_7.wav"), SOUND::ATTACKGRUNT_7);
	error += this->loadSound(std::string("include/Sound/AttackGrunt_8.wav"), SOUND::ATTACKGRUNT_8);
	error += this->loadSound(std::string("include/Sound/AttackGrunt_9.wav"), SOUND::ATTACKGRUNT_9);

	error += this->loadSound(std::string("include/Sound/EnemyDeath_1.wav"), SOUND::ENEMYDEATH_1);
	error += this->loadSound(std::string("include/Sound/EnemyDeath_2.wav"), SOUND::ENEMYDEATH_2);
	error += this->loadSound(std::string("include/Sound/EnemyDeath_3.wav"), SOUND::ENEMYDEATH_3);
	error += this->loadSound(std::string("include/Sound/EnemyDeath_4.wav"), SOUND::ENEMYDEATH_4);
	error += this->loadSound(std::string("include/Sound/EnemyDeath_5.wav"), SOUND::ENEMYDEATH_5);

	error += this->loadSound(std::string("include/Sound/AbilitySound_SpeedBoost.wav"), SOUND::ABILITYSOUND_SPEEDBOOST);
	error += this->loadSound(std::string("include/Sound/AbilitySound_Teleport.wav"), SOUND::ABILITYSOUND_TELEPORT);

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
}
