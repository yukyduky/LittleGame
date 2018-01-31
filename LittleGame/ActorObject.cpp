#include "ActorObject.h"
#include "GameObject.h"
#include "ControllerComponent.h"

ActorObject::ActorObject(const size_t ID)
	: GameObject(ID)
{
	for (auto it : this->abilities) {
		it = nullptr;
	}
}


ActorObject::ActorObject(const size_t ID, XMFLOAT3 pos)
	: GameObject(ID, pos)
{
	this->pos = pos;
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
	DirectX::XMFLOAT2 MovementVector;
	MovementVector = this->pInput->GETnormalizedVectorOfLeftStick();
	
	// Affect position based on movement vector

}

void ActorObject::moveUp()
{
	if (this->state == OBJECTSTATE::IDLE || this->state == OBJECTSTATE::MOVING) {

	}
	else {

	}
}

void ActorObject::moveLeft()
{
	if (this->state == OBJECTSTATE::IDLE || this->state == OBJECTSTATE::MOVING) {

	}
	else {

	}
}
void ActorObject::moveDown()
{
	if (this->state == OBJECTSTATE::IDLE || this->state == OBJECTSTATE::MOVING) {

	}
	else {

	}
}
void ActorObject::moveRight()
{
	if (this->state == OBJECTSTATE::IDLE || this->state == OBJECTSTATE::MOVING) {

	}
	else {

	}
}

void ActorObject::rotate()
{
	if (this->state == OBJECTSTATE::IDLE || this->state == OBJECTSTATE::MOVING) {

	}
	else {

	}
}

void ActorObject::fireAbility0()
{
	if (this->state == OBJECTSTATE::IDLE || this->state == OBJECTSTATE::MOVING) {

	}
	else {

	}
}

void ActorObject::selectAbilityX()
{

}

void ActorObject::fireAbilityX()
{
	if (this->state == OBJECTSTATE::IDLE || this->state == OBJECTSTATE::MOVING) {

	}
	else {

	}
}

void ActorObject::SETinputComponent(InputComponent* pInputComponent)
{
	this->pInput = pInputComponent;
}

InputComponent* ActorObject::GETinputComponent()
{
	return this->pInput;
}

