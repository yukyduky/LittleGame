#include "EnemyManager.h"
#include "ActorObject.h"
#include "GamePlayState.h"
#include "Locator.h"
#include "PhysicsComponent.h"
#include "BlockComponent.h"
// #include "AIComponent.h"

EnemyManager::EnemyManager()
{
	this->pGPS = nullptr;
}

EnemyManager::EnemyManager(GamePlayState& pGPS)
{
	this->pGPS = &pGPS;
}

void EnemyManager::startLevel1()
{
	this->startTime = Locator::getGameTime()->GetTime();
	this->timePassed = 0;
	this->currentWaveCount = 5;
	this->currentWaveSize = 5;
	Wave* currentWave;

	// Per wave
	for (int i = 0; i < this->currentWaveCount; i++) {
		currentWave = new Wave();

		// Per enemy
		for (int j = 0; j < this->currentWaveSize; j++) {
			// Create an enemy and attatch it to the wave.
			ActorObject* enemy = this->createEnemy(ENEMYTYPE::IMMOLATION);
			currentWave->enemies.push_back(enemy);
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
		// they'll be cleaned and deleted from there.
		delete currentWave;
	}
}

ActorObject* EnemyManager::createEnemy(ENEMYTYPE::TYPE)
{
	/*
	Creation relies on:
	GamePlayState->arenaObjects.size for nextID();
	GamePlayState->physicsListDynamic
	GamePlayState->graphics
	&GamePlayState;
	*/

	ActorObject* enemy;
	BlockComponent* block;
	InputComponent* input;
	PhysicsComponent* physics;

	// Graphics
	XMFLOAT3 enemyScale(10.0f, 20.0f, 10.0f);
	XMFLOAT3 enemyPos(0.0f, 0.0f, 0.0f);	// Position is randomed!

	// Object
	enemy = new ActorObject(0);

	// Physics
	physics = new PhysicsComponent(*enemy);
	/* this->physicsListDynamic.push_back(physics); kanske om det behövs */

	// Input
	/* input = new AIComponent(ENUM::BEHAVIOR); */

	return enemy;
}

void EnemyManager::initialize(GamePlayState& pGPS)
{
	this->pGPS = &pGPS;
}

void EnemyManager::update()
{
	// If there are any waves left on the current level
	if (this->waves.size() > 0) {

		// If the currentwave has any enemies left
		if (this->waves.back()->enemies.size() > 0) {

			// Update timePassed
			timePassed += Locator::getGameTime()->GetTime() - startTime;

			// If the spawnInterval is met
			if (timePassed > spawnInterval) {

				// Reset the timer
				startTime = Locator::getGameTime()->GetTime();
				timePassed = 0;

				// Grab the next enemy in line
				// Pop him!
				// Send him out into the real world
				/*
				ActorObject* freshEnemy = this->currentWaves.front()->enemies.front();
				this->currentWaves.front()->enemies.pop_front;
				this->pGPS->GetDynamicObjectsVector().push_back(freshEnemy);
				*/

			}
		}
	}
}

void EnemyManager::cleanUp()
{
	this->cleanLevel();

}