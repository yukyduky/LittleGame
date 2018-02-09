#pragma once
#ifndef EXPLOSIONENEMYATTACK_H
#define EXPLOSIONENEMYATTACK_H

#include "EnemyAttackComponent.h"

class ExplosionEnemyAttack : public EnemyAttackComponent
{
private:


public:
	ExplosionEnemyAttack(ActorObject& pHead);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Returns the id of the actor on which this component is attached to!
	*/
	virtual const size_t getID();
	virtual void receive(GameObject & obj, Message msg);
	virtual void update();
	virtual void cleanUp();

	virtual void attack();


};

#endif 
