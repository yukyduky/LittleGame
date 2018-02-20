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
struct ArrayList;

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
	ArrayList* allSwarmers;



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







// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ STRUCT
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ STRUCT
struct ArrayList
{
	// Necessary structs
	struct ArrayNode;	// Forward declaration since Alive/Dead/Array all reside within eachother
	struct AliveNode {
		ArrayNode*	 index = nullptr;
		AliveNode*	 back = nullptr;
		AliveNode*	 forward = nullptr;
	};
	struct DeadNode {
		ArrayNode*	 index = nullptr;
		DeadNode*	 back = nullptr;
		DeadNode*	 forward = nullptr;
	};
	struct ArrayNode {
		EnemyObject* obj = nullptr;
		AliveNode*	 alive = nullptr;
		DeadNode*	 dead = nullptr;
	};

	// Variables
	int size = -1;
	ArrayNode* mainArray = nullptr;
	AliveNode* firstAlive = nullptr;
	DeadNode* firstDead = nullptr;

	// Functions
	void initialize(std::vector<EnemyObject*> allObjectsToBeInserted) {
		// Prep some values
		this->size = allObjectsToBeInserted.size();
		this->mainArray = new ArrayNode[this->size];	// Allocate the entire array

														// Add the first one
		this->mainArray[0].obj = allObjectsToBeInserted[0];
		this->firstAlive = new AliveNode();
		this->firstAlive->index = &this->mainArray[0];	// Connect Alive->Array
		this->mainArray[0].alive = this->firstAlive;	// Connect Array->Alive

		AliveNode* stepper = this->firstAlive;
		// Array is done, now connect all the pieces up until the last one
		for (int i = 1; i < (this->size - 1); i++) {
			// Connect AliveList
			stepper->forward = new AliveNode();		// Create forward and connect
			stepper->forward->back = stepper;		// back-><-front
			stepper->index = &this->mainArray[i];		// Connect List->Array

														// Connect Array
			this->mainArray[i].obj = allObjectsToBeInserted[i];	// Array->Obj
			this->mainArray[i].alive = stepper;					// Array->List

																// Step forward
			stepper = stepper->forward;
		}

		// Add the last one
		stepper->index = &this->mainArray[this->size];
		this->mainArray[this->size].obj = allObjectsToBeInserted[this->size];
		this->mainArray[this->size].alive = stepper;
	}
	void remove(int index) {

	}
	void find(int index) {

	}
	void cleanUp() {

		for (int i = 0; i < this->size; i++) {
			// We only need to delete the 'newed' data, so we don't really care about the links between the data.
			if (this->mainArray[i].dead != nullptr) {
				delete this->mainArray[i].dead;
				this->mainArray[i].dead = nullptr;
			}
			if (this->mainArray[i].alive != nullptr) {
				delete this->mainArray[i].alive;
				this->mainArray[i].dead = nullptr;
			}
			// All objects clean themselves, we're only using pointers here.
		}

		delete this->mainArray;
	}
};
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ STRUCT
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ STRUCT


#endif 
