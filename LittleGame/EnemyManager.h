#pragma once
#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <deque>
#include "GameObject.h"
#include "ActorObject.h"
#include "AIComponent.h"
#include "LevelManager.h"
#include "GUIManager.h"


// Forward declaration to prevent double includes
class EndState;
class GamePlayState;

struct Wave {
	// Push to the back, pop from the front, [0] is the first enemy and [n] is the last enemy.
	std::deque<ActorObject*> enemies;
};

namespace ENEMYTYPE {
	enum TYPE {
		IMMOLATION,
		SIZE
	};
}

class EnemyManager
{
private:
	// Necessary since creation of actors is dependant on our std::vectors which rely in the GPS.
	GamePlayState * pGPS = nullptr;
	EndState * endState = nullptr;
	std::vector<ActorObject*> players;
	int activeEnemiesCount = 0;

	// Assumes that all the gameObjects are updated through this pointer, if 
	// it has since then been divided into several arrays, the pointer here should be to the Actors
	std::vector<GameObject*>* pGameObjectsArray = nullptr;

	// Push to the back, pop from the front, [0] is the first wave and [n] is the last wave.
	std::deque<Wave*> waves;
	int currentWaveCount = 0;
	int currentWaveSize = 0;
	double spawnInterval = 0;
	double waveInterval = 0;
	double timePassed = 0;
	double startTime = 0;

	void cleanLevel();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Creates an Actor, attaches necessary components and returns him to you!
	*/
	ActorObject* createEnemy(ENEMYTYPE::TYPE enemyType, AIBEHAVIOR::KEY aiBehavior, enemySpawnPositions spawnPosVectors);

public:
	EnemyManager();
	EnemyManager(GamePlayState& pGPS, std::vector<ActorObject*>& players);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Saves the pGPS as an internal pointer.
	*/
	void startLevel1(enemySpawnPositions spawnPosVectors);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Saves the pGPS as an internal pointer.
	*/
	void initialize(GamePlayState& pGPS, std::vector<ActorObject*> players);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Spawns enemies to dynamicObjects according to the spawnInterval and waves
	(If there are waves/enemies left).
	- Doesn't currently have any time in between waves.
	*/
	void update(GUIManager* GUI);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. No need to clean up objects if they are attatched to the GameObjects vector since they'll
	get cleaned up by the GPS.
	*/
	void cleanUp();

};






#endif 
