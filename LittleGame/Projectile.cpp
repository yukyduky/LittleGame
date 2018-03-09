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

Projectile::Projectile(const size_t ID, float velocity, float maxFlyingRange, PROJBEHAVIOR behavior, GameObject* shooter, XMFLOAT3 pos, XMFLOAT3 dir, OBJECTTYPE::TYPE objectType, std::pair<size_t, Light*> light, IDHandler* lightIDs) : GameObject(ID, pos)
{
	this->setState(OBJECTSTATE::TYPE::ACTIVATED);
	this->setType(OBJECTTYPE::PROJECTILE);
	this->spell = nullptr;

	this->type = objectType;
	this->direction = dir;
	this->velocity = velocity;
	this->spinn = false;
	this->rangeCounter = 0;
	this->maxFlyingRange = maxFlyingRange;
	
	// Dose nothing, the matrix is assigned as 0,0,0 when it gets the blockcomp
	// This is instead done in spawnProj
	//this->SETrotationMatrix(DirectX::XMLoadFloat4x4(&shooter->getRotationMatrix()));

	// IGNORE THIS ATM, IT IS AN OPTIMIZATION WHICH COULD BE IMPLEMENTED (setSpell should be done inside the constructor)
	//Spell* projectilesSpell = nullptr;

	//switch (this->name) {
	//case NAME::AUTOATTACK: {
	//	projectilesSpell = new SpAutoAttack(shooter);
	//	break;
	//}
	//case NAME::BOMB: {
	//	projectilesSpell = new SpBomb(shooter);
	//	break;
	//}
	//case NAME::DASH: {
	//	projectilesSpell = new SpDash(shooter);
	//	break;
	//}
	//case NAME::FIRE: {
	//	projectilesSpell = new SpFire(shooter);
	//	break;
	//}
	//case NAME::ENEM_SWARM: {
	////	SpSwarmProjectile* trueThis = static_cast<SpSwarmProjectile*>(this);
	//	EnemyObject* trueCaster = static_cast<EnemyObject*>(shooter);

	//	projectilesSpell = new SpSwarmProjectile(
	//		shooter, trueThis->getRange(), trueThis->getDamage(),
	//		trueThis->getAggroRange(), trueThis->getCoolDown()
	//	);
	//	break;
	//}
	//}

	//this->spell = projectilesSpell;
	


	this->light = light;
	this->lightIDs = lightIDs;
}

//Projectile::Projectile(const size_t ID, float velocity, PROJBEHAVIOR behavior, XMFLOAT3 pos, XMFLOAT3 dir, OBJECTTYPE::TYPE objectType, std::pair<size_t, Light*> light, IDHandler * lightIDs) : GameObject(ID, pos)
//{
//	this->setState(OBJECTSTATE::TYPE::ACTIVATED);
//	this->setType(OBJECTTYPE::PROJECTILE);
//	this->spell = nullptr;
//
//	this->type = objectType;
//	this->direction = dir;
//	this->behavior = behavior;
//	this->velocity = velocity;
//	this->rangeCounter = 0;
//
//	this->light = light;
//	this->lightIDs = lightIDs;
//}

Projectile::~Projectile()
{
}

void Projectile::cleanUp()
{
	this->lightIDs->remove(this->light.first);
	this->light.second->diffuse = XMFLOAT3(0.0f, 0.0f, 0.0f);
	this->light.second->ambient = XMFLOAT3(0.0f, 0.0f, 0.0f);

	for (auto &c : this->components) {
		c->cleanUp();
		delete c;
	}

	// Detta tar bort spelarens egna spell
	if (this->spell != nullptr && this->spell->getOwner()->getType() != OBJECTTYPE::PLAYER) {
		delete this->spell;
	}
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
	XMVECTOR vecCurrentDirection = XMLoadFloat3(&this->direction);
	XMVECTOR vecDesiredDirection = XMLoadFloat3(&floatToPlayer);;

	// Use optimized math
	XMVECTOR vecAngle = XMVector3AngleBetweenVectors(vecDesiredDirection, vecCurrentDirection);
	XMStoreFloat3(&floatAngle, vecAngle);	// x,y,z of floatAngle all contain the same angle.
	angle = floatAngle.x;		// I'd only like 1 of the values thank you!

	return angle;
}

void Projectile::turnLeft()
{
	float dt = Locator::getGameTime()->getDeltaTime();
	XMFLOAT3 floatUp(0, 1, 0);
	
	// Convert into XMVECTOR for optimization
	XMVECTOR vecDirection = XMLoadFloat3(&this->direction);
	XMVECTOR vecUp = XMLoadFloat3(&floatUp);
	
	// Rotate with quaternions so no axis-locks happen
	XMVECTOR rotationQuaternion = XMQuaternionRotationAxis(vecUp, -this->rotationSpeed*dt);
	vecDirection = DirectX::XMVector3Rotate(vecDirection, rotationQuaternion);

	// Convert back into XMFloat
	XMStoreFloat3(&this->direction, vecDirection);
}

void Projectile::turnRight()
{
	float dt = Locator::getGameTime()->getDeltaTime();
	XMFLOAT3 floatUp(0, 1, 0);

	// Convert into XMVECTOR for optimization
	XMVECTOR vecDirection = XMLoadFloat3(&this->direction);
	XMVECTOR vecUp = XMLoadFloat3(&floatUp);

	// Rotate with quaternions so no axis-locks happen
	XMVECTOR rotationQuaternion = XMQuaternionRotationAxis(vecUp, this->rotationSpeed*dt);
	vecDirection = DirectX::XMVector3Rotate(vecDirection, rotationQuaternion);

	// Convert back into XMFloat
	XMStoreFloat3(&this->direction, vecDirection);
}

void Projectile::setDirection(XMVECTOR dir) {
	DirectX::XMStoreFloat3(&this->direction, dir);
}

DirectX::XMFLOAT3 Projectile::getDirection()
{	
	return this->direction;
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
	this->previousPos = this->pos;

	this->pos.x += (this->direction.x * this->velocity) * dt;
	this->pos.z += (this->direction.z * this->velocity) * dt;

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
	steeringDirection.x = desiredDirection.x - this->direction.x;
	steeringDirection.y = desiredDirection.y - this->direction.y;
	steeringDirection.z = desiredDirection.z - this->direction.z;

	// Normalize it
	XMVECTOR vecSteering = DirectX::XMLoadFloat3(&steeringDirection);
	vecDesired = XMVector3Normalize(vecSteering);
	DirectX::XMStoreFloat3(&steeringDirection, vecSteering);

	// Affect the current direction
	this->direction.x += steeringDirection.x * this->rotationSpeed * dt;
	this->direction.y += steeringDirection.y * this->rotationSpeed * dt;
	this->direction.z += steeringDirection.z * this->rotationSpeed * dt;

	// Then normalize the current direction
	XMVECTOR vecDirection = DirectX::XMLoadFloat3(&this->direction);
	vecDirection = XMVector3Normalize(vecDirection);
	DirectX::XMStoreFloat3(&this->direction, vecDirection);
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
	this->light.second->pos = pos;

	if (this->spinn)
	{
		XMVECTOR dir = XMLoadFloat3(&this->direction);
		XMMATRIX rotM = XMLoadFloat4x4(&this->getRotationMatrix());
		this->SETrotationMatrix(rotM * XMMatrixRotationAxis(dir, static_cast<float>(this->rangeCounter)));
	}
	else if (this->behavior == PROJBEHAVIOR::ENLARGE)
	{
		float size = this->rangeCounter * 4.0f;
		XMMATRIX scaleM = XMMatrixScaling(size, size, size);
		this->GETphysicsComponent()->updateBoundingArea(size);
		this->SETscaleMatrix(scaleM);
	}

	/*
	this->rangeCounter++;
	if (this->rangeCounter >= this->maxFlyingRange && this->maxFlyingRange != -1)
	{
		this->setState(OBJECTSTATE::TYPE::DEAD);
	}
	*/
	
}

