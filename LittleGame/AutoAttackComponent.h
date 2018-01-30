#pragma once
#ifndef AUTOATTACKCOMPONENT_H_
#define AUTOATTACKCOMPONENT_H_

#include "AbilityComponent.h"

class AutoAttackComponent : public AbilityComponent
{
private:
	const size_t ID;
	float damage;
	float range;
	float energyCost;
	ABILITYTYPE::TYPE type;

public:
	AutoAttackComponent(GameObject& obj, float damage, float range, float energyCost, ABILITYTYPE::TYPE type);
	~AutoAttackComponent();

	virtual const size_t getID();
	virtual void receive(GameObject & obj, Message msg);
	virtual float GETdamage();
	virtual float GETrange();
	virtual float GETenergyCost();
	virtual float GETtype();
};


#endif