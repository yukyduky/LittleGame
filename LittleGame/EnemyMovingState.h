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

class EnemyMovingState : public EnemyState
{
private:

public:
	EnemyMovingState(EnemyObject& pHead, AIComponent& pBrain);
	void cleanUp();
	virtual void executeBehavior();

};

#endif