#include "Projectile.h"
#include "Component.h"

Projectile::Projectile(const size_t ID, XMFLOAT3 pos, float spd) : GameObject(ID, pos)
{
	this->speed = spd;
	this->setState(OBJECTSTATE::MOVING);
}

Projectile::~Projectile()
{
	this->cleanUp();
}

void Projectile::cleanUp()
{
	for (auto &c : this->components) {
		c->getID();
		c->cleanUp();
		delete c;
	}
}

void Projectile::update()
{
	float dt = Locator::getGameTime()->getDeltaTime();
	this->pos.x += this->velocity.x * dt;
	// Projectiles dosnt move in Y
	//this->pos.y += this->velocity.y * dt;
	this->pos.z += this->velocity.z * dt;

	this->updateWorldMatrix(pos);
}

