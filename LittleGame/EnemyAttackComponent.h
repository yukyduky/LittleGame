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
	float damage;
	float passedTime;
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
	2. Not complex, just peak it!
	*/
	virtual bool timeToAttack() {
		this->passedTime += Locator::getGameTime()->getDeltaTime();
		if (this->passedTime > attackDuration) {
			this->passedTime = 0;
			this->pHead->setState(OBJECTSTATE::TYPE::ACTIVATED);
			return true;
		}
		return false;
	};
};

#endif 
