#pragma once
#ifndef IMMOLATIONENEMYATTACK_H
#define IMMOLATIONENEMYATTACK_H

#include "EnemyAttackComponent.h"

class EnemyObject;

class ImmolationEnemyAttack : public EnemyAttackComponent
{
private:
	// Saved Dynamic_casted head so that we don't need to dynamic cast each loop!
	EnemyObject * pHead2;

public:
	ImmolationEnemyAttack(EnemyObject& pHead, std::vector<ActorObject*>* players);

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
