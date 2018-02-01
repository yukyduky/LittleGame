#include "AbilityComponent.h"
#include "GameObject.h"


// -------------TEMPLATE
AbilityComponent::AbilityComponent(GameObject* pHead)
{
}
// -------------TEMPLATE

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
