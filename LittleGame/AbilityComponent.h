#pragma once
#ifndef ABILITYCOMPONENT_H
#define ABILITYCOMPONENT_H

#include "Component.h"
#include "Projectile.h"
#include "Locator.h"

enum class ABILITYTYPE {FIRE};

class AbilityComponent : public Component
{
protected:
	Projectile * pHead;

	float range = 10;
	float damage = 100;
	ABILITYTYPE type;

public:
	AbilityComponent(Projectile& pHead); 

	virtual const size_t getID();
	virtual void receive(GameObject & obj, Message msg);
	virtual void cleanUp();
};








#endif
