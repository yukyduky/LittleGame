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

EnemyManager::EnemyManager()
{
	this->pGPS = nullptr;
}

EnemyManager::EnemyManager(GamePlayState& pGPS, std::vector<ActorObject*> players)
{
	this->pGPS = &pGPS;
	this->players = players; 
}

void EnemyManager::startLevel1()
{
	this->startTime = Locator::getGameTime()->GetTime();
	this->timePassed = 0;
	this->spawnInterval = 0.1;
	this->currentWaveCount = 3;
	this->currentWaveSize = 2;
	int testScale = 1;
	Wave* currentWave;

	// Per wave
	for (int i = 0; i < this->currentWaveCount; i++) {
		currentWave = new Wave();

		// Per enemy
		for (int j = 0; j < this->currentWaveSize; j++) {
			// Create an enemy and attatch it to the wave.
			ActorObject* enemy = this->createEnemy(0.1*(testScale), ENEMYTYPE::IMMOLATION, AIBEHAVIOR::STRAIGHTTOWARDS);
			currentWave->enemies.push_back(enemy);
			testScale++;
		}

		// Attach the currentWave to our waves
		this->waves.push_back(currentWave);

		// Up the difficulty a bit maybe?
		this->currentWaveSize += 1;
	}
}

void EnemyManager::cleanLevel()
{
	// Per wave
	for (auto &currentWave : this->waves) {

		// Since enemies are actors which SHOULD HAVE been added to the dynamicObjectsArray,
		// they'll be cleaned and deleted from there, so we only need to delete the 'Waves' here
		delete currentWave;
	}
}

ActorObject* EnemyManager::createEnemy(float posScale, ENEMYTYPE::TYPE enemyType, AIBEHAVIOR::KEY aiBehavior)
{
	/// D E C L A R A T I O N
	// GRAND OBJECT
	EnemyObject* enemyObject;
	// COMPONENTS
	BlockComponent* graphicsComponent;
	AIComponent* aiComponent;
	InputComponent* input;
	PhysicsComponent* physicsComponent;
	EnemyAttackComponent* attackComponent;
	// STATES
	EnemyAttackingState* attackState;
	EnemyMovingState* moveState;


	/// D E F I N I T I O N
	size_t ID = this->pGPS->newID();
	XMFLOAT3 scale(10.0f, 20.0f, 10.0f);
	XMFLOAT3 pos((float)(ARENAWIDTH*posScale), scale.y, (float)(ARENAHEIGHT / 2 * posScale));
	float speed = 80;
	XMFLOAT3 velocity(speed, speed, speed);
	XMFLOAT4 enemyColor(10.0f, 0.0, 0.0f, 255.0f);
	XMFLOAT3 rotation(0, 0, 0);
	float immolationDamage = 30;
	float immolationDuration = 3;
	float immolationRange = 100;
	
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
	attackComponent = new ImmolationEnemyAttack(immolationDamage, immolationDuration, immolationRange, *enemyObject);
	
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
}

void EnemyManager::update()
{
	// If there are any waves left on the current level
	if (this->waves.size() > 0) {

		// If the currentwave has any enemies left
		if (this->waves.front()->enemies.size() > 0) {

			// Update timePassed
			timePassed += Locator::getGameTime()->getDeltaTime();

			// If the spawnInterval is met
			if (timePassed > spawnInterval) {

				// Reset the timer
				timePassed = 0;

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
		else {
			// Goodbye wave!
			delete this->waves.front();
			this->waves.pop_front();
		}
	}
}

void EnemyManager::cleanUp()
{
	this->cleanLevel();

}