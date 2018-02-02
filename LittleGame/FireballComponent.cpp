#include "FireballComponent.h"

FireballComponent::FireballComponent(Projectile& pHead, float modi) : AbilityComponent(pHead)
{
	this->damage = 10 * modi;
	this->range *= 100 * modi;
	this->speed = 50;

	pHead.setSpeed(this->speed);

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

void FireballComponent::update()
{
	int hej = 0;
	int hejhej = hej + hej;
	
}

