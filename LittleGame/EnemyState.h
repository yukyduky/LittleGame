#pragma once
#ifndef ENEMYSTATE_H
#define ENEMYSTATE_H

/* Example of State-Timeline
state(n)^
	[2]	| 						    ATTACK PHASE 2
	[1]	| 			ATTACK PHASE 1		0
	[0]	|  MOVING			     					MOVING
		|-------------------------------------------------> t
*/

class EnemyState
{
private:


public:

	virtual void update() = 0;

};

#endif