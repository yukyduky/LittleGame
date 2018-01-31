#include "AbilityComponent.h"
#include "Projectile.h"

//AbilityComponent::AbilityComponent(GameObject* pHead, int testVariable) 
//	: Component(pHead)
//{
//	// this->head = pHead  <-- is set by Component(pHead)
//	int blah = testVariable;
//}

const size_t AbilityComponent::getID()
{
	return -1;
}

void AbilityComponent::receive(GameObject & obj, Message msg)
{
	if (msg.compMsg == COMPMSG::CHE_RANGE)
	{
		Projectile* proj = dynamic_cast<Projectile*>(&obj);
		if (proj->getTravelDist() < this->GETrange())
		{
			obj.setState(OBJECTSTATE::STOP);
		}

	}
}

