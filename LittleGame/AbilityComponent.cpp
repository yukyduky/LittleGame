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
	
}

void AbilityComponent::cleanUp()
{

}
