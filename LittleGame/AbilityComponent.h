#pragma once
#ifndef ABILITYCOMPONENT_H_
#define ABILITYCOMPONENT_H_

#include "Component.h"
#include <DirectXMath.h>

struct Message;

namespace ABILITYTYPE {
	enum TYPE {FIRE, SIZE};
}

class AbilityComponent : public Component
{
protected:
	float damage;
	float range;
	float energyCost;
	ABILITYTYPE::TYPE type;
public:
	AbilityComponent(GameObject* pHead);

	virtual const size_t getID() = 0;
	virtual void receive(GameObject & obj, Message msg) = 0;
	virtual float GETdamage() = 0;
	virtual float GETrange() = 0;
	virtual float GETenergyCost() = 0;
	virtual float GETtype() = 0;
};

#endif
