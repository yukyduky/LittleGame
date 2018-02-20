#pragma once
#ifndef SWARMERENEMYATTACK_H
#define SWARMERENEMYATTACK_H

#include "EnemyAttackComponent.h"

class EnemyObject;

class SwarmerEnemyAttack : public EnemyAttackComponent
{
private:


public:
	SwarmerEnemyAttack(EnemyObject& pHead, int& activeEnemiesCount, float projectileDamage, float projectileDuration, float projectileRange);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Returns the id of the actor on which this component is attached to!
	*/
	virtual const size_t getID();
	virtual void receive(GameObject & obj, Message msg);
	virtual void update();
	virtual void cleanUp();

	virtual void attack();

};

#endif
