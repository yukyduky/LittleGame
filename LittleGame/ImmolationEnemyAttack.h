#pragma once
#ifndef IMMOLATIONENEMYATTACK_H
#define IMMOLATIONENEMYATTACK_H

#include "EnemyAttackComponent.h"

class EnemyObject;

class ImmolationEnemyAttack : public EnemyAttackComponent
{
private:
	// Correlates to the value 'activeEnemiesCount' inside EnemyManager.
	int* pActiveEnemiesCount = nullptr;

public:
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	*/
	ImmolationEnemyAttack(float damage, float attackDuration, float attackRange, int* pActiveEnemiesCount, EnemyObject& pHead);

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
