#include "Projectile.h"
#include "ActorObject.h"
#include "GameObject.h"
#include "Component.h"

Projectile::Projectile(const size_t ID, float velocity, bool spinn, XMFLOAT3 pos, XMFLOAT3 dir, OBJECTTYPE::TYPE objectType) : GameObject(ID, pos)
{
	this->setState(OBJECTSTATE::TYPE::ACTIVATED);
	this->setType(OBJECTTYPE::PROJECTILE);
	this->spell = nullptr;

	this->type = objectType;
	this->direction = dir;
	this->velocity = velocity;
	this->spinn = spinn;
	this->rangeCoutner = 0;
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
	float cos = -1.0;
	float nominator = -1.0;
	float denominator = -1.0;
	XMVECTOR mathCurrent;
	XMVECTOR mathDesired;
	XMFLOAT3 playerPos = this->pPlayer->GETPosition();
	XMFLOAT3 desiredDirection;
	XMFLOAT3 lengthCurrent;
	XMFLOAT3 lengthDesired;
	desiredDirection.x = (playerPos).x - this->pos.x;
	desiredDirection.y = (playerPos).y - this->pos.y;
	desiredDirection.z = (playerPos).z - this->pos.z;

	mathCurrent = XMLoadFloat3(&this->direction);			// Load into vector,
	mathCurrent = DirectX::XMVector3Length(mathCurrent);	// get dat range
	mathDesired = XMLoadFloat3(&desiredDirection);				// Load into vector,
	mathDesired = DirectX::XMVector3Length(mathDesired);		// get dat range
	XMStoreFloat3(&lengthCurrent, mathCurrent);
	XMStoreFloat3(&lengthDesired, mathDesired);

	// Using dotproduct to determine cos(degree)
	nominator = (
		(this->direction.x * desiredDirection.x) +
		(this->direction.y * desiredDirection.y) +
		(this->direction.z * desiredDirection.z)
	);
	denominator = (lengthCurrent.x * lengthDesired.x);

	// Get dat rotation
	cos = nominator / denominator;

	return cos;
}

void Projectile::turnLeft(float speed)
{
	this->direction.x *= -std::cos(speed);
	this->direction.z *= -std::cos(speed);
}

void Projectile::turnRight(float speed)
{
	this->direction.x *= std::cos(speed);
	this->direction.z *= std::cos(speed);
}

void Projectile::setDirection(XMVECTOR dir) {
	DirectX::XMStoreFloat3(&this->direction, dir);
}

XMVECTOR Projectile::getDirection() {
	DirectX::XMVECTOR directionVector = DirectX::XMLoadFloat3(&this->direction);
	
	return directionVector;
}

void Projectile::setSeeking(float seekSpeed, ActorObject* pPlayer)
{
	this->isFollowing = true;
	this->seekSpeed = seekSpeed;
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



void Projectile::update()
{
	// Alter velocity if we're gonna seek towards the player
	if (this->isFollowing) {
		// Find out 
		float cos = getAngleTowardsPlayer();

		// Turn to the right?
		if (cos > 0) {
			this->turnRight(this->seekSpeed);
		}
		// Turn to the left?
		else {
			this->turnLeft(this->seekSpeed);
		}
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

