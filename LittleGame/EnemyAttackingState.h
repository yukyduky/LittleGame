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
	EnemyObject * pHead = nullptr;
	AIComponent * pBrain = nullptr;
	EnemyAttackComponent* attackComponent = nullptr;

	float attackDamage = 0.0f;		// Not really needed, used to avoid "long" 'get->get->get' calls
	float attackDuration = 0.0f;	//
	float attackRange = 0.0f;		//

public:
	EnemyAttackingState(EnemyObject& pHead, AIComponent& pBrain, EnemyAttackComponent& attackComponent);
	void attack();
	virtual void executeBehavior();

	float GETattackDamage();
	float GETattackDuration();
	float GETattackRange();
	
};

#endif