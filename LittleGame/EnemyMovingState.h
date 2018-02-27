#pragma once
#ifndef ENEMYMOVINGSTATE_H
#define ENEMYMOVINGSTATE_H

#include "EnemyState.h"

/* Example of State-Timeline
state(n)^
[2]	| 						    ATTACK PHASE 2
[1]	| 			ATTACK PHASE 1		
[0]	|  MOVING			     					MOVING
	|-------------------------------------------------> t
*/

class EnemyObject;
class AIComponent;
class EnemyAttackingState;

class EnemyMovingState : public EnemyState
{
private:
	EnemyObject * pHead = nullptr;
	AIComponent * pBrain = nullptr;
	float attackRange = 0.0f;	// Fetched from Head's attackComponent

public:
	EnemyMovingState(EnemyObject& pHead, AIComponent& pBrain);
	virtual void executeBehavior();

};

#endif