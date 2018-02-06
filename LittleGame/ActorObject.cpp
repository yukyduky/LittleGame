#include "ActorObject.h"
#include "ControllerComponent.h"
#include "GamePlayState.h"
#include "ArenaGlobals.h"

//Include spells
#include "DamageSpell.h"
#include "MobilitySpell.h"

#include <DirectXMath.h>

ActorObject::ActorObject(const size_t ID)
	: GameObject(ID)
{
	
}


ActorObject::ActorObject(const size_t ID, XMFLOAT3 pos, GamePlayState* pGPS)
	: GameObject(ID, pos)
{
	this->pGPS = pGPS;
	this->pos = pos;
}

const size_t ActorObject::getID()
{
	return this->ID;
}

GamePlayState * ActorObject::getPGPS()
{
	return this->pGPS;
}

float ActorObject::getRotation()
{
	return this->rotation;
}

XMFLOAT3 ActorObject::getDirection()
{
	return XMFLOAT3(-std::cos(this->rotation), 0.0f, std::sin(this->rotation));
}

void ActorObject::setSpeed(float speed)
{
	this->speed = speed;
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
	//Create the new objects we will need for the calculations.
	DirectX::XMFLOAT2 MovementVector;
	MovementVector = this->pInput->GETnormalizedVectorOfLeftStick();
	float deltaTime = Locator::getGameTime()->getDeltaTime();
	XMFLOAT3 playerPos = this->GETPosition();
	XMFLOAT3 playerVelocity = this->getVelocity();
	XMFLOAT3 tempPos = playerPos;
	tempPos.x += MovementVector.x * playerVelocity.x * deltaTime;
	tempPos.z += MovementVector.y * playerVelocity.z * deltaTime;
	XMFLOAT3 playerNewPos;

	//Check so that the player still is inside the arena in x- and z-dimension.
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
}

void ActorObject::moveUp()
{
	if (this->state == OBJECTSTATE::IDLE || this->state == OBJECTSTATE::MOVING) {
		double dt = Locator::getGameTime()->getDeltaTime();
		XMFLOAT3 playerPos = this->GETPosition();
		XMFLOAT3 playerVelocity = this->getVelocity() * this->speed;
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
		XMFLOAT3 playerPos = this->GETPosition();
		XMFLOAT3 playerVelocity = this->getVelocity() * this->speed;;
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
		XMFLOAT3 playerPos = this->GETPosition();
		XMFLOAT3 playerVelocity = this->getVelocity() * this->speed;;
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
		XMFLOAT3 playerPos = this->GETPosition();
		XMFLOAT3 playerVelocity = this->getVelocity() * this->speed;;
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
		this->rotation += 0.1f;
		XMMATRIX rotateM = XMMatrixRotationY(this->rotation);
		this->SETrotationMatrix(XMMatrixRotationY(this->rotation));
		
		this->updateWorldMatrix(this->pos);
	}
	else {

	}
}

void ActorObject::fireAbility0()
{
	if (this->state == OBJECTSTATE::IDLE || this->state == OBJECTSTATE::MOVING) {
		this->spells[0]->castSpell();
	}
	else {

	}
}

void ActorObject::selectAbility1()
{
	if (this->state == OBJECTSTATE::IDLE || this->state == OBJECTSTATE::MOVING) {
		this->selectedSpell = this->spells[1];
	}
	else {

	}
}

void ActorObject::selectAbility2()
{
	if (this->state == OBJECTSTATE::IDLE || this->state == OBJECTSTATE::MOVING) {
		this->selectedSpell = this->spells[2];
	}
	else {

	}
}

void ActorObject::selectAbility3()
{
	if (this->state == OBJECTSTATE::IDLE || this->state == OBJECTSTATE::MOVING) {
		this->selectedSpell = this->spells[3];
		
	}
	else {

	}
}

void ActorObject::selectAbility4()
{
	if (this->state == OBJECTSTATE::IDLE || this->state == OBJECTSTATE::MOVING) {
		this->selectedSpell = this->spells[4];
	}
	else {

	}
}

void ActorObject::fireAbilityX()
{
	if (this->state == OBJECTSTATE::IDLE || this->state == OBJECTSTATE::MOVING) {
		this->selectedSpell->castSpell();
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

void ActorObject::decCD()
{
	for (auto itteration : spells)
	{
		itteration->updateCD();
	}
	// Resets the player to the original movmentspeed, before the CD runs out
	if (this->spells.at(size_t(NAME::SPEEDBUFF))->getState() == SPELLSTATE::COOLDOWN)
	{
		if (this->spells.at(size_t(NAME::SPEEDBUFF))->getTSC() > 1.5)
		{
			this->speed = 1;
		}
	}
}

void ActorObject::addSpell(Spell * spell)
{
	int next = this->spells.size();
	this->spells.push_back(spell);
}

