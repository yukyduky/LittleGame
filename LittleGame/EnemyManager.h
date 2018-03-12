#pragma once
#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include "GameObject.h"
#include "ActorObject.h"
#include "AIComponent.h"
#include "EnemyObject.h"
#include "EnemyIncludes.h"
#include "LevelManager.h"
#include "GUIManager.h"

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
	size_t		 arrayIndex = 0;
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
	XMFLOAT3 averagePosition = { 0, 0, 0.0001f };
	ArrayNode* mainArray = nullptr;
	AliveNode* firstAlive = nullptr;
	DeadNode* firstDead = nullptr;

	void activateIndex(size_t index) {
		// Check if it has already been activated
		if (this->mainArray[index].alive == nullptr) {

			AliveNode* freshNode = new AliveNode();
			this->mainArray[index].alive = freshNode;

			// If this is going to be the only one alive
			if (this->firstAlive == nullptr) {
				this->firstAlive = this->mainArray[index].alive;
			}
			// If we're activating one earlier than the current firstAlive
			else if (index < this->firstAlive->index->arrayIndex) {
				this->firstAlive = this->mainArray[index].alive;
			}
			else {
				// Activate it
				bool found = false;
				
				// Connect behind
				int stepper = index - 1;
				while (stepper > -1 && !found) {
					AliveNode* toBeBack = this->mainArray[stepper].alive;

					if (toBeBack != nullptr) {
						found = true;
						// Connect the freshNode to it's proper back and front
						freshNode->back = toBeBack;

						// Connect to front if it exists
						if (toBeBack->forward != nullptr) {
							freshNode->forward = toBeBack->forward;
						}

						// Replace the old links
						freshNode->back->forward = freshNode;

						// Connect to it's forward if it exists
						if (freshNode->forward != nullptr) {
							freshNode->forward->back = freshNode;
						}
					}
					stepper--;
				}
			}
			

			// Connect to the array
			freshNode->index = &this->mainArray[index];
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
		XMFLOAT3 averagePosition_ = { 0, 0, 0.0001f };
		XMFLOAT3 currentPosition = { 0, 0, 0 };
		AliveNode* stepper = this->firstAlive;

		if (stepper != nullptr) {
			while (stepper->forward != nullptr) {
				// Add up all of them! (except the last one)
				currentPosition = stepper->index->obj->GETPosition();
				averagePosition_.x += currentPosition.x;
				averagePosition_.y += currentPosition.y;
				averagePosition_.z += currentPosition.z;

				stepper = stepper->forward;
			}

			// Add up the last one
			currentPosition = stepper->index->obj->GETPosition();
			averagePosition_.x += currentPosition.x;
			averagePosition_.y += currentPosition.y;
			averagePosition_.z += currentPosition.z;

			// We'd rather multiply than divide
			float optimizer = 1.0 / this->count;

			// Divide down
			averagePosition_.x *= optimizer;
			averagePosition_.y *= optimizer;
			averagePosition_.z *= optimizer;

			this->averagePosition = averagePosition_;
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
		if (swarmerID < this->capacity) {
			this->activateIndex(swarmerID);
		}
		else {
			// You've initialized this class twice, don't do that.
			assert(false);
		}
	}
	void remove(int index) {
		if (this->count > 0) {
			AliveNode* nodeToBeRemoved = this->mainArray[index].alive;
			if (nodeToBeRemoved != nullptr) {
				if (this->firstAlive != nullptr) {
					// To remove the AliveNode, connect it's 'back' and 'forward' pointers
					AliveNode* back = nodeToBeRemoved->back;
					AliveNode* forward = nodeToBeRemoved->forward;

					// If we're deleting the first one
					if (nodeToBeRemoved == this->firstAlive) {
						// And we have something in front of us
						if (nodeToBeRemoved->forward != nullptr) {
							// Make what's in front of us the firstAlive node
							this->firstAlive = nodeToBeRemoved->forward;
							// It 
							this->firstAlive->back = nullptr;
						}
						// And nothing ahead, we were the only node left
						else {
							this->firstAlive = nullptr;
						}
					}
					// nodeToBeRemoved definitely has a node behind itself, but not necessarily one ahead.
					else {
						// It does have one ahead
						if (forward != nullptr) {
							// So it has one ahead and back
							forward->back = back;
							back->forward = forward;
						}
						// Check behind
						else if (back != nullptr) {
							// Remove link so that 'back' has nothing in front of itself
							back->forward = nullptr;
						}
					}

					// Also clean!
					delete this->mainArray[index].alive;
					this->mainArray[index].alive = nullptr;
					this->count--;
					Locator::getGameTime()->UpdateFrameTime();
				}
			}
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
				this->mainArray[i].alive = nullptr;
			}
			// All objects clean themselves, we're only using pointers here.
		}
		delete this->mainArray;
		*&this->mainArray = nullptr;
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
	std::vector<int> currentWaveMinionCount;
	std::vector<int> currentWaveSwarmerCount;
	std::vector<int> currentWaveChargerCount;
	float spawnInterval = 0.0f;
	float waveInterval = 0.0f;
	int minionCount = 0;
	int chargerCount = 0;
	float timePassed = 0.0f;
	float startTime = 0.0f;

	bool ramp = false;
	bool pulse = false;

	void cleanLevel();

	EnemyObject* createEnemy(ENEMYTYPE::TYPE enemyType, AIBEHAVIOR::KEY aiBehavior, enemySpawnPositions spawnPosVectors) {
		EnemyObject* newEnemy;

		switch(enemyType) {
		case ENEMYTYPE::SWARMER: 
			newEnemy = this->createSwarmer(spawnPosVectors);
			break;

		case ENEMYTYPE::IMMOLATION:
			newEnemy = this->createMinion(spawnPosVectors);
			break;
		default:
			newEnemy = this->createMinion(spawnPosVectors);
			break;

		}
		/// Upgrade depending on players choices (if there are any)
		Locator::getStatsHeader();
		newEnemy;

		return newEnemy;
	}

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Creates an Actor, attaches necessary components and returns him to you!
	*/
	EnemyObject* createCharger(enemySpawnPositions spawnPosVectors);
	EnemyObject* createSwarmer(enemySpawnPositions spawnPosVectors);
	EnemyObject* createMinion(enemySpawnPositions spawnPosVectors);
	EnemyObject* createBoss(ENEMYTYPE::TYPE enemyType, AIBEHAVIOR::KEY aiBehavior);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Returns an XMFLOAT3vector where [0] is the spawnPosition and [1] is the opening in the wall.
	*/
	std::vector<XMFLOAT3> generateEnemySpawnPositions(enemySpawnPositions spawnPosVectors, XMFLOAT3 scale);

public:
	EnemyManager();
	EnemyManager(GamePlayState& pGPS, std::vector<ActorObject*> players);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Saves the pGPS as an internal pointer.
	*/
	void startStandardLevel(enemySpawnPositions spawnPosVectors, float difficulty);
	void startRampLevel(enemySpawnPositions spawnPosVectors, float difficulty);
	void startPulseLevel(enemySpawnPositions spawnPosVectors, float difficulty);

	void startBossLevel();

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
	void update(GUIManager* GUI);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. No need to clean up objects if they are attatched to the GameObjects vector since they'll
	get cleaned up by the GPS.
	*/
	void cleanUp();

};





#endif 
