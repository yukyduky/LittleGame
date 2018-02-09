#pragma once
#ifndef ENEMYATTACKCOMPONENT_H
#define ENEMYATTACKCOMPONENT_H

#include "Component.h"
#include "ActorObject.h"

class EnemyAttackComponent : public Component
{
protected:
	ActorObject * pHead = nullptr;
	float passedTime;
	float attackDuration;

public:
	virtual const size_t getID() = 0;
	virtual void receive(GameObject & obj, Message msg) = 0;
	virtual void update() = 0;
	virtual void cleanUp() = 0;

	virtual void attack() = 0;
};

#endif 
