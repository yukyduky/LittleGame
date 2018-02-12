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

class EnemyMovingState : public EnemyState
{
private:


public:
	virtual void update();

};

#endif