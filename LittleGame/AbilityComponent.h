#pragma once
#ifndef ABILITYCOMPONENT_H_
#define ABILITYCOMPONENT_H_

#include "Component.h"
#include <DirectXMath.h>

namespace ABILITYTYPE {
	enum TYPE { DEFAULT, SIZE};
}

class AbilityComponent : public Component
{
public:
	
	virtual const size_t getID() = 0;
	virtual void receive(GameObject & obj, Message msg) = 0;
	virtual float GETdamage() = 0;
	virtual float GETrange() = 0;
	virtual float GETenergyCost() = 0;
	virtual float GETtype() = 0;
};

#endif
