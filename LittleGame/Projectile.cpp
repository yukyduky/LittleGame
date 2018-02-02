#include "Projectile.h"
#include "Component.h"

Projectile::Projectile(const size_t ID, XMFLOAT3 pos) : GameObject(ID, pos)
{
	//this->speed = spd;
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
	GameObject::update();

	if (this->state != OBJECTSTATE::DEAD)
	{
		float dt = Locator::getGameTime()->getDeltaTime();
		this->pos.x += this->velocity.x * dt;
		// Projectiles dosnt move in Y
		this->pos.z += this->velocity.z * dt;

		this->updateWorldMatrix(pos);
	}
	else
	{
		//----TEMPLATE will fix after rio has been remade
		this->setVelocity(XMFLOAT3(0,0,0));
		this->updateWorldMatrix(XMFLOAT3(0, -200, 0));
		//this->cleanUp();
		this->send(OBJECTSTATE::DEAD);
	}
}

