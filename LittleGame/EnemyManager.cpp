#include "EnemyManager.h"
#include "ActorObject.h"
#include "GamePlayState.h"
#include "Locator.h"
#include "PhysicsComponent.h"
#include "BlockComponent.h"
#include "AIComponent.h"
#include "EnemyObject.h"
#include "EnemyAttackComponent.h"
#include "ImmolationEnemyAttack.h"
#include "EnemyAttackingState.h"
#include "EnemyMovingState.h"
#include "StateManager.h"
//#include "EndState.h"
#include "RewardMenuState.h"

EnemyManager::EnemyManager()
{
	this->pGPS = nullptr;

	this->activeEnemiesCount = 0;
}

EnemyManager::EnemyManager(GamePlayState& pGPS, std::vector<ActorObject*>& players)
{
	// Set up pointers
	this->pGPS = &pGPS;
	this->players = players; 
	this->activeEnemiesCount = 0;
	this->ramp = false;
	this->pulse = false;
}

void EnemyManager::startStandardLevel(enemySpawnPositions spawnPosVectors, float difficulty)
{
	this->startTime = Locator::getGameTime()->GetTime();
	this->timePassed = 0;
	this->activeEnemiesCount = 0;
	this->spawnInterval = 0.20f;
	this->waveInterval = (5.1f - (difficulty * 0.5f));
	this->currentWaveCount = (4 + static_cast<int>(difficulty));

	this->currentWaveEnemyCount.resize(10);
	for (int i = 0; i < this->currentWaveEnemyCount.size(); i++)
		this->currentWaveEnemyCount.at(i) = (20 + static_cast<int>(difficulty));

	Wave* currentWave = nullptr;

	// Per wave
	for (int i = 0; i < this->currentWaveCount; i++) {
		currentWave = new Wave();

		// Per enemy
		for (int j = 0; j < this->currentWaveEnemyCount.size(); j++) {
			// Create an enemy and attatch it to the wave.
			ActorObject* enemy = this->createEnemy(ENEMYTYPE::IMMOLATION, AIBEHAVIOR::STRAIGHTTOWARDS, spawnPosVectors);
			currentWave->enemies.push_back(enemy);
			this->activeEnemiesCount++;
		}

		// Attach the currentWave to our waves
		this->waves.push_back(currentWave);
	}
}

void EnemyManager::startRampLevel(enemySpawnPositions spawnPosVectors, float difficulty)
{
	this->startTime = Locator::getGameTime()->GetTime();
	this->timePassed = 0;
	this->activeEnemiesCount = 0;
	this->spawnInterval = 0.20f;
	this->waveInterval = 10.1f;
	this->currentWaveCount = 10;

	// Turn the 'ramp' effect ON
	this->ramp = true;
	
	this->currentWaveEnemyCount.resize(10);
	for (int i = 0; i < this->currentWaveEnemyCount.size(); i++)
		this->currentWaveEnemyCount.at(i) = (4 + (2 * i));
		//this->currentWaveEnemyCount.at(i) = (4 + static_cast<int>(1.5f * i));

	Wave* currentWave = nullptr;

	// Per wave
	for (int i = 0; i < this->currentWaveCount; i++) {
		currentWave = new Wave();

		// Per enemy
		for (int j = 0; j < this->currentWaveEnemyCount.at(i); j++) {
			// Create an enemy and attatch it to the wave.
			ActorObject* enemy = this->createEnemy(ENEMYTYPE::IMMOLATION, AIBEHAVIOR::STRAIGHTTOWARDS, spawnPosVectors);
			currentWave->enemies.push_back(enemy);
			this->activeEnemiesCount++;
		}

		// Attach the currentWave to our waves
		this->waves.push_back(currentWave);

		// Up the difficulty a bit maybe?
		//this->currentWaveEnemyCount += 1;
	}

}

void EnemyManager::startPulseLevel(enemySpawnPositions spawnPosVectors, float difficulty)
{
	this->startTime = Locator::getGameTime()->GetTime();
	this->timePassed = 0;
	this->activeEnemiesCount = 0;
	this->spawnInterval = 0.0f;
	this->waveInterval = 4.0f;
	this->currentWaveCount = 10;

	this->currentWaveEnemyCount.resize(10);
	for (int i = 0; i < this->currentWaveEnemyCount.size(); i++)
		this->currentWaveEnemyCount.at(i) = (8 + static_cast<int>(difficulty));
	//this->currentWaveEnemyCount.at(i) = (4 + static_cast<int>(1.5f * i));

	Wave* currentWave = nullptr;

	// Per wave
	for (int i = 0; i < this->currentWaveCount; i++) {
		currentWave = new Wave();

		// Per enemy
		for (int j = 0; j < this->currentWaveEnemyCount.at(i); j++) {
			// Create an enemy and attatch it to the wave.
			ActorObject* enemy = this->createEnemy(ENEMYTYPE::IMMOLATION, AIBEHAVIOR::STRAIGHTTOWARDS, spawnPosVectors);
			currentWave->enemies.push_back(enemy);
			this->activeEnemiesCount++;
		}

		// Attach the currentWave to our waves
		this->waves.push_back(currentWave);

		// Up the difficulty a bit maybe?
		//this->currentWaveEnemyCount += 1;
	}

}

void EnemyManager::cleanLevel()
{
	// Per wave
	for (auto &currentWave : this->waves) {

		for (size_t i = 0; i < currentWave->enemies.size(); i++) {
			currentWave->enemies[i]->cleanUp();
			delete currentWave->enemies[i];
		}
		// Since enemies are actors which SHOULD HAVE been added to the dynamicObjectsArray,
		// they'll be cleaned and deleted from there, so we only need to delete the 'Waves' here
		delete currentWave;
	}

	int popWavesQueue = waves.size();

	for (int i = 0; i < popWavesQueue; i++) {
		this->waves.pop_back();
	}
}

ActorObject* EnemyManager::createEnemy(ENEMYTYPE::TYPE enemyType, AIBEHAVIOR::KEY aiBehavior, enemySpawnPositions spawnPosVectors)
{
	/// D E C L A R A T I O N
	// GRAND OBJECT
	EnemyObject* enemyObject = nullptr;
	// COMPONENTS
	BlockComponent* graphicsComponent = nullptr;
	AIComponent* aiComponent = nullptr;
	InputComponent* input = nullptr;
	PhysicsComponent* physicsComponent = nullptr;
	EnemyAttackComponent* attackComponent = nullptr;
	// STATES
	EnemyAttackingState* attackState = nullptr;
	EnemyMovingState* moveState = nullptr;

	bool reGenerateRandom = true;
	int spawnLocation = 0;


	/// D E F I N I T I O N
	size_t ID = this->pGPS->newID();
	XMFLOAT3 scale(10.0f, 20.0f, 10.0f);
	XMFLOAT3 pos = { 0, 0, 0 };
	float spawnOffset = 0.0f;

	if (this->pulse) {
		spawnOffset = 700.0f;
	}

	else {
		spawnOffset = Locator::getRandomGenerator()->GenerateFloat(700.0f, 800.0f);
	}

	while (reGenerateRandom)
	{
		spawnLocation = Locator::getRandomGenerator()->GenerateInt(1, 4);

		switch (spawnLocation) {
		case 1:
		{
			if (spawnPosVectors.west.size() > 0) {
				spawnLocation = Locator::getRandomGenerator()->GenerateInt(0, (spawnPosVectors.west.size() - 1));
				pos = {
					(spawnPosVectors.west.at(spawnLocation).x - spawnOffset),
					scale.y,
					spawnPosVectors.west.at(spawnLocation).y
				};
				reGenerateRandom = false;
			}
			break;
		}
		case 2:
		{
			if (spawnPosVectors.south.size() > 0) {
				spawnLocation = Locator::getRandomGenerator()->GenerateInt(0, (spawnPosVectors.south.size() - 1));
				pos = {
					spawnPosVectors.south.at(spawnLocation).x,
					scale.y,
					(spawnPosVectors.south.at(spawnLocation).y - spawnOffset)
				};
				reGenerateRandom = false;
			}
			break;
		}
		case 3:
		{
			if (spawnPosVectors.east.size() > 0) {
				spawnLocation = Locator::getRandomGenerator()->GenerateInt(0, (spawnPosVectors.east.size() - 1));
				pos = {
					(spawnPosVectors.east.at(spawnLocation).x + spawnOffset),
					scale.y,
					spawnPosVectors.east.at(spawnLocation).y
				};
				reGenerateRandom = false;
			}
			break;
		}
		case 4:
		{
			if (spawnPosVectors.north.size() > 0) {
				spawnLocation = Locator::getRandomGenerator()->GenerateInt(0, (spawnPosVectors.north.size() - 1));
				pos = {
					spawnPosVectors.north.at(spawnLocation).x,
					scale.y,
					(spawnPosVectors.north.at(spawnLocation).y + spawnOffset)
				};
				reGenerateRandom = false;
			}
			break;
		}
		break;
		}
	}

	//if (spawnLocation == 1)
	//	pos = { -spawnOffset, scale.y, static_cast<float>(ARENADATA::GETarenaHeight() * 0.5) };

	//else if (spawnLocation == 2)
	//	pos = { static_cast<float>(ARENADATA::GETarenaWidth() * 0.5), scale.y, -spawnOffset };

	//else if (spawnLocation == 3)
	//	pos = { (static_cast<float>(ARENADATA::GETarenaWidth()) + spawnOffset), scale.y, static_cast<float>(ARENADATA::GETarenaHeight() * 0.5) };

	//else if (spawnLocation == 4)
	//	pos = { static_cast<float>(ARENADATA::GETarenaWidth() * 0.5), scale.y, (static_cast<float>(ARENADATA::GETarenaHeight()) + spawnOffset) };


	float speed = 180.0f;
	XMFLOAT3 velocity(speed, speed, speed);
	XMFLOAT4 enemyColor(1.0f, 0.0f, 0.0f, 0.3f);
	XMFLOAT3 rotation(0.0f, 0.0f, 0.0f);
	float immolationDamage = 3.0f;
	float immolationDuration = 0.3f;
	float immolationRange = 50.0f;
	
	// OBJECT
	enemyObject = new EnemyObject(
		ID, speed, pos, velocity, 
		this->pGPS, &this->players, 
		OBJECTTYPE::ENEMY
	);
	
	// COMPONENTS
	graphicsComponent = new BlockComponent(*this->pGPS, *enemyObject, enemyColor, scale, rotation);
	physicsComponent = new PhysicsComponent(*enemyObject, 20);
	aiComponent = new AIComponent(*enemyObject, aiBehavior);
	attackComponent = new ImmolationEnemyAttack(immolationDamage, immolationDuration, immolationRange, &this->activeEnemiesCount, *enemyObject);
	
	// STATES
	attackState = new EnemyAttackingState(*enemyObject, *aiComponent, *attackComponent);
	moveState = new EnemyMovingState(*enemyObject, *aiComponent, *attackState);

	
	// Make the enemy inactive
	enemyObject->setState(OBJECTSTATE::TYPE::DEAD);
	return enemyObject;
}

void EnemyManager::initialize(GamePlayState& pGPS, std::vector<ActorObject*> players)
{
	this->pGPS = &pGPS;
	this->players = players;
	this->activeEnemiesCount = 0;
	this->ramp = false;
	this->pulse = false;
}

void EnemyManager::update(GUIManager* GUI)
{
	// If there are any waves left on the current level
	if (this->waves.size() > 0) {

		// If the currentwave has any enemies left
		if (this->waves.front()->enemies.size() > 0) {

			// Update timePassed
			this->timePassed += Locator::getGameTime()->getDeltaTime();

			// If the spawnInterval is met
			if (this->timePassed > spawnInterval) {

				// Reset the timer
				this->timePassed = 0;

				// Grab the next enemy in line
				ActorObject* freshEnemy = this->waves.front()->enemies.front();
				// Remove his homelink
				this->waves.front()->enemies.pop_front();
				// Send him out into the real world and let him handle himself (gl hf bobby!)
				freshEnemy->setState(OBJECTSTATE::TYPE::ACTIVATED);
				(*this->pGPS->getDynamicObjects()).push_back(freshEnemy);

				GUI->pushEnemyElement(*this->pGPS->GETGUIObjects(), *this->pGPS->getGraphicsComponents(), this->pGPS->newID());

				//char msgbuf[20];
				//sprintf_s(msgbuf, "SPAWNED\n");
				//OutputDebugStringA(msgbuf);
			}
		}
		// No enemies in this wave? Move on to the next wave
		else if (this->timePassed > this->waveInterval) {
			this->timePassed = 0;
			
			// Ramping the time between waves
			if (this->ramp)
				this->waveInterval -= 1.0f;

			// Goodbye wave!
			delete this->waves.front();
			this->waves.pop_front();
		}

		else {
			this->timePassed += Locator::getGameTime()->getDeltaTime();
		}
	}
	// All waves have been spawned!
	else {
		// Has the player won? :O
		if (this->activeEnemiesCount < 1) {
			Locator::getGlobalEvents()->generateMessage(GLOBALMESSAGES::PLAYERWON);
		}
	}
}

void EnemyManager::cleanUp()
{
	this->cleanLevel();
}