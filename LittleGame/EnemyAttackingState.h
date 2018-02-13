#pragma once
#ifndef ENEMYATTACKINGSTATE_H
#define ENEMYATTACKINGSTATE_H

#include "EnemyState.h"
#include "AIComponent.h"

/* Example of State-Timeline
state(n)^
[2]	| 						    ATTACK PHASE 2
[1]	| 			ATTACK PHASE 1		0
[0]	|  MOVING			     					MOVING
	|-------------------------------------------------> t
*/

class EnemyObject;
class AIComponent;
class EnemyAttackComponent;

class EnemyAttackingState : public EnemyState
{
private:
	EnemyObject * pHead;
	AIComponent * pBrain;
	EnemyAttackComponent* attackComponent;

	float attackDuration;
	float attackDamage;

public:
	EnemyAttackingState(EnemyObject& pHead, AIComponent& pBrain, EnemyAttackComponent& attackComponent);
	void attack();
	virtual void executeBehavior();

};

#endif