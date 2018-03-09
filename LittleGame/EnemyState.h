#pragma once
#ifndef ENEMYSTATE_H
#define ENEMYSTATE_H

/* Example of a State-Timeline for an enemy
state(n)^
	[2]	| 						THIRD
	[1]	| 			SECOND				
	[0]	|  FIRST			     			FIRST
		|-------------------------------------------------> t
*/

class EnemyObject;
class AIComponent;

class EnemyState
{
protected:
	EnemyObject * pHead = nullptr;
	AIComponent * pBrain = nullptr;
	float attackRange = 0.0f;	// Fetched from Head's attackComponent

public:
	EnemyState(EnemyObject& pHead, AIComponent& pBrain);
	virtual void cleanUp() = 0;
	virtual void executeBehavior() = 0;
};

#endif