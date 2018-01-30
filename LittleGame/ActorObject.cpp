#include "ActorObject.h"
#include "GameObject.h"

ActorObject::ActorObject(const size_t ID)
	: GameObject(ID)
{
	for (auto it : this->abilities) {
		it = nullptr;
	}
}


ActorObject::ActorObject(const size_t ID, Vector3 pos)
	: GameObject(ID, pos)
{
	for (auto it : this->abilities) {
		it = nullptr;
	}
}

const size_t ActorObject::getID()
{
	return -1;
}

void ActorObject::receive(GameObject & obj, Message msg)
{

}

void ActorObject::move()
{
	if (this->state == OBJECTSTATE::IDLE || this->state == OBJECTSTATE::MOVING) {
		// Change the position of the worldMatrix depending on the rotation
	}
	else {

	}
}

void ActorObject::move(Vector3 direction, float speed)
{

}

void ActorObject::fireAbility0()
{

}

void ActorObject::selectAbilityX()
{

}

void ActorObject::fireAbilityX()
{

}