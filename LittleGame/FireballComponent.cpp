#include "FireballComponent.h"

FireballComponent::FireballComponent(Projectile& pHead, float modi) : AbilityComponent(pHead)
{
	this->damage *= modi;
	this->range *= modi;
}

const size_t FireballComponent::getID()
{
	return -1;
}

void FireballComponent::receive(GameObject & obj, Message msg)
{

}

void FireballComponent::cleanUp()
{

}

