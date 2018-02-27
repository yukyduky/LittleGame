#include "Projectile.h"
#include "ActorObject.h"
#include "GameObject.h"
#include "Component.h"
#include "IncludeSpells.h"

Projectile::Projectile(const size_t ID, float velocity, float range, bool spinn, ActorObject* shooter, XMFLOAT3 pos, XMFLOAT3 dir, OBJECTTYPE::TYPE objectType) : GameObject(ID, pos)
{
	this->setState(OBJECTSTATE::TYPE::ACTIVATED);
	this->setType(OBJECTTYPE::PROJECTILE);
	this->spell = nullptr;

	this->type = objectType;
	this->direction = dir;
	this->velocity = velocity;
	this->spinn = spinn;
	this->rangeCoutner = 0;
	this->range = range;
	this->SETrotationMatrix(shooter->getRotationMatrix());

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
	

}

Projectile::~Projectile()
{
}

void Projectile::cleanUp()
{
	for (auto &c : this->components) {
		c->cleanUp();
		delete c;
	}
	if (this->spell != nullptr) {
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

XMVECTOR Projectile::getDirection() {
	DirectX::XMVECTOR directionVector = DirectX::XMLoadFloat3(&this->direction);
	
	return directionVector;
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

Spell * Projectile::getSpell()
{
	return this->spell;
}

void Projectile::move()
{
	float dt = Locator::getGameTime()->getDeltaTime();

	this->pos.x += (this->direction.x * this->velocity) * dt;
	this->pos.z += (this->direction.z * this->velocity) * dt;
	this->setPosition(pos);
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

	this->move();

	if (this->spinn)
	{
		this->SETrotationMatrix(this->getRotationMatrix() * XMMatrixRotationAxis(this->getDirection(), this->rangeCoutner));
	}

	this->rangeCoutner++;
	if (this->rangeCoutner >= this->range && this->range != -1)
	{
		this->setState(OBJECTSTATE::TYPE::DEAD);
	}
	
}

