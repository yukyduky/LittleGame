#pragma once
#ifndef EXPLOSIONENEMYATTACK_H
#define EXPLOSIONENEMYATTACK_H

#include "EnemyAttackComponent.h"

class ExplosionEnemyAttack : public EnemyAttackComponent
{
private:


public:
	ExplosionEnemyAttack();

	virtual const size_t getID();
	virtual void receive(GameObject & obj, Message msg);
	virtual void update();
	virtual void cleanUp();

	virtual void attack();


};

#endif 
