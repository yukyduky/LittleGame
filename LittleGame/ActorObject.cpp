#include "ActorObject.h"
#include "ControllerComponent.h"
#include "GamePlayState.h"
#include "ArenaGlobals.h"
#include "StateManager.h"
#include "EndState.h"

//Include spells
//#include "Spell.h"
#include "IncludeSpells.h"
#include <DirectXMath.h>


ActorObject::ActorObject(const size_t ID, float speed, XMFLOAT3 pos, XMFLOAT3 velocity, GamePlayState* pGPS, OBJECTTYPE::TYPE objectType)
	: GameObject(ID, pos)
{
	this->pGPS = pGPS;
	this->pos = pos;

	this->type = objectType;
	this->velocity = velocity;	
	this->state = OBJECTSTATE::TYPE::ACTIVATED;
	this->speed = speed;
	this->counter = 0.0f;
	this->transitionTime = 5.0f;
	
	// Balance
	this->hp = 100;
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

XMFLOAT3 ActorObject::getDirection(float length)
{
	return XMFLOAT3(-std::cos(this->rotation) * length, 0.0f, std::sin(this->rotation) * length);
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
	for (int i = 0; i < this->spells.size(); i++) {
		delete this->spells[i];
	}
	// Cleanup all the components
	for (auto &c : this->components) {
		c->getID();
		c->cleanUp();
		delete c;
	}
}

void ActorObject::update()
{
	float gravity = -9.82 * 4;
	double dt = Locator::getGameTime()->getDeltaTime();

	switch (this->state)
	{
	//State used to make a object fall and after a set time the object becomes "invisible"
	case OBJECTSTATE::TYPE::FALLING:
		this->velocity.y += gravity * dt * 4;
		this->pos.y += this->velocity.y * dt;
		if (this->pos.y < -500.0f) {
			this->pos.y = -500.0f;
			this->velocity.y = 0.0f;
			this->state = OBJECTSTATE::TYPE::INVISIBLE;
		}
		this->updateWorldMatrix();
		break;
	default:
		for (auto &i : this->components) {
			i->update();
		}
		for (auto &i : this->spells) {
			i->update();
			i->updateCD();
		}
		break;
	}
}

void ActorObject::move()
{
	//Create the new objects we will need for the calculations.
	DirectX::XMFLOAT2 MovementVector;
	MovementVector = this->pInput->GETnormalizedVectorOfLeftStick();
	float deltaTime = Locator::getGameTime()->getDeltaTime();
	XMFLOAT3 actorPos = this->GETPosition();
	XMFLOAT3 actorVelocity = this->getVelocity();
	XMFLOAT3 tempPos = actorPos;
	tempPos.x += MovementVector.x * actorVelocity.x * deltaTime;
	tempPos.z += MovementVector.y * actorVelocity.z * deltaTime;
	XMFLOAT3 actorNewPos;

	//Check so that the player still is inside the arena in x- and z-dimension.
	if (this->getType() == OBJECTTYPE::ENEMY) {
		actorNewPos.z = tempPos.z;
		this->physicsComponent->updateBoundingArea(actorPos);

		actorNewPos.x = tempPos.x;
		this->physicsComponent->updateBoundingArea(actorPos);

		actorNewPos.y = actorPos.y;
		this->setPosition(actorNewPos);
	}

	else {
		if (tempPos.z > ARENASQUARESIZE && tempPos.z < ARENAHEIGHT - ARENASQUARESIZE) {
			actorNewPos.z = tempPos.z;
			this->physicsComponent->updateBoundingArea(actorPos);
		}
		else { actorNewPos.z = actorPos.z; }
		if (tempPos.x > ARENASQUARESIZE && tempPos.x < ARENAWIDTH - ARENASQUARESIZE) {
			actorNewPos.x = tempPos.x;
			this->physicsComponent->updateBoundingArea(actorPos);
		}
		else { actorNewPos.x = actorPos.x; }
		actorNewPos.y = actorPos.y;
		this->setPosition(actorNewPos);
	}
}

void ActorObject::moveUp()
{
	if (this->state == OBJECTSTATE::TYPE::ACTIVATED) {
		double dt = Locator::getGameTime()->getDeltaTime();
		XMFLOAT3 playerPos = this->GETPosition();
		XMFLOAT3 actorVelocity = this->getVelocity() * this->speed;
		playerPos.z += actorVelocity.z * dt;
		if (playerPos.z < ARENAHEIGHT - ARENASQUARESIZE) {
			this->physicsComponent->updateBoundingArea(playerPos);
			this->setPosition(playerPos);
		}
	}
	else {

	}
}

void ActorObject::moveLeft()
{
	if (this->state == OBJECTSTATE::TYPE::ACTIVATED) {
		double dt = Locator::getGameTime()->getDeltaTime();
		XMFLOAT3 playerPos = this->GETPosition();
		XMFLOAT3 actorVelocity = this->getVelocity() * this->speed;
		playerPos.x -= actorVelocity.x * dt;
		if (playerPos.x > ARENASQUARESIZE) {
			this->physicsComponent->updateBoundingArea(playerPos);
			this->setPosition(playerPos);
		}
	}
	else {

	}
}
void ActorObject::moveDown()
{
	if (this->state == OBJECTSTATE::TYPE::ACTIVATED) {
		double dt = Locator::getGameTime()->getDeltaTime();
		XMFLOAT3 playerPos = this->GETPosition();
		XMFLOAT3 actorVelocity = this->getVelocity() * this->speed;
		playerPos.z -= actorVelocity.z * dt;
		if (playerPos.z > ARENASQUARESIZE) {
			this->setPosition(playerPos);
			this->physicsComponent->updateBoundingArea(playerPos);
		}
	}
	else {

	}
}
void ActorObject::moveRight()
{
	if (this->state == OBJECTSTATE::TYPE::ACTIVATED) {
		double dt = Locator::getGameTime()->getDeltaTime();
		XMFLOAT3 playerPos = this->GETPosition();
		XMFLOAT3 actorVelocity = this->getVelocity() * this->speed;
		playerPos.x += actorVelocity.x * dt;
		if (playerPos.x < ARENAWIDTH - ARENASQUARESIZE) {
			this->setPosition(playerPos);
			this->physicsComponent->updateBoundingArea(playerPos);
		}
	}
	else {

	}
}

void ActorObject::rotate()
{
	DirectX::XMFLOAT2 aimVec;
	aimVec = this->pInput->GETnormalizedVectorOfRightStick();
	XMVECTOR aimNor = XMLoadFloat2(&aimVec);
	XMFLOAT2 tempFloatVec = XMFLOAT2(-1.0f, 0.0f);
	XMVECTOR dir = XMLoadFloat2(&tempFloatVec);

	//XMVECTOR aimNor = XMVector3Normalize(aim);
	XMVECTOR angle = XMVector3AngleBetweenVectors(aimNor, dir);

	float temp;
	XMStoreFloat(&temp, angle);

	if (aimVec.y < 0.0f)
	{
		temp *= -1.0f;
	}

	this->rotation = temp;
	//this->rotation = 0.5;

	//this->rotate();

	this->SETrotationMatrix(XMMatrixRotationY(this->rotation));
}

void ActorObject::rotate(XMFLOAT3 aimVec)
{
	XMVECTOR cursor = XMLoadFloat3(&aimVec);
	XMVECTOR posVec = XMLoadFloat3(&this->pos);
	XMVECTOR aim = XMVectorSubtract(cursor, posVec);
	//XMVECTOR dir = XMLoadFloat3(&this->getDirection());
	XMFLOAT3 tempFloatVec = XMFLOAT3(-1.0f, 0.0f, 0.0f);
	XMVECTOR dir = XMLoadFloat3(&tempFloatVec);

	XMVECTOR aimNor = XMVector3Normalize(aim);
	XMVECTOR angle = XMVector3AngleBetweenVectors(aimNor, dir);

	float temp;
	XMStoreFloat(&temp, angle);

	if (this->pos.z > aimVec.z)
	{
		temp *= -1.0f;
	}

	this->rotation = temp;
	//this->rotation = 0.5;

	//this->rotate();

	this->SETrotationMatrix(XMMatrixRotationY(this->rotation));
}

void ActorObject::rotate(XMFLOAT2 aimVec)
{
	
}

void ActorObject::fireAbility0()
{
	if (this->state == OBJECTSTATE::TYPE::ACTIVATED) {
		this->spells[0]->castSpell();
	}
	else {

	}
}

void ActorObject::fireAbilityX()
{
	if ((this->state == OBJECTSTATE::TYPE::ACTIVATED) && this->spells[4]->getState() != SPELLSTATE::ACTIVE) {
		this->selectedSpell->castSpell();
	}
	else {

	}
}

void ActorObject::selectAbility1()
{
	if (this->state == OBJECTSTATE::TYPE::ACTIVATED) {
		this->selectedSpell = this->spells[1];
	}
	else {

	}
}

void ActorObject::selectAbility2()
{
	this->pGPS->GETMouseInput()->getWorldPosition();

	if (this->state == OBJECTSTATE::TYPE::ACTIVATED) {
		this->selectedSpell = this->spells[2];
	}
	else {

	}
}

void ActorObject::selectAbility3()
{
	if (this->state == OBJECTSTATE::TYPE::ACTIVATED) {
		this->selectedSpell = this->spells[3];
		
	}
	else {

	}
}

void ActorObject::selectAbility4()
{
	if (this->state == OBJECTSTATE::TYPE::ACTIVATED) {
		this->selectedSpell = this->spells[4];
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
	
}

void ActorObject::dealDmg(float dmg)
{
	this->hp -= dmg;
	if (this->hp <= 0) {
		this->hp = 0;
		this->state = OBJECTSTATE::TYPE::DEAD;

		// Push the "EndState" which will end all!
		StateManager::pushState(EndState::getInstance());
	}
}

void ActorObject::addSpell(Spell * spell)
{
	this->spells.push_back(spell);
}

void ActorObject::switchSpell()
{
	// new vector with spells that will replace the old once
	std::vector<Spell*> newSpells;

	for (auto j : this->spells)
	{
		Spell* i = nullptr;

		// First look at the name
		switch (j->getName())
		{

		case NAME::AUTOATTACK:
			// Looks at what new spell will replace depending on what glyph has been added to the spell
			switch (j->getGlyph())
			{
			case GLYPHTYPE::NONE:
				i = new SpAutoAttack(this);
				break;
			case GLYPHTYPE::GLYPH1:
				i = new SpAutoAttack(this);
				break;
			case GLYPHTYPE::GLYPH2:
				i = new SpAutoAttack(this);
				break;
			case GLYPHTYPE::GLYPH3:
				i = new SpAutoAttack(this);
				break;
			}
			break;

		case NAME::FIRE:
			switch (j->getGlyph())
			{
			case GLYPHTYPE::NONE:
				i = new SpFire(this);
				break;
			case GLYPHTYPE::GLYPH1:
				i = new SpFire(this);
				break;
			case GLYPHTYPE::GLYPH2:
				i = new SpFire(this);
				break;
			case GLYPHTYPE::GLYPH3:
				i = new SpFire(this);
				break;
			}
			break;

		case NAME::BOMB:
			switch (j->getGlyph())
			{
			case GLYPHTYPE::NONE:
				i = new SpBomb(this);
				break;
			case GLYPHTYPE::GLYPH1:
				i = new SpBomb(this);
				break;
			case GLYPHTYPE::GLYPH2:
				i = new SpBomb(this);
				break;
			case GLYPHTYPE::GLYPH3:
				i = new SpBomb(this);
				break;
			}
			break;

		case NAME::DASH:
			switch (j->getGlyph())
			{
			case GLYPHTYPE::NONE:
				i = new SpDash(this);
				break;
			case GLYPHTYPE::GLYPH1:
				i = new SpDash(this);
				break;
			case GLYPHTYPE::GLYPH2:
				i = new SpDash(this);
				break;
			case GLYPHTYPE::GLYPH3:
				i = new SpDash(this);
				break;
			}
			break;

		case NAME::BUFF:
			switch (j->getGlyph())
			{
			case GLYPHTYPE::NONE:
				i = new SpBuff(this);
				break;
			case GLYPHTYPE::GLYPH1:
				i = new SpBuff(this);
				break;
			case GLYPHTYPE::GLYPH2:
				i = new SpBuff(this);
				break;
			case GLYPHTYPE::GLYPH3:
				i = new SpBuff(this);
				break;
			}
			break;
		}// i is holding the new Spell

		newSpells.push_back(i);

	}
	
	this->spells.clear();
	
	for (auto i : newSpells)
	{
		this->spells.push_back(i);
	}
	
	newSpells.clear();
}