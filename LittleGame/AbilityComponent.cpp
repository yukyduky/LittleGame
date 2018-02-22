#include "AbilityComponent.h"

AbilityComponent::AbilityComponent(Projectile& pHead)
{
	this->pHead = &pHead;

}

const size_t AbilityComponent::getID()
{
	return -1;
}

void AbilityComponent::receive(GameObject & obj, Message msg)
{

}

void AbilityComponent::update()
{
	this->range -= static_cast<float>(Locator::getGameTime()->getDeltaTime());

	if (this->range < 0.0f)
	{
		this->pHead->setState(OBJECTSTATE::TYPE::DEAD);
	}
}

void AbilityComponent::cleanUp()
{

}
