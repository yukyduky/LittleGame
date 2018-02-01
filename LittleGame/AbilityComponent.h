#pragma once
#ifndef ABILITYCOMPONENT_H
#define ABILITYCOMPONENT_H

#include "Component.h"

class AbilityComponent : public Component
{
private:


public:
	// -------------TEMPLATE
	AbilityComponent(GameObject* pHead); 
	// -------------TEMPLATE

	virtual const size_t getID();
	virtual void receive(GameObject & obj, Message msg);
	virtual void update();
	virtual void cleanUp();

};








#endif
