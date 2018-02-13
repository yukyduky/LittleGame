#pragma once
#ifndef IMMOLATIONENEMYATTACK_H
#define IMMOLATIONENEMYATTACK_H

#include "EnemyAttackComponent.h"

class EnemyObject;

class ImmolationEnemyAttack : public EnemyAttackComponent
{
private:


public:
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	WARNING: THIS CLASS IS SET ONTO AN ENEMYSTATE WHICH DEALS WITH IT.
	- This constructor does not attach itself onto an enemyobject, rather
	it should be given to the state which should use it..
	*/
	ImmolationEnemyAttack(float damage, float attackDuration, float attackRange, EnemyObject& pHead);

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
