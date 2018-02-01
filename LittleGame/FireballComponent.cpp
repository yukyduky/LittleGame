#include "FireballComponent.h"

FireballComponent::FireballComponent(Projectile& pHead, float modi) : AbilityComponent(pHead)
{
	this->damage = 10 * modi;
	this->range *= 100 * modi;


	this->type = ABILITYTYPE::FIRE;
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

