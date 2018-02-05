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

	//Can changes this into a struct
	//These are all assigned in the subComponents
	size_t cooldown = 0;
	float range = 0;
	float damage = 0;
	ABILITYTYPE type;
	float speed = 0;

public:
	AbilityComponent(Projectile& pHead); 

	virtual const size_t getID();
	virtual void receive(GameObject & obj, Message msg);
	virtual void update() = 0;
	virtual void cleanUp();
};








#endif
