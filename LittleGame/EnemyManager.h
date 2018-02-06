#pragma once
#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <deque>
#include "GameObject.h"
#include "ActorObject.h"

// Forward declaration to prevent double includes
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
	GamePlayState * pGPS;

	// Assumes that all the gameObjects are updated through this pointer, if 
	// it has since then been divided into several arrays, the pointer here should be to the Actors
	std::vector<GameObject*>* pGameObjectsArray = nullptr;

	// Push to the back, pop from the front, [0] is the first wave and [n] is the last wave.
	std::deque<Wave*> waves;
	int currentWaveCount;
	int currentWaveSize;
	double spawnInterval;
	double timePassed;
	double startTime;

	void cleanLevel();
	ActorObject* createEnemy(ENEMYTYPE::TYPE);

public:
	EnemyManager();
	EnemyManager(GamePlayState& pGPS);


	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Saves the pGPS as an internal pointer.
	*/
	void startLevel1();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Saves the pGPS as an internal pointer.
	*/
	void initialize(GamePlayState& pGPS);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. 
	*/
	void update();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. No need to clean up objects if they are attatched to the GameObjects vector since they'll
	get cleaned up by the GPS.
	*/
	void cleanUp();

};






#endif 
