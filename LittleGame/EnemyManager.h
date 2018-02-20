#pragma once
#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <deque>
#include "GameObject.h"
#include "ActorObject.h"
#include "AIComponent.h"


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

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ CLASS
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ CLASS

class EnemyManager
{
private:
	// Necessary since creation of actors is dependant on our std::vectors which rely in the GPS.
	GamePlayState * pGPS;
	EndState * endState;
	std::vector<ActorObject*> players;
	std::vector<GameObject*>* pGameObjectsArray = nullptr;
	int activeEnemiesCount = 0;

	// Relevant to grid
	int swarmerCount = -1;



	// Push to the back, pop from the front, [0] is the first wave and [n] is the last wave.
	std::deque<Wave*> waves;
	int currentWaveCount;
	int currentWaveSize;
	double spawnInterval;
	double waveInterval;
	double timePassed;
	double startTime;

	void cleanLevel();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Creates an Actor, attaches necessary components and returns him to you!
	*/
	EnemyObject* createEnemy(ENEMYTYPE::TYPE enemyType, AIBEHAVIOR::KEY aiBehavior);
	EnemyObject* createClusterer();

public:
	EnemyManager();
	EnemyManager(GamePlayState& pGPS, std::vector<ActorObject*> players);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Saves the pGPS as an internal pointer.
	*/
	void startLevel1();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Saves the pGPS as an internal pointer.
	*/
	void initialize(GamePlayState& pGPS, std::vector<ActorObject*> players);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Spawns enemies to dynamicObjects according to the spawnInterval and waves
	(If there are waves/enemies left).
	- Doesn't currently have any time in between waves.
	*/
	void update();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. No need to clean up objects if they are attatched to the GameObjects vector since they'll
	get cleaned up by the GPS.
	*/
	void cleanUp();

};



#endif 
