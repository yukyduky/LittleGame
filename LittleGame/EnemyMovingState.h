#pragma once
#ifndef ENEMYMOVINGSTATE_H
#define ENEMYMOVINGSTATE_H

#include "EnemyState.h"

/* Example of State-Timeline
state(n)^
[2]	| 						    ATTACK PHASE 2
[1]	| 			ATTACK PHASE 1		0
[0]	|  MOVING			     					MOVING
|-------------------------------------------------> t
*/

class EnemyObject;
class AIComponent;
class EnemyAttackingState;

class EnemyMovingState : public EnemyState
{
private:
	EnemyObject * pHead;
	AIComponent * pBrain;
	float attackRange;	// Fetched from Head's attackComponent
	EnemyAttackingState* attackingStateTemplate;	// Used instead of 'new' each frame

public:
	EnemyMovingState(EnemyObject& pHead, AIComponent& pBrain, EnemyAttackingState& attackState);
	virtual void executeBehavior();

};

#endif