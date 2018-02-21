#include "Projectile.h"
#include "Component.h"

Projectile::Projectile(const size_t ID, float speed, bool spinn, XMFLOAT3 pos, XMFLOAT3 dir, OBJECTTYPE::TYPE objectType) : GameObject(ID, pos)
{
	//this->speed = spd;
	this->setState(OBJECTSTATE::TYPE::ACTIVATED);
	this->setType(OBJECTTYPE::PROJECTILE);
	this->spell = nullptr;

	this->type = objectType;
	this->direction = dir;
	this->speed = speed;
	this->spinn = spinn;
	this->velocity = XMFLOAT3(dir.x * this->speed, dir.y * this->speed, dir.z * this->speed);
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
}

void Projectile::setDirection(XMVECTOR dir) {
	DirectX::XMStoreFloat3(&this->direction, dir);
}

XMVECTOR Projectile::getDirection() {
	DirectX::XMVECTOR directionVector = DirectX::XMLoadFloat3(&this->direction);
	
	return directionVector;
}

void Projectile::setFollowing(float rotationSpeed, XMFLOAT3* playerPos)
{
	this->isFollowing = true;
	this->followingRotationSpeed = rotationSpeed;
}

Spell * Projectile::getSpell()
{
	return this->spell;
}



void Projectile::update()
{
	for (auto &i : this->components) {
		i->update();
	}

	// Alter velocity
	if (this->isFollowing) {
		// alter velocity depending on playerPosition
		float cos = -1.0;
		float nominator = -1.0;
		float denominator = -1.0;
		XMVECTOR mathCurrent;
		XMVECTOR mathDesired;
		XMFLOAT3 desiredDirection;
		XMFLOAT3 lengthCurrent;
		XMFLOAT3 lengthDesired;
		desiredDirection.x = (*this->pPlayerPos).x - this->pos.x;
		desiredDirection.y = (*this->pPlayerPos).x - this->pos.x;
		desiredDirection.z = (*this->pPlayerPos).x - this->pos.x;

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

		if (cos > 0) {

		}
		else {

		}
		this->velocity.x *= std::cos(degrees);
		this->velocity.y *= std::sin(degrees);
	}

	float dt = Locator::getGameTime()->getDeltaTime();
	this->pos.x += this->velocity.x * dt;
	// Projectiles dosnt move in Y
	this->pos.z += this->velocity.z * dt;
	this->setPosition(pos);
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

