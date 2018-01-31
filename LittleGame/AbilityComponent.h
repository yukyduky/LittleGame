#pragma once
#ifndef ABILITYCOMPONENT_H
#define ABILITYCOMPONENT_H

#include "Component.h"

class AbilityComponent : public Component
{
private:


public:
	AbilityComponent();

	// Constructor for AbilityComponent
	/*AbilityComponent(GameObject* pHead, int testVariable);*/
	virtual const size_t getID();
	virtual void receive(GameObject & obj, Message msg);
	virtual void cleanUp();

};








#endif
