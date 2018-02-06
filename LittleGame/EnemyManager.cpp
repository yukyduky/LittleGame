#include "EnemyManager.h"
#include "ActorObject.h"
#include "GamePlayState.h"
#include "Locator.h"
#include "PhysicsComponent.h"
#include "BlockComponent.h"
#include "AIComponent.h"

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
	this->spawnInterval = 0.5;
	this->currentWaveCount = 3;
	this->currentWaveSize = 2;
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
		// they'll be cleaned and deleted from there, so we only need to delete the 'Waves' here
		delete currentWave;
	}
}

ActorObject* EnemyManager::createEnemy(ENEMYTYPE::TYPE)
{
	/*
	NOT FINISHED. Waiting for Static/Dynamic-objects 
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
	enemy->addComponent(physics);
	/* this->physicsListDynamic.push_back(physics); kanske om det behövs */

	// Input
	input = new AIComponent(*enemy, AIBEHAVIOR::STRAIGHTTOWARDS);

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
		if (this->waves.front()->enemies.size() > 0) {

			// Update timePassed
			timePassed += Locator::getGameTime()->GetTime() - startTime;

			// If the spawnInterval is met
			if (timePassed > spawnInterval) {

				// Reset the timer
				startTime = Locator::getGameTime()->GetTime();
				timePassed = 0;

				// Grab the next enemy in line
				// Remove his homelink
				// Send him out into the real world and let him handle himself (gl hf bobby!)
				
				ActorObject* freshEnemy = this->waves.front()->enemies.front();
				this->waves.front()->enemies.pop_front();
			//	this->pGPS->GetDynamicObjectsVector().push_back(freshEnemy);
				

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