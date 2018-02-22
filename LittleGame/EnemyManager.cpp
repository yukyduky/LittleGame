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
#include "EndState.h"

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
	this->endState = new EndState();
	this->activeEnemiesCount = 0;
}

void EnemyManager::startLevel1()
{
	this->startTime = Locator::getGameTime()->GetTime();
	this->timePassed = 0;
	this->activeEnemiesCount = 0;
	this->spawnInterval = 0.2;
	this->waveInterval = 5;
	this->currentWaveCount = 4;
	this->currentWaveSize = 20;
	Wave* currentWave = nullptr;

	// Per wave
	for (int i = 0; i < this->currentWaveCount; i++) {
		currentWave = new Wave();

		// Per enemy
		for (int j = 0; j < this->currentWaveSize; j++) {
			// Create an enemy and attatch it to the wave.
			ActorObject* enemy = this->createEnemy(ENEMYTYPE::IMMOLATION, AIBEHAVIOR::STRAIGHTTOWARDS);
			currentWave->enemies.push_back(enemy);
			this->activeEnemiesCount++;
		}

		// Attach the currentWave to our waves
		this->waves.push_back(currentWave);

		// Up the difficulty a bit maybe?
		this->currentWaveSize += 1;
	}

	// I couldn't figure out why, but the above loop creates 1 less enemy than it claims to.
	this->activeEnemiesCount--;
}

void EnemyManager::cleanLevel()
{
	// Per wave
	for (auto &currentWave : this->waves) {

		for (int i = 0; i < currentWave->enemies.size(); i++) {
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

ActorObject* EnemyManager::createEnemy(ENEMYTYPE::TYPE enemyType, AIBEHAVIOR::KEY aiBehavior)
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


	/// D E F I N I T I O N
	size_t ID = this->pGPS->newID();
	XMFLOAT3 scale(10.0f, 20.0f, 10.0f);
	XMFLOAT3 pos = { 0, 0, 0 };

	int spawnLocation = Locator::getRandomGenerator()->GenerateInt(1, 4);
	float spawnOffset = Locator::getRandomGenerator()->GenerateFloat(400, 500);

	if (spawnLocation == 1)
		pos = { -spawnOffset, scale.y, static_cast<float>(ARENAHEIGHT * 0.5) };

	else if (spawnLocation == 2)
		pos = { static_cast<float>(ARENAWIDTH * 0.5), scale.y, -spawnOffset };

	else if (spawnLocation == 3)
		pos = { (static_cast<float>(ARENAWIDTH) + spawnOffset), scale.y, static_cast<float>(ARENAHEIGHT * 0.5) };

	else if (spawnLocation == 4)
		pos = { static_cast<float>(ARENAWIDTH * 0.5), scale.y, (static_cast<float>(ARENAHEIGHT) + spawnOffset) };


	float speed = 180;
	XMFLOAT3 velocity(speed, speed, speed);
	XMFLOAT4 enemyColor(1.0f, 0.0, 0.0f, 0.3f);
	XMFLOAT3 rotation(0, 0, 0);
	float immolationDamage = 3;
	float immolationDuration = 0.3;
	float immolationRange = 80;
	
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
	this->endState = new EndState();
	this->activeEnemiesCount = 0;
}

void EnemyManager::update()
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

				char msgbuf[20];
				sprintf_s(msgbuf, "SPAWNED\n");
				OutputDebugStringA(msgbuf);
			}
		}
		// No enemies in this wave? Move on to the next wave
		else if (this->timePassed > this->waveInterval) {
			this->timePassed = 0;

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
			StateManager::pushState(this->endState);
		}
	}
}

void EnemyManager::cleanUp()
{
	this->cleanLevel();
}