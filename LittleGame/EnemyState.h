#pragma once
#ifndef ENEMYSTATE_H
#define ENEMYSTATE_H

/* Example of a State-Timeline for an enemy
state(n)^
	[2]	| 				push	    ATTACK PHASE 2	pop
	[1]	| 	push	ATTACK PHASE 1					pop
	[0]	|  MOVING			     						MOVING
		|-------------------------------------------------> t
*/

class EnemyState
{
private:

public:
	virtual void executeBehavior() = 0;

};

#endif