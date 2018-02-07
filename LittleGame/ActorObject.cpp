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


ActorObject::ActorObject(const size_t ID, XMFLOAT3 pos, XMFLOAT3 velocity, GamePlayState* pGPS, OBJECTTYPE::TYPE objectType)
	: GameObject(ID, pos)
{
	this->pGPS = pGPS;
	this->pos = pos;
	this->setState(OBJECTSTATE::IDLE);

	this->type = objectType;
	this->velocity = velocity;	
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
	XMFLOAT3 playerPos = this->getPosition();
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
		if (this->spells.at(size_t(NAME::EXPLOSION))->getState() == SPELLSTATE::READY)
		{
			spells.at(size_t(NAME::EXPLOSION))->castSpell();
		}
		//if (autoAttCD[0] <= 0)
		//{
		//	ProjProp props(10, XMFLOAT3(200.5f, 200.5f, 0.5f), 400);
		//	this->pGPS->initProjectile(this->pos + DirectX::XMFLOAT3{ -40, 0, 0 }, this->getDirection(), props)->SETrotationMatrix(this->getRotationMatrix());

		//	this->autoAttCD[0] = this->autoAttCD[1];
		//}
	}
	else {

	}
}

void ActorObject::selectAbility1()
{
	if (this->state == OBJECTSTATE::IDLE || this->state == OBJECTSTATE::MOVING) {
		this->rotate();
	}
	else {

	}
}

void ActorObject::selectAbility2()
{
	if (this->state == OBJECTSTATE::IDLE || this->state == OBJECTSTATE::MOVING) {
		this->rotate();
	}
	else {

	}
}

void ActorObject::selectAbility3()
{
	if (this->state == OBJECTSTATE::IDLE || this->state == OBJECTSTATE::MOVING) {
		this->rotate();
	}
	else {

	}
}

void ActorObject::selectAbility4()
{
	if (this->state == OBJECTSTATE::IDLE || this->state == OBJECTSTATE::MOVING) {
		this->rotate();
	}
	else {

	}
}

void ActorObject::fireAbilityX()
{
	if (this->state == OBJECTSTATE::IDLE || this->state == OBJECTSTATE::MOVING) {
		if (spells.at(size_t(NAME::AUTOATTACK))->castSpell())
		{
			
		}
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

	//Below should be changed to work with above
	if (autoAttCD[0] > 0)
	{
		autoAttCD[0] -= Locator::getGameTime()->getDeltaTime();
	}
}

void ActorObject::addSpell(Spell * spell)
{
	int next = this->spells.size();
	this->spells.push_back(spell);
}

