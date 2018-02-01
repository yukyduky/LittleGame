#include "ActorObject.h"
#include "GameObject.h"
#include "ControllerComponent.h"
#include "Locator.h"
#include "GamePlayState.h"

ActorObject::ActorObject(const size_t ID)
	: GameObject(ID)
{
	for (auto it : this->abilities) {
		it = nullptr;
	}
}


ActorObject::ActorObject(const size_t ID, XMFLOAT3 pos, GamePlayState* pGPS)
	: GameObject(ID, pos)
{
	this->pGPS = pGPS;
	this->pos = pos;
	for (auto it : this->abilities) {
		it = nullptr;
	}
}

const size_t ActorObject::getID()
{
	return this->ID;
}

void ActorObject::receive(GameObject & obj, Message msg)
{

}

void ActorObject::cleanUp()
{
	// Clean up all internal data

	// Cleanup all the components
	for (auto &c : this->components) {
		c->getID();
		c->cleanUp();
		delete c;
	}
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
		double dt = Locator::getGameTime()->getDeltaTime();
		XMFLOAT3 playerPos = this->getPosition();
		XMFLOAT3 playerVelocity = this->getVelocity();
		playerPos.z += playerVelocity.z * dt;
		this->setPosition(playerPos);
		this->updateWorldMatrix();
	}
	else {

	}
}

void ActorObject::moveLeft()
{
	if (this->state == OBJECTSTATE::IDLE || this->state == OBJECTSTATE::MOVING) {
		double dt = Locator::getGameTime()->getDeltaTime();
		XMFLOAT3 playerPos = this->getPosition();
		XMFLOAT3 playerVelocity = this->getVelocity();
		playerPos.x -= playerVelocity.x * dt;
		this->setPosition(playerPos);
		this->updateWorldMatrix();
	}
	else {

	}
}
void ActorObject::moveDown()
{
	if (this->state == OBJECTSTATE::IDLE || this->state == OBJECTSTATE::MOVING) {
		double dt = Locator::getGameTime()->getDeltaTime();
		XMFLOAT3 playerPos = this->getPosition();
		XMFLOAT3 playerVelocity = this->getVelocity();
		playerPos.z -= playerVelocity.z * dt;
		this->setPosition(playerPos);
		this->updateWorldMatrix();
	}
	else {

	}
}
void ActorObject::moveRight()
{
	if (this->state == OBJECTSTATE::IDLE || this->state == OBJECTSTATE::MOVING) {
		double dt = Locator::getGameTime()->getDeltaTime();
		XMFLOAT3 playerPos = this->getPosition();
		XMFLOAT3 playerVelocity = this->getVelocity();
		playerPos.x += playerVelocity.x * dt;
		this->setPosition(playerPos);
		this->updateWorldMatrix();
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
		ProjProp props(5, XMFLOAT3(0.5, 0.5, 0.5));
		pGPS->initProjectile(this->pos, XMFLOAT3(1.5, 1.5, 1.5), props);
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
	this->components.push_back(pInputComponent);
}

InputComponent* ActorObject::GETinputComponent()
{
	return this->pInput;
}

