#include "ActorObject.h"
#include "GameObject.h"
#include "ControllerComponent.h"
#include "Locator.h"
#include "ArenaGlobals.h"

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
	float deltaTime = Locator::getGameTime()->getDeltaTime();
	XMFLOAT3 playerPos = this->getPosition();
	XMFLOAT3 playerVelocity = this->getVelocity();
	XMFLOAT3 tempPos = playerPos;
	tempPos.x += MovementVector.x * playerVelocity.x * deltaTime;
	tempPos.z += MovementVector.y * playerVelocity.z * deltaTime;
	
	XMFLOAT3 playerNewPos;
	if (tempPos.z > ARENASQUARESIZE && tempPos.z < ARENAHEIGHT - ARENASQUARESIZE) {
		playerNewPos.z = tempPos.z;
	}
	else { playerNewPos.z = playerPos.z; }
	if (tempPos.x > ARENASQUARESIZE && tempPos.x < ARENAWIDTH - ARENASQUARESIZE) {
		playerNewPos.x = tempPos.x;
	} 
	else { playerNewPos.x = playerPos.x; }
	playerNewPos.y = playerPos.y;
	this->updateWorldMatrix(playerNewPos);
	// Affect position based on movement vector
}

void ActorObject::moveUp()
{
	if (this->state == OBJECTSTATE::IDLE || this->state == OBJECTSTATE::MOVING) {
		double dt = Locator::getGameTime()->getDeltaTime();
		XMFLOAT3 playerPos = this->getPosition();
		XMFLOAT3 playerVelocity = this->getVelocity();
		playerPos.z += playerVelocity.z * dt;
		if (playerPos.z < ARENAHEIGHT - ARENASQUARESIZE) {
			this->updateWorldMatrix(playerPos);
		}
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
		if (playerPos.x > ARENASQUARESIZE) {
			this->updateWorldMatrix(playerPos);
		}
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
		if (playerPos.z > ARENASQUARESIZE) {
			this->updateWorldMatrix(playerPos);
		}
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
		if (playerPos.x < ARENAWIDTH - ARENASQUARESIZE) {
			this->updateWorldMatrix(playerPos);
		}
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
	this->components.push_back(pInputComponent);
}

InputComponent* ActorObject::GETinputComponent()
{
	return this->pInput;
}

