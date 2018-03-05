#pragma once
#ifndef ENEMYATTACKCOMPONENT_H
#define ENEMYATTACKCOMPONENT_H

#include "Component.h"
#include "ActorObject.h"
#include "Locator.h"

class EnemyAttackComponent : public Component
{
protected:
	ActorObject * pHead = nullptr;
	std::vector<ActorObject*>* players;
	int* pActiveEnemiesCount = nullptr; // Correlates to the value 'activeEnemiesCount' inside EnemyManager.
	float passedTime;
	float attackDamage;
	float attackDuration;
	float attackRange;

public:
	virtual const size_t getID() = 0;
	virtual void receive(GameObject & obj, Message msg) = 0;
	virtual void update() = 0;
	virtual void cleanUp() = 0;

	virtual void attack() = 0;
	
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Returns true if it's time to attack, and false otherwise.
	2. Determines this with an internal timer which compares with attackDuration
	*/
	virtual bool timeToAttack() {
		this->passedTime += static_cast<float>(Locator::getGameTime()->getDeltaTime());
		if (this->passedTime > attackDuration) {
			this->passedTime = 0.0f;
			return true;
		}
		return false;
	};

	float GETattackDamage() {
		return this->attackDamage;
	}
	float GETattackDuration() {
		return this->attackDuration;
	}
	float GETattackRange() {
		return this->attackRange;
	}
};

#endif 
