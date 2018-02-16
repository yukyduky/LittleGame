#pragma once
#ifndef ENEMYSTATE_H
#define ENEMYSTATE_H

/* Example of a State-Timeline for an enemy
state(n)^
	[2]	| 						SOUND
	[1]	| 			OPTIONS				
	[0]	|  MAIN			     			MAIN
		|-------------------------------------------------> t
*/

class EnemyState
{
private:

public:
	virtual void executeBehavior() = 0;

};

#endif