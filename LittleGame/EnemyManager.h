#pragma once
#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <deque>
#include "GameObject.h"
#include "ActorObject.h"
#include "AIComponent.h"

/* ---------------------------------------------------------------------------
	If you're here to look at anything that is NOT the swarmers, i highly recommend 
	minimizing EVERYTHING that is not the EnemyManager class
---------------------------------------------------------------------------- */


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
class ArrayList 
{
private:
	// This class is technically not done, since it can be added upon if we want to dynamically
	// add swarmers to it, which we don't need or want to do atm.

	// Variables
	int size = -1;
	XMFLOAT3 averagePosition = { -1, -1, -1 };
	ArrayNode* mainArray = nullptr;
	AliveNode* firstAlive = nullptr;
	DeadNode* firstDead = nullptr;

public:

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
		// Array is done, now connect all the pointers up until the last one
		for (int i = 1; i < (this->size); i++) {
			// Connect AliveList
			stepper->forward = new AliveNode();		// Create forward and connect
			stepper->forward->back = stepper;		// back-><-front
			stepper->index = &this->mainArray[i];		// Connect List->Array

			// Step forward
			stepper = stepper->forward;

			// Connect Array
			this->mainArray[i].obj = allObjectsToBeInserted[i];	// Array->Obj
			this->mainArray[i].alive = stepper;					// Array->List
		}

		// Add the last one
		stepper->index = &this->mainArray[this->size-1];
	}
	void update() {
		// Update the averagePosition
		XMFLOAT3 averagePosition = { 0, 0, 0 };
		XMFLOAT3 currentPosition = { 0, 0, 0 };
		AliveNode* stepper = this->firstAlive;

		while (stepper->forward != nullptr) {
			// Add up all of them! (except the last one)
			currentPosition = stepper->index->obj->GETPosition();
			averagePosition.x += currentPosition.x;
			averagePosition.y += currentPosition.y;
			averagePosition.z += currentPosition.z;

			stepper = stepper->forward;
		}

		// Add up the last one
		currentPosition = this->mainArray[0].obj->GETPosition();
		averagePosition.x += currentPosition.x;
		averagePosition.y += currentPosition.y;
		averagePosition.z += currentPosition.z;

		// Divide down
		averagePosition.x /= this->size;
		averagePosition.y /= this->size;
		averagePosition.z /= this->size;
	}
	XMFLOAT3* getAveragePosition() {
		return &this->averagePosition;
	}
	EnemyObject* find(int index) {
		if (this->mainArray[index].alive != nullptr) {
			return this->mainArray[index].obj;
		}
		return nullptr;
	}
	AliveNode* getFirst() {
		return this->firstAlive;
	}
	void insert() {
		// NOT IMPLEMENTED AS IT IS NOT NEEDED OR WANTED ATM.
	}
	void remove(int index) {
		if (this->firstAlive != nullptr) {
			// To remove the AliveNode, connect it's 'back' and 'forward' pointers
			AliveNode* back = this->mainArray[index].alive->back;
			AliveNode* forward = this->mainArray[index].alive->forward;
			back->forward = forward;
			forward->back = back;

			// Also clean!
			delete this->mainArray[index].alive;
			this->mainArray[index].alive = nullptr;
			this->size--;
		}
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

class EnemyManager
{
private:
	// Necessary since creation of actors is dependant on our std::vectors which rely in the GPS.
	GamePlayState * pGPS = nullptr;
	std::vector<ActorObject*> players;	// Only players[0] here.
	std::vector<GameObject*>* pGameObjectsArray = nullptr;
	int activeEnemiesCount = 0;

	// Relevant to grid
	int swarmerCount = -1;
	ArrayList* pSwarmers = nullptr;


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
	EnemyObject* createMinion(ENEMYTYPE::TYPE enemyType, AIBEHAVIOR::KEY aiBehavior);
	EnemyObject* createSwarmer();

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
