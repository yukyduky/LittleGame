#pragma once
#ifndef FIREBALLCOMPONENT_H
#define FIREBALLCOMPONENT_H

#include "AbilityComponent.h"


class FireballComponent : public AbilityComponent
{
private:
	
public:
	FireballComponent(Projectile& pHead, float modi);

	virtual const size_t getID();
	virtual void receive(GameObject & obj, Message msg);
	virtual void cleanUp();

	void update();


};








#endif //!FIREBALLCOMPONENT_H
