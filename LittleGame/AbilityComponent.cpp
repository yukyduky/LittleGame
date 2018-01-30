#include "AbilityComponent.h"
#include "GameObject.h"

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

}

