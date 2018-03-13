#include "Projectile.h"
#include "ActorObject.h"
#include "GameObject.h"
#include "Component.h"
#include "RenderInputOrganizer.h"
#include "IncludeSpells.h"

Projectile::Projectile() : GameObject(-1)
{
	this->setState(OBJECTSTATE::TYPE::DEAD);
}

Projectile::Projectile(const size_t ID, float velocity, float maxFlyingRange, PROJBEHAVIOR behavior, GameObject* shooter, XMFLOAT3 pos, XMFLOAT3 dir, OBJECTTYPE::TYPE objectType, size_t lightID, idlist<Light>* lights) : GameObject(ID, pos)
{
	this->setState(OBJECTSTATE::TYPE::ACTIVATED);
	this->setType(OBJECTTYPE::PROJECTILE);
	this->spell = nullptr;

	this->type = objectType;
	this->moveDirection = dir;
	this->velocityMagnitude = velocity;
	this->spinn = spinn;
	this->kineticVector = XMFLOAT3(dir.x * this->speed, dir.y * this->speed, dir.z * this->speed);
	this->rangeCounter = 0;
	this->maxFlyingRange = maxFlyingRange;

	this->lightID = lightID;
	this->lights = lights;
}

Projectile::~Projectile()
{
}

void Projectile::cleanUp()
{
	this->lights->remove(lightID);

	for (auto &c : this->components) {
		c->cleanUp();
		delete c;
	}

	// Detta tar bort spelarens egna spell
	//if (this->spell != nullptr && this->spell->getOwner()->getType() != OBJECTTYPE::PLAYER) {
	delete this->spell;
	//}
}

float Projectile::getAngleTowardsPlayer()
{
	// Prepare to convert into XMVECTOR
	float angle;
	XMFLOAT3 floatAngle;
	XMFLOAT3 playerPos = this->pPlayer->GETPosition();
	XMFLOAT3 floatToPlayer;
	floatToPlayer.x = (playerPos).x - this->pos.x;
	floatToPlayer.y = (playerPos).y - this->pos.y;
	floatToPlayer.z = (playerPos).z - this->pos.z;

	// Convert to XMVECTOR
	XMVECTOR vecCurrentmoveDirection = XMLoadFloat3(&this->moveDirection);
	XMVECTOR vecDesiredmoveDirection = XMLoadFloat3(&floatToPlayer);;

	// Use optimized math
	XMVECTOR vecAngle = XMVector3AngleBetweenVectors(vecDesiredmoveDirection, vecCurrentmoveDirection);
	XMStoreFloat3(&floatAngle, vecAngle);	// x,y,z of floatAngle all contain the same angle.
	angle = floatAngle.x;		// I'd only like 1 of the values thank you!

	return angle;
}

void Projectile::turnLeft()
{
	float dt = Locator::getGameTime()->getDeltaTime();
	XMFLOAT3 floatUp(0, 1, 0);
	
	// Convert into XMVECTOR for optimization
	XMVECTOR vecmoveDirection = XMLoadFloat3(&this->moveDirection);
	XMVECTOR vecUp = XMLoadFloat3(&floatUp);
	
	// Rotate with quaternions so no axis-locks happen
	XMVECTOR rotationQuaternion = XMQuaternionRotationAxis(vecUp, -this->rotationSpeed*dt);
	vecmoveDirection = DirectX::XMVector3Rotate(vecmoveDirection, rotationQuaternion);

	// Convert back into XMFloat
	XMStoreFloat3(&this->moveDirection, vecmoveDirection);
}

void Projectile::turnRight()
{
	float dt = Locator::getGameTime()->getDeltaTime();
	XMFLOAT3 floatUp(0, 1, 0);

	// Convert into XMVECTOR for optimization
	XMVECTOR vecmoveDirection = XMLoadFloat3(&this->moveDirection);
	XMVECTOR vecUp = XMLoadFloat3(&floatUp);

	// Rotate with quaternions so no axis-locks happen
	XMVECTOR rotationQuaternion = XMQuaternionRotationAxis(vecUp, this->rotationSpeed*dt);
	vecmoveDirection = DirectX::XMVector3Rotate(vecmoveDirection, rotationQuaternion);

	// Convert back into XMFloat
	XMStoreFloat3(&this->moveDirection, vecmoveDirection);
}

void Projectile::setDirection(XMVECTOR dir) {
	DirectX::XMStoreFloat3(&this->moveDirection, dir);
}

DirectX::XMFLOAT3 Projectile::getDirection()
{	
	return this->moveDirection;
}

void Projectile::setSeeking(float rotationSpeed, ActorObject* pPlayer)
{
	this->isFollowing = true;
	this->rotationSpeed = rotationSpeed;
	this->pPlayer = pPlayer;
}

void Projectile::setSpell(Spell * spell)
{
	this->spell = spell;
}

void Projectile::setSpellByName(int spellName, int glyph)
{
	Spell* i = nullptr; // Will hold the new spell to be set into the proj
	NAME name = (NAME)spellName;
	GLYPHTYPE glyphtype = (GLYPHTYPE)glyph;

	switch (name)
	{

	case NAME::AUTOATTACK:
		// Looks at what new spell will replace depending on what glyph has been added to the spell
		switch (glyphtype)
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
		switch (glyphtype)
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
		switch (glyphtype)
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
		switch (glyphtype)
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
		switch (glyphtype)
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

	this->spell = i;
}

Spell * Projectile::getSpell()
{
	return this->spell;
}

void Projectile::move()
{
	XMFLOAT3 traveledDistance = XMFLOAT3(0.0f, 0.0f, 0.0f);
	float dt = Locator::getGameTime()->getDeltaTime();

	// Save old position to relevant targets
	this->previousPos = this->pos;

	this->pos.x += (this->moveDirection.x * this->velocityMagnitude) * dt;
	this->pos.z += (this->moveDirection.z * this->velocityMagnitude) * dt;

	traveledDistance = this->pos - this->previousPos;
	XMVECTOR dist = XMLoadFloat3(&traveledDistance);
	dist = XMVector3Length(dist);
	XMStoreFloat3(&traveledDistance, dist);
	this->rangeCounter += traveledDistance.x;

	if (this->rangeCounter >= this->maxFlyingRange && this->maxFlyingRange != -1) {
		this->setState(OBJECTSTATE::TYPE::DEAD);
	}
	else {
		this->setPosition(pos);
	}

	// Save new position to relevant targets
	(*this->lights).getElementByID(this->lightID).pos = pos;
}

void Projectile::steerTowardsPlayer()
{
	float dt = Locator::getGameTime()->getDeltaTime();
	XMFLOAT3 playerPos = this->pPlayer->GETPosition();
	XMFLOAT3 desiredDirection;
	XMFLOAT3 steeringDirection;

	// Calculate desired direction
	desiredDirection.x = playerPos.x - this->pos.x;
	desiredDirection.y = playerPos.y - this->pos.y;
	desiredDirection.z = playerPos.z - this->pos.z;

	// Normalize it
	XMVECTOR vecDesired = DirectX::XMLoadFloat3(&desiredDirection);
	vecDesired = XMVector3Normalize(vecDesired);
	DirectX::XMStoreFloat3(&desiredDirection, vecDesired);

	// Calculate the steering direction
	steeringDirection.x = desiredDirection.x - this->moveDirection.x;
	steeringDirection.y = desiredDirection.y - this->moveDirection.y;
	steeringDirection.z = desiredDirection.z - this->moveDirection.z;

	// Normalize it
	XMVECTOR vecSteering = DirectX::XMLoadFloat3(&steeringDirection);
	vecDesired = XMVector3Normalize(vecSteering);
	DirectX::XMStoreFloat3(&steeringDirection, vecSteering);

	// Affect the current direction
	this->moveDirection.x += steeringDirection.x * this->rotationSpeed * dt;
	this->moveDirection.y += steeringDirection.y * this->rotationSpeed * dt;
	this->moveDirection.z += steeringDirection.z * this->rotationSpeed * dt;

	// Then normalize the current direction
	XMVECTOR vecDirection = DirectX::XMLoadFloat3(&this->moveDirection);
	vecDirection = XMVector3Normalize(vecDirection);
	DirectX::XMStoreFloat3(&this->moveDirection, vecDirection);
}



void Projectile::update()
{
	// Alter velocity if we're gonna seek towards the player
	if (this->isFollowing) {
		steerTowardsPlayer();
	}

	for (auto &i : this->components) {
		i->update();
	}
	
	this->spell->update();

	this->move();

	if (this->spinn)
	{
		XMVECTOR dir = XMLoadFloat3(&this->moveDirection);
		XMMATRIX rotM = XMLoadFloat4x4(&this->getRotationMatrix());
		this->SETrotationMatrix(rotM * XMMatrixRotationAxis(dir, static_cast<float>(this->rangeCounter)));
	}

	/*
	this->rangeCounter++;
	if (this->rangeCounter >= this->maxFlyingRange && this->maxFlyingRange != -1)
	{
		this->setState(OBJECTSTATE::TYPE::DEAD);
	}
	*/
	
}
