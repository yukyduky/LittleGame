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

	size_t cooldown = 0;
	float range = 0;
	float damage = 0;
	ABILITYTYPE type;

public:
	AbilityComponent(Projectile& pHead); 

	virtual const size_t getID();
	virtual void receive(GameObject & obj, Message msg);
	virtual void cleanUp();
};








#endif
