
#include "AudioManager.h"


AudioManager::AudioManager() : soundVolume(10.0f), musicVolume(10.0f)
{
}

int AudioManager::init()
{
	int error = 0;

	error += this->loadSound(std::string("include/Sound/ahem_x.wav"), SOUND::AHEM);
	error += this->loadSound(std::string("include/Sound/gulp_x.wav"), SOUND::GULP);
	error += this->loadSound(std::string("include/Sound/hammer_anvil.wav"), SOUND::METAL_0);
	error += this->loadSound(std::string("include/Sound/metal_crunch.wav"), SOUND::METAL_1);
	error += this->loadSound(std::string("include/Sound/typewriter_click.wav"), SOUND::CLICK);

	error += this->loadSound(std::string("include/Sound/Ability0_Glyph0.wav"), SOUND::ABILITY0_GLYPH0);
	error += this->loadSound(std::string("include/Sound/Ability0_Glyph2.wav"), SOUND::ABILITY0_GLYPH2);
	error += this->loadSound(std::string("include/Sound/Ability1_Glyph0.wav"), SOUND::ABILITY1_GLYPH0);
	error += this->loadSound(std::string("include/Sound/Ability1_Glyph1.wav"), SOUND::ABILITY1_GLYPH1);
	error += this->loadSound(std::string("include/Sound/Ability1_Glyph2.wav"), SOUND::ABILITY1_GLYPH2);
	error += this->loadSound(std::string("include/Sound/Ability1_Glyph3.wav"), SOUND::ABILITY1_GLYPH3);
	error += this->loadSound(std::string("include/Sound/Ability2_Glyph0_Throw.wav"), SOUND::ABILITY2_GLYPH0_THROW);
	error += this->loadSound(std::string("include/Sound/Ability2_Glyph0_Explosion.wav"), SOUND::ABILITY2_GLYPH0_EXPLOSION);
	error += this->loadSound(std::string("include/Sound/Ability2_Glyph1_Explosion.wav"), SOUND::ABILITY2_GLYPH1_EXPLOSION);
	error += this->loadSound(std::string("include/Sound/Ability2_Glyph2_Armed.wav"), SOUND::ABILITY2_GLYPH2_ARMED);
	error += this->loadSound(std::string("include/Sound/Ability2_Glyph2_Explosion.wav"), SOUND::ABILITY2_GLYPH2_EXPLOSION);
	error += this->loadSound(std::string("include/Sound/Ability2_Glyph3_Explosion.wav"), SOUND::ABILITY2_GLYPH3_EXPLOSION);
	error += this->loadSound(std::string("include/Sound/Ability3_Glyph0.wav"), SOUND::ABILITY3_GLYPH0);
	error += this->loadSound(std::string("include/Sound/Ability3_Glyph1.wav"), SOUND::ABILITY3_GLYPH1);
	error += this->loadSound(std::string("include/Sound/Ability4_Glyph0.wav"), SOUND::ABILITY4_GLYPH0);
	error += this->loadSound(std::string("include/Sound/Ability4_Glyph1.wav"), SOUND::ABILITY4_GLYPH1);
	error += this->loadSound(std::string("include/Sound/Ability4_Glyph2.wav"), SOUND::ABILITY4_GLYPH2);

	error += this->loadSound(std::string("include/Sound/8BIT_Death.wav"), SOUND::EIGHTBIT_DEATH);
	error += this->loadSound(std::string("include/Sound/8BIT_Start.wav"), SOUND::EIGHTBIT_START);
	error += this->loadSound(std::string("include/Sound/8BIT_LevelEnd.wav"), SOUND::EIGHTBIT_LEVELEND);
	error += this->loadSound(std::string("include/Sound/8BIT_NextWave.wav"), SOUND::EIGHTBIT_NEXTWAVE);
	
	error += this->loadSound(std::string("include/Sound/TriangleSlice.wav"), SOUND::TRIANGLESLICE);

	error += this->loadSound(std::string("include/Sound/EnemyAttack_1.wav"), SOUND::ENEMYATTACK_1);
	error += this->loadSound(std::string("include/Sound/EnemyAttack_2.wav"), SOUND::ENEMYATTACK_2);
	error += this->loadSound(std::string("include/Sound/EnemyAttack_3.wav"), SOUND::ENEMYATTACK_3);
	error += this->loadSound(std::string("include/Sound/EnemyAttack_4.wav"), SOUND::ENEMYATTACK_4);
	error += this->loadSound(std::string("include/Sound/EnemyAttack_5.wav"), SOUND::ENEMYATTACK_5);

	error += this->loadSound(std::string("include/Sound/EnemyDeath_1.wav"), SOUND::ENEMYDEATH_1);
	error += this->loadSound(std::string("include/Sound/EnemyDeath_2.wav"), SOUND::ENEMYDEATH_2);
	error += this->loadSound(std::string("include/Sound/EnemyDeath_3.wav"), SOUND::ENEMYDEATH_3);
	error += this->loadSound(std::string("include/Sound/EnemyDeath_4.wav"), SOUND::ENEMYDEATH_4);
	error += this->loadSound(std::string("include/Sound/EnemyDeath_5.wav"), SOUND::ENEMYDEATH_5);

	error += this->loadSound(std::string("include/Sound/gendestroy.wav"), SOUND::GENERATORDESTROYED);
	error += this->loadSound(std::string("include/Sound/genhit.wav"), SOUND::GENERATORHIT);
	error += this->loadSound(std::string("include/Sound/electrifiedeffect.wav"), SOUND::ELECTRIFIEDEFFECT);
	error += this->loadSound(std::string("include/Sound/heatedeffect2.wav"), SOUND::HEATEDEFFECT);
	error += this->loadSound(std::string("include/Sound/sloweffect.wav"), SOUND::SLOWEFFECT);


	error += this->mapMusic(std::string("include/Sound/OPM-OST.ogg"), MUSIC::ONEPUNCH);
	error += this->mapMusic(std::string("include/Sound/Menu_Music.ogg"), MUSIC::MENU_MUSIC);
	error += this->mapMusic(std::string("include/Sound/Game_Music.ogg"), MUSIC::GAME_MUSIC);

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
	this->currentMusic[currState].setLoop(true);
}

void AudioManager::play(SOUND::NAME name)
{
	this->soundQueue[name].play();
}

void AudioManager::stopAll()
{
	this->stopMusic();
	this->stopSound();
}

void AudioManager::stopMusic()
{
	this->currentMusic[currState].stop();
}

void AudioManager::stopSound()
{
	this->currentSound.stop();
}

void AudioManager::pause(MUSIC::NAME name)
{
	this->currentMusic[currState].pause();
}

void AudioManager::pause(SOUND::NAME name)
{
}

void AudioManager::adjustMaster(float volume)
{
	this->adjustEffects(volume);

	this->adjustMusic(volume);
}

void AudioManager::adjustMaster(bool value)
{
	if (value)
	{
		this->adjustEffects(5.0f);
		this->adjustMusic(1.0f);
	}
	else
	{
		this->adjustEffects(- 5.0f);
		this->adjustMusic(- 1.0f);
	}
}

void AudioManager::adjustMusic(float volume)
{
	this->musicVolume += volume;
	if (this->musicVolume < 0.0f)
	{
  		this->musicVolume = 0.0f;
	}
	else if (this->musicVolume > 100.0f)
	{
  		this->musicVolume = 100.0f;
	}
	for (int i = 0; i < MUSICSTATE::SIZE; i++)
	{
		this->currentMusic[i].setVolume(this->musicVolume);
	}
}

void AudioManager::adjustEffects(float volume)
{
	this->soundVolume += volume;
	if (this->soundVolume < 0.0f)
	{
		this->soundVolume = 0.0f;
	}
	else if (this->soundVolume > 100.0f)
	{
		this->soundVolume = 100.0f;
	}
	for (int i = 0; i < SOUND::SIZE; i++)
	{
		this->soundQueue[i].setVolume(this->soundVolume);
	}
}

void AudioManager::setRepeatMusic(bool repeat)
{
	this->repeatMusic = repeat;
}

void AudioManager::cleanUp()
{
	this->stopAll();	
}
