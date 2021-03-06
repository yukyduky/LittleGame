#include "ActorObject.h"
#include "ControllerComponent.h"
#include "GamePlayState.h"
#include "MenuPauseState.h"
#include "ArenaGlobals.h"
#include "StateManager.h"
#include "MenuRewardState.h"
#include "MenuStatisticsState.h"

#include "RestartState.h"
//Include spells
//#include "Spell.h"
#include "IncludeSpells.h"
#include <DirectXMath.h>


void ActorObject::truncateKineticVector()
{
	float multiSpeed = Locator::getGameTime()->getMultiplier() * this->topSpeed * this->topSpeedMagnitude;
	if (this->kineticVector.x < (multiSpeed * -1))
		this->kineticVector.x = (multiSpeed * -1);
	else if (this->kineticVector.x > multiSpeed)
		this->kineticVector.x = multiSpeed;

	if (this->kineticVector.z > multiSpeed)
		this->kineticVector.z = (multiSpeed);
	else if (this->kineticVector.z < (multiSpeed * -1))
		this->kineticVector.z = (multiSpeed* -1);
}

void ActorObject::applyFriction(float dt)
{
	float appliedFriction = this->frictionFactor * dt/* * this->topSpeedMagnitude*/;
	// Friction for X-AXIS
	if (this->kineticVector.x > 0.0f)
	{
		this->kineticVector.x -= appliedFriction;

		if (this->kineticVector.x < 0.0f)
			this->kineticVector.x = 0.0f;
	}
	else if (this->kineticVector.x < 0.0f)
	{
		this->kineticVector.x += appliedFriction;

		if (this->kineticVector.x > 0.0f)
			this->kineticVector.x = 0.0f;
	}

	// Friction for Z-AXIS
	if (this->kineticVector.z > 0.0f)
	{
		this->kineticVector.z -= appliedFriction;

		if (this->kineticVector.z < 0.0f)
			this->kineticVector.z = 0.0f;
	}
	else if (this->kineticVector.z < 0.0f)
	{
		this->kineticVector.z += appliedFriction;

		if (this->kineticVector.z > 0.0f)
			this->kineticVector.z = 0.0f;
	}
}

void ActorObject::preventLeaveArena()
{
	// Attempting to exit arena, NORTH
	if (this->newPos.z > ARENADATA::GETarenaHeight() - ARENADATA::GETsquareSize()) {
		this->physicsComponent->updateBoundingArea(this->previousPos);
		this->setPosition(this->previousPos);
		this->kineticVector.z *= -1;
	}
	// Attempting to exit arena, WEST
	else if (this->newPos.x < ARENADATA::GETsquareSize()) {
		this->physicsComponent->updateBoundingArea(this->previousPos);
		this->setPosition(this->previousPos);
		this->kineticVector.x *= -1;
	}
	// Attempting to exit arena, SOUTH
	else if (this->newPos.z < ARENADATA::GETsquareSize()) {
		this->setPosition(this->previousPos);
		this->physicsComponent->updateBoundingArea(this->previousPos);
		this->kineticVector.z *= -1;
	}
	// Attempting to exit arena, EAST
	else if (this->newPos.x > ARENADATA::GETarenaWidth() - ARENADATA::GETsquareSize()) {
		this->setPosition(this->previousPos);
		this->physicsComponent->updateBoundingArea(this->previousPos);
		this->kineticVector.x *= -1;
	}
}

ActorObject::ActorObject(const size_t ID, float velocityMagnitude, float topSpeed, XMFLOAT3 pos, GamePlayState* pGPS, OBJECTTYPE::TYPE objectType, float hp_in)
	: GameObject(ID, pos)
{
	this->pGPS = pGPS;
	this->pos = pos;
	this->previousPos = pos;

	this->type = objectType;
	this->kineticVector = { 0.0f, 0.0f, 0.0f };
	this->state = OBJECTSTATE::TYPE::ACTIVATED;
	this->velocityMagnitude = velocityMagnitude;
	this->topSpeed = topSpeed;
	this->topSpeedMagnitude = 1.0f;
	this->counter = 0.0f;
	this->transitionTime = 5.0f;

	this->frictionFactor = 15.0f;
	
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

void ActorObject::setDirection()
{
	this->direction = XMFLOAT3(-std::cos(this->rotation), 0.0f, std::sin(this->rotation));
}
void ActorObject::setDirection(XMFLOAT3 direction)
{
	this->direction = direction;
}

XMFLOAT3 ActorObject::getDirection()
{
	return this->direction;
}

XMFLOAT3 ActorObject::getDirection(float length)
{
	return XMFLOAT3(-std::cos(this->rotation) * length, 0.0f, std::sin(this->rotation) * length);
}

void ActorObject::SETvelocityMagnitude(float velocityMagnitude)
{
	this->velocityMagnitude = velocityMagnitude;
}

void ActorObject::SETtopSpeedMagnitude(float speed)
{
	this->topSpeedMagnitude = speed;
}

void ActorObject::restoreFullHealth()
{
	this->hp = this->hpMAX;
}

void ActorObject::receive(GameObject & obj, Message msg)
{

}

void ActorObject::cleanUp()
{
	// Clean up all internal data
	for (int i = 0; i < this->spells.size(); i++) {
		if (this->spells[i] != nullptr) {
			this->spells[i]->cleanUp();
			delete this->spells[i];
			this->spells[i] = nullptr;
		}
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
	vColor colorHolder = this->GETgraphicsComponent()->GETcolorOriginal();
	float healthRatioHolder = this->GEThp() / this->GEThpMAX();

	this->move();

	switch (this->statusEffect)
	{
	case TILESTATE::COOLED:
		this->counter += dt;
		if (this->counter > 3.0f) {
			this->statusEffect = TILESTATE::ACTIVE;
			this->topSpeed *= 2.0f;
			this->slowed = false;
		}
		else if (!slowed)
		{
			this->topSpeed *= 0.5f;
			this->slowed = true;
		}
		break;
	case TILESTATE::HEATED:
		this->dealDmg(15.0f);
		this->statusEffect = TILESTATE::ACTIVE;
		break;
	case TILESTATE::ELECTRIFIED:
		this->counter += dt;
		if (this->counter > 1.5f) {
			this->statusEffect = TILESTATE::ACTIVE;
			this->state = OBJECTSTATE::TYPE::ACTIVATED;

			this->GETgraphicsComponent()->updateColor(vColor(
				(colorHolder.r * healthRatioHolder),
				(colorHolder.g * healthRatioHolder),
				(colorHolder.b * healthRatioHolder),
				(colorHolder.a * healthRatioHolder))
			);

		}
		else {
			this->state = OBJECTSTATE::TYPE::STUNNED;
			this->kineticVector.x = 0.0f;
			this->kineticVector.z = 0.0f;
			this->GETgraphicsComponent()->updateColor(vColor(0.784f, 0.784f, 0.001f, 1.0f));
		}
		break;
	default:
		break;
	}


	switch (this->state)
	{
	//State used to make an object fall and after a set time the object becomes "invisible"
	case OBJECTSTATE::TYPE::FALLING:
		// Set x- and z-kineticVector to 0 in order to fall straight down
		this->kineticVector.x = 0.0f;
		this->kineticVector.z = 0.0f;

		this->kineticVector.y += gravity * dt * 4;
		this->pos.y += this->kineticVector.y * dt;
		if (this->pos.y < -500.0f) {
			this->pos.y = -500.0f;
			this->kineticVector.y = 0.0f;
			Locator::getGlobalEvents()->generateMessage(GLOBALMESSAGES::PLAYERDIED);
		}
		this->updateWorldMatrix();
		break;
	case OBJECTSTATE::TYPE::GENERATORRISING:
		if (this->pos.y < 25.0f) {
			this->pos.y += 0.5;
			this->turnOnInvulnerability();
		}
		else {
			this->pos.y = 25.0f;
			this->turnOffInvulnerability();
			this->state = OBJECTSTATE::TYPE::GENERATORACTIVE;
		}
		this->updateWorldMatrix();
		break;
	case OBJECTSTATE::TYPE::STUNNED:
		break;
	case OBJECTSTATE::TYPE::TELEPORTED:
		this->applyStatusEffect(TILESTATE::STATE::ELECTRIFIED);
		for (auto &i : this->components) {
			i->update();
		}
		for (auto &i : this->spells) {
			i->updateCD();
		}
		break;
	default:
		for (auto &i : this->components) {
			i->update();
		}
		for (auto &i : this->spells) {
			i->updateCD();// The player only wants the CD of hte spell
		}
		break;
	}
}

void ActorObject::updatekineticVector()
{
	float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());
	this->previousPos = this->pos;

	//Create the new objects we will need for the calculations.
	//DirectX::XMFLOAT2 movementInput = this->pInput->GE&TnormalizedVectorOfLeftStick();
	this->MovementVector = this->pInput->GETnormalizedVectorOfLeftStick();
	this->moveDirection = { MovementVector.x, 0.0f, MovementVector.y };

	XMFLOAT3 additiveVector = (this->moveDirection * this->velocityMagnitude * dt);

	this->kineticVector.x += additiveVector.x;
	this->kineticVector.z += additiveVector.z;
}

void ActorObject::setKineticVector(XMFLOAT3 kineticVector_)
{
	this->kineticVector = kineticVector_;
}

void ActorObject::updatekineticVectorUp()
{
	float multiplier = Locator::getGameTime()->getMultiplier() * this->topSpeedMagnitude;
	if (this->state == OBJECTSTATE::TYPE::ACTIVATED && this->kineticVector.z < this->topSpeed * multiplier) {
		float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());

		this->moveDirection = { 0.0f, 0.0f, 1.0f };

		XMFLOAT3 additiveVector = (this->moveDirection * this->velocityMagnitude * dt);

		// Moving up; only needs 'z'
		kineticVector.z += additiveVector.z;
	}
}

void ActorObject::updatekineticVectorLeft()
{
	float multiplier = Locator::getGameTime()->getMultiplier() * this->topSpeedMagnitude;
	if (this->state == OBJECTSTATE::TYPE::ACTIVATED && this->kineticVector.z < this->topSpeed * multiplier) {
		float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());

		this->moveDirection = { -1.0f, 0.0f, 0.0f };

		XMFLOAT3 additiveVector = (this->moveDirection * this->velocityMagnitude * dt);

		// Moving Left; only needs 'x'
		kineticVector.x += additiveVector.x;
	}
}
void ActorObject::updatekineticVectorDown()
{
	float multiplier = Locator::getGameTime()->getMultiplier() * this->topSpeedMagnitude;
	if (this->state == OBJECTSTATE::TYPE::ACTIVATED && this->kineticVector.z < this->topSpeed * multiplier) {
		float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());

		this->moveDirection = { 0.0f, 0.0f, -1.0f };

		XMFLOAT3 additiveVector = (this->moveDirection * this->velocityMagnitude * dt);

		// Moving down; only needs 'z'
		kineticVector.z += additiveVector.z;
	}
}
void ActorObject::updatekineticVectorRight()
{
	float multiplier = Locator::getGameTime()->getMultiplier() * this->topSpeedMagnitude;
	if (this->state == OBJECTSTATE::TYPE::ACTIVATED && this->kineticVector.z < this->topSpeed * multiplier) {
		float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());

		this->moveDirection = { 1.0f, 0.0f, 0.0f };

		XMFLOAT3 additiveVector = (this->moveDirection * this->velocityMagnitude * dt);

		// Moving right; only needs 'x'
		kineticVector.x += additiveVector.x;

	}
}

void ActorObject::move()
{
	float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());

	// Make sure that the actor doesn't exceed max speed
	this->truncateKineticVector();

	// Storing previous pos & preparing the new pos
	this->previousPos = this->pos;
	this->newPos = this->pos;

	this->newPos.x += this->kineticVector.x;
	//this->newPos.y += this->kineticVector.y;
	this->newPos.z += this->kineticVector.z;

	this->applyFriction(dt);

	this->pos = newPos;
	this->physicsComponent->updateBoundingArea(pos);

	// ANTI-'EXIT-ARENA' code for the PLAYER
	if (this->getType() == OBJECTTYPE::TYPE::PLAYER)
		this->preventLeaveArena();
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

	// Update direction
	this->setDirection();
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

	// Update direction
	this->setDirection();
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
	if (this->state == OBJECTSTATE::TYPE::ACTIVATED) {
		this->selectedSpell->castSpell();
	}
	else {

	}
}

void ActorObject::pauseMenu()
{
	StateManager::pushState(MenuPauseState::getInstance());
	Locator::getAudioManager()->pause(MUSIC::GAME_MUSIC);
	Locator::getAudioManager()->play(MUSIC::MENU_MUSIC);
}

void ActorObject::selectAbility1()
{
	if (this->state == OBJECTSTATE::TYPE::ACTIVATED) {
		this->selectedSpell = this->spells[1];
		this->selectedSpellIntValue = 1;
	}
	else {

	}
}

void ActorObject::selectAbility2()
{
	if (this->state == OBJECTSTATE::TYPE::ACTIVATED) {
		this->selectedSpell = this->spells[2];
		this->selectedSpellIntValue = 2;
	}
	else {

	}
}

void ActorObject::selectAbility3()
{
	if (this->state == OBJECTSTATE::TYPE::ACTIVATED) {
		this->spells[3]->castSpell();
		//this->selectedSpell = this->spells[3];
		//this->selectedSpellIntValue = 3;
	}
	else {

	}
}

void ActorObject::selectAbility4()
{
	Locator::getGlobalEvents()->generateMessage(GLOBALMESSAGES::PLAYERWON);

	if (this->state == OBJECTSTATE::TYPE::ACTIVATED) {
		this->spells[4]->castSpell();

		//this->selectedSpell = this->spells[4];
		//this->selectedSpellIntValue = 4;
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

//void ActorObject::decCD()
//{
//	for (auto itteration : spells)
//	{
//		itteration->updateCD();
//	}
//	
//}

void ActorObject::dealDmg(float damag)
{
	float dmg = damag;
	if (this->pGPS->getBerserkerMode())
	{
		dmg *= 3.0f;
	}

	this->hp -= dmg * this->invulnerable;
	
	if (this->getType() != OBJECTTYPE::TYPE::PLAYER && this->invulnerable != 0.0f) {
		vColor colorHolder = this->GETgraphicsComponent()->GETcolorOriginal();
		float healthRatioHolder = this->GEThp() / this->GEThpMAX();

		this->GETgraphicsComponent()->updateColor(vColor(
			(colorHolder.r * healthRatioHolder),
			(colorHolder.g * healthRatioHolder),
			(colorHolder.b * healthRatioHolder),
			(colorHolder.a * healthRatioHolder))
		);
	}
	else if (this->getType() == OBJECTTYPE::TYPE::PLAYER)
	{
		if (this->hp > this->hpMAX)
		{
			this->hp = this->hpMAX;
		}
		if (dmg > 0.0f)
		{
			Locator::getStatsHeader()->addDamageTaken(dmg);
		}
	}

	if (this->hp <= 0.0f) {
		this->hp = 0.0f;
		this->state = OBJECTSTATE::TYPE::DEAD;

		if (this->getType() == OBJECTTYPE::TYPE::ENEMY) {
			// Adds to the killcount
			Locator::getStatsHeader()->addKill();

			Locator::getAudioManager()->play(SOUND::NAME::ENEMYDEATH_3);
			Locator::getGlobalEvents()->generateMessage(GLOBALMESSAGES::ENEMYDIED);
			Locator::getGlobalEvents()->incrementEnemyDeathCount();

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
				i = new SpAutoAttackG1(this);
				break;
			case GLYPHTYPE::GLYPH2:
				i = new SpAutoAttackG2(this);
				break;
			case GLYPHTYPE::GLYPH3:
				i = new SpAutoAttackG3(this);
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
				i = new SpFireG1(this);
				break;
			case GLYPHTYPE::GLYPH2:
				i = new SpFireG2(this);
				break;
			case GLYPHTYPE::GLYPH3:
				i = new SpFireG3(this);
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
				i = new SpBombG1(this);
				break;
			case GLYPHTYPE::GLYPH2:
				i = new SpBombG2(this);
				break;
			case GLYPHTYPE::GLYPH3:
				i = new SpBombG3(this);
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
				i = new SpDashG1(this);
				break;
			case GLYPHTYPE::GLYPH2:
				i = new SpDashG2(this);
				break;
			case GLYPHTYPE::GLYPH3:
				i = new SpDashG3(this);
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
				i = new SpBuffG1(this);
				break;
			case GLYPHTYPE::GLYPH2:
				i = new SpBuffG2(this);
				break;
			case GLYPHTYPE::GLYPH3:
				i = new SpBuffG3(this);
				break;
			}
			break;
		}// i is holding the new Spell

		newSpells.push_back(i);

	}

	// Clean up old spells
	for (auto &i : this->spells) {
		delete i;
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

void ActorObject::applyStatusEffect(TILESTATE::STATE effect)
{
	this->statusEffect = effect;
	this->counter = 0.0f;
}

void ActorObject::turnOnInvulnerability()
{
	this->invulnerable = 0.0f;
	this->GETgraphicsComponent()->updateColor(vColor(0.3f, 0.3f, 0.3f, 1.0f));
}

void ActorObject::turnOffInvulnerability()
{
	this->invulnerable = 1.0f;
	vColor colorHolder = this->GETgraphicsComponent()->GETcolorOriginal();
	float healthRatioHolder = this->GEThp() / this->GEThpMAX();

	this->GETgraphicsComponent()->updateColor(vColor(
		(colorHolder.r * healthRatioHolder),
		(colorHolder.g * healthRatioHolder),
		(colorHolder.b * healthRatioHolder),
		(colorHolder.a * healthRatioHolder))
	);
}

Spell * ActorObject::getFirstSpell()
{
	if (this->spells.size() > 0) {
		return this->spells[0];
	}
	return nullptr;
}
