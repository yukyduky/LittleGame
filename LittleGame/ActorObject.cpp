#include "ActorObject.h"
#include "ControllerComponent.h"
#include "GamePlayState.h"
#include "MainMenuState.h"
#include "ArenaGlobals.h"
#include "StateManager.h"
#include "RewardMenuState.h"

#include "RestartState.h"
//Include spells
//#include "Spell.h"
#include "IncludeSpells.h"
#include <DirectXMath.h>


ActorObject::ActorObject(const size_t ID, float speed, XMFLOAT3 pos, XMFLOAT3 velocity, GamePlayState* pGPS, OBJECTTYPE::TYPE objectType, float hp_in)
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
	this->hp = hp_in;
	this->hpMAX = hp_in;
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
	for (auto &i : this->spells) {
		delete i;
	}
	this->spells.clear();
	// Cleanup all the components
	for (auto &c : this->components) {
		c->cleanUp();
		delete c;
	}
	this->components.clear();
}

void ActorObject::update()
{
	float gravity = -9.82f * 4.0f;
	float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());

	switch (this->state)
	{
	//State used to make an object fall and after a set time the object becomes "invisible"
	case OBJECTSTATE::TYPE::FALLING:
		this->velocity.y += gravity * dt * 4;
		this->pos.y += this->velocity.y * dt;
		if (this->pos.y < -500.0f) {
			this->pos.y = -500.0f;
			this->velocity.y = 0.0f;
			Locator::getGlobalEvents()->generateMessage(GLOBALMESSAGES::PLAYERDIED);
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
	float deltaTime = static_cast<float>(Locator::getGameTime()->getDeltaTime());
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
		if (tempPos.z > ARENADATA::GETsquareSize() && tempPos.z < ARENADATA::GETarenaHeight() - ARENADATA::GETsquareSize()) {
			actorNewPos.z = tempPos.z;
			this->physicsComponent->updateBoundingArea(actorPos);
		}
		else { actorNewPos.z = actorPos.z; }
		if (tempPos.x > ARENADATA::GETsquareSize() && tempPos.x < ARENADATA::GETarenaWidth() - ARENADATA::GETsquareSize()) {
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
		float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());
		XMFLOAT3 playerPos = this->GETPosition();
		XMFLOAT3 actorVelocity = this->getVelocity() * this->speed;
		playerPos.z += actorVelocity.z * dt;
		if (playerPos.z < ARENADATA::GETarenaHeight() - ARENADATA::GETsquareSize()) {
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
		float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());
		XMFLOAT3 playerPos = this->GETPosition();
		XMFLOAT3 actorVelocity = this->getVelocity() * this->speed;
		playerPos.x -= actorVelocity.x * dt;
		if (playerPos.x > ARENADATA::GETsquareSize()) {
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
		float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());
		XMFLOAT3 playerPos = this->GETPosition();
		XMFLOAT3 actorVelocity = this->getVelocity() * this->speed;
		playerPos.z -= actorVelocity.z * dt;
		if (playerPos.z > ARENADATA::GETsquareSize()) {
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
		float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());
		XMFLOAT3 playerPos = this->GETPosition();
		XMFLOAT3 actorVelocity = this->getVelocity() * this->speed;
		playerPos.x += actorVelocity.x * dt;
		if (playerPos.x < ARENADATA::GETarenaWidth() - ARENADATA::GETsquareSize()) {
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

void ActorObject::pauseMenu()
{
	StateManager::pushState(MainMenuState::getInstance());
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
	Locator::getGlobalEvents()->generateMessage(GLOBALMESSAGES::PLAYERWON);

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
	
	if (this->getType() != OBJECTTYPE::TYPE::PLAYER) {
		vColor colorHolder = this->GETgraphicsComponent()->GETcolor();

		this->GETgraphicsComponent()->updateColor(vColor(
			this->GEThp() / this->GEThpMAX(),
			0.0f,
			0.0f,
			colorHolder.a)
		);
	}

	if (this->hp <= 0.0f) {
		this->hp = 0.0f;
		this->state = OBJECTSTATE::TYPE::DEAD;

		if (this->getType() == OBJECTTYPE::TYPE::ENEMY) {
			Locator::getAudioManager()->play(SOUND::NAME::ENEMYDEATH_3);
			//Locator::getAudioManager()->play(SOUND::NAME::ENEMYDEATH_4);
		}

		// If the player much did dieded, create globalMessage 'PLAYERDIED'
		else if (this->getType() == OBJECTTYPE::TYPE::PLAYER)
			Locator::getGlobalEvents()->generateMessage(GLOBALMESSAGES::PLAYERDIED);
	}
}

bool ActorObject::useEnergy(float energyUse) {
	bool returnValue = false;

	if (energyUse <= this->energy) {
		this->energy -= energyUse;
		returnValue = true;
	}

	return returnValue;
}

void ActorObject::addEnergy(float energyGain) {
	this->energy += energyGain;

	if (this->energy > this->energyMAX)
		this->energy = this->energyMAX;
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
				i = new SpAutoAttack(this);
				break;
			case GLYPHTYPE::GLYPH2:
				i = new SpDash(this);
				break;
			case GLYPHTYPE::GLYPH3:
				i = new SpBuff(this);
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

	this->selectAbility1();
}

void ActorObject::changeSpell(int spell, int glyph)
{
	this->spells[spell]->insertGlyph((GLYPHTYPE)glyph);
}
