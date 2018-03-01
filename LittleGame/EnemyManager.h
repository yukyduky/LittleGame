#pragma once
#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "GameObject.h"
#include "ActorObject.h"
#include "AIComponent.h"
#include "EnemyObject.h"
#include "EnemyIncludes.h"

/* ---------------------------------------------------------------------------
	If you're here to look at anything that is NOT the swarmers, i highly recommend 
	minimizing EVERYTHING that is not the EnemyManager class
---------------------------------------------------------------------------- */



// Forward declaration to prevent double includes
class GamePlayState;
class Grid;

struct Wave {
	// Push to the back, pop from the front, [0] is the first enemy and [n] is the last enemy.
	std::deque<EnemyObject*> enemies;
};

struct ArrayNode;
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
	/*
	The ArrayList uses a combination of two triple linked lists and an array to
	achieve O(1)-time in Remove & Find.

	*/
	// This class can be added upon if we want to dynamically
	// add swarmers to it, which we don't need or want to do atm.

	// Variables
	int capacity = -1;
	int count = 0;
	int toBeActivated = 0;
	XMFLOAT3 averagePosition = { -1, -1, -1 };
	ArrayNode* mainArray = nullptr;
	AliveNode* firstAlive = nullptr;
	DeadNode* firstDead = nullptr;

	void activateIndex(size_t index) {
		// Check if it has already been activated
		if (this->mainArray[index].alive == nullptr) {
			// Activate it
			bool found = false;
			AliveNode* freshNode = new AliveNode();

			// Connect behind
			int stepper = index;
			while (stepper > -1 && !found) {
				AliveNode* toBeBack = this->mainArray[stepper].alive;

				if (toBeBack != nullptr) {
					found = true;
					// Connect the freshNode to it's proper back and front
					freshNode->back = toBeBack;
					freshNode->forward = toBeBack->forward;

					// Replace the old links
					freshNode->back->forward = freshNode;

					// Connect to it's forward if it exists
					if (freshNode->forward != nullptr) {
						freshNode->forward->back = freshNode;
					}
				}

				stepper--;
			}

			// Connect to the array
			freshNode->index = &this->mainArray[index];
			this->mainArray[index].alive = freshNode;

			if (this->firstAlive == nullptr) {
				this->firstAlive = freshNode;
			}

			this->count++;
			/// Connect front will never occur if we always activate through toBeActivated
		}
	}

public:

	void initialize(std::vector<EnemyObject*> allObjectsToBeInserted) {
		// Prep some values
		this->capacity = allObjectsToBeInserted.size();
		this->mainArray = new ArrayNode[this->capacity];	// Allocate the entire array

		for (int i = 0; i < this->capacity; i++) {
			this->mainArray[i].obj = allObjectsToBeInserted[i];
		}

		/// LEAVING THIS HERE INCASE I HAVE FORGOTTEN SOMETHING WITH THE SOLUTION ABOVE
		//// Add the first one
		//this->mainArray[0].obj = allObjectsToBeInserted[0];0
		//this->firstAlive = new AliveNode();
		//this->firstAlive->index = &this->mainArray[0];	// Connect Alive->Array
		//this->mainArray[0].alive = this->firstAlive;	// Connect Array->Alive

		//AliveNode* stepper = this->firstAlive;
		//// Array is done, now connect all the pointers up until the last one
		//for (int i = 1; i < (this->capacity); i++) {
		//	// Connect AliveList
		//	stepper->forward = new AliveNode();		// Create forward and connect
		//	stepper->forward->back = stepper;		// back-><-front
		//	stepper->index = &this->mainArray[i];		// Connect List->Array

		//	// Step forward
		//	stepper = stepper->forward;

		//	// Connect Array
		//	this->mainArray[i].obj = allObjectsToBeInserted[i];	// Array->Obj
		//	this->mainArray[i].alive = stepper;					// Array->List
		//}

		//// Add the last one
		//stepper->index = &this->mainArray[this->capacity - 1];
	}
	void update() {
		// Update the averagePosition
		XMFLOAT3 averagePosition = { 0, 0, 0 };
		XMFLOAT3 currentPosition = { 0, 0, 0 };
		AliveNode* stepper = this->firstAlive;

		if (stepper != nullptr) {
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

			// We'd rather multiply than divide
			float optimizer = 1.0 / this->count;

			// Divide down
			averagePosition.x *= optimizer;
			averagePosition.y *= optimizer;
			averagePosition.z *= optimizer;

			this->averagePosition = averagePosition;
		}
	}
	XMFLOAT3 getAveragePosition() {
		return this->averagePosition;
	}
	EnemyObject* find(int index) {
		if (this->mainArray[index].alive != nullptr) {
			return this->mainArray[index].obj;
		}
		return nullptr;
	}
	AliveNode* getFirst() {
		if (this->firstAlive == nullptr)
			return nullptr;
		return this->firstAlive;
	}
	void activateNext() {
		int index = this->toBeActivated++;

		this->activateIndex(index);
	}
	void activateMe(size_t swarmerID) {
		this->activateIndex(swarmerID);
	}
	void remove(int index) {
		if (this->firstAlive != nullptr) {
			// To remove the AliveNode, connect it's 'back' and 'forward' pointers
			AliveNode* back = this->mainArray[index].alive->back;
			AliveNode* forward = this->mainArray[index].alive->forward;

			
			if (back != nullptr) {
				back->forward = forward;
			}
			if (forward != nullptr) {
				forward->back = back;
			}
				
			// If we're deleting the first one
			if (this->mainArray[index].alive == this->firstAlive) {
				if (this->mainArray[index].alive->forward != nullptr) {
					this->firstAlive = this->mainArray[index].alive->forward;
				}
				else {
					this->firstAlive = nullptr;
				}
				
			}

			// Also clean!
			delete this->mainArray[index].alive;
			this->mainArray[index].alive = nullptr;
			this->count--;
		}
	}
	void cleanUp() {

		for (int i = 0; i < this->capacity; i++) {
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
	Grid* pGrid = nullptr;
	size_t swarmerIDs = 0;

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
	2. Checks if all of the enemies has died.
	3. Updates internal arrayList & grid.
	*/
	void update();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. No need to clean up objects if they are attatched to the GameObjects vector since they'll
	get cleaned up by the GPS.
	*/
	void cleanUp();

};





#endif 
