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
	this->rangeCounter = 0;
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

Spell * Projectile::getSpell()
{
	return this->spell;
}



void Projectile::update()
{
	//GameObject::update();

	for (auto &i : this->components) {
		i->update();
	}

	float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());
	this->pos.x += this->velocity.x * dt;
	// Projectiles dosnt move in Y
	this->pos.z += this->velocity.z * dt;
	this->setPosition(pos);
	if (this->spinn)
	{
		this->SETrotationMatrix(this->getRotationMatrix() * XMMatrixRotationAxis(this->getDirection(), static_cast<float>(this->rangeCounter)));
	}

	this->rangeCounter++;
	if (this->rangeCounter >= this->range && this->range != -1.0f)
	{
		this->setState(OBJECTSTATE::TYPE::DEAD);
	}
	
}

