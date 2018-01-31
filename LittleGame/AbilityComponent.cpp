#include "AbilityComponent.h"
#include "Projectile.h"

AbilityComponent::AbilityComponent(GameObject* pHead)// : Component(pHead)
{
	
}

const size_t AbilityComponent::getID()
{
	return -1;
}

void AbilityComponent::receive(GameObject & obj, Message msg)
{
	if (msg.compMsg == COMPMSG::CHE_RANGE)
	{
		//Projectile* proj = dynamic_cast<Projectile*>(&obj);
		if (dynamic_cast<Projectile*>(&obj)->getTravelDist() > this->range)
		{
			obj.setState(OBJECTSTATE::DEAD);
		}

	}
}

float AbilityComponent::GETdamage() { return this->damage; }
float AbilityComponent::GETenergyCost() { return this->energyCost; }
float AbilityComponent::GETrange() { return this->range; }
float AbilityComponent::GETtype() { return this->type; }