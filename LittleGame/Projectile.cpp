#include "Projectile.h"
#include "Component.h"

Projectile::Projectile(const size_t ID, float speed, XMFLOAT3 pos, XMFLOAT3 dir, OBJECTTYPE::TYPE objectType) : GameObject(ID, pos)
{
	//this->speed = spd;
	this->setState(OBJECTSTATE::TYPE::MOVING);
	this->setType(OBJECTTYPE::PROJECTILE);
	this->spell = nullptr;

	this->type = objectType;
	this->direction = dir;
	this->speed = speed;
	this->velocity = XMFLOAT3(this->direction.x * this->speed, this->direction.y * this->speed, this->direction.z * this->speed);
	this->rangeCoutner = 0;
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

	if (this->state == OBJECTSTATE::TYPE::DEAD)
	{
		//----TEMPLATE will fix after rio has been remade
		this->setVelocity(XMFLOAT3(0, 0, 0));
		this->setPosition(XMFLOAT3(0, -200, 0));
		//this->cleanUp();
		this->send(OBJECTSTATE::TYPE::DEAD);
	}
	else
	{
		float dt = Locator::getGameTime()->getDeltaTime();
		this->pos.x += this->velocity.x * dt;
		// Projectiles dosnt move in Y
		this->pos.z += this->velocity.z * dt;
		this->setPosition(pos);

		this->rangeCoutner++;
		if (this->rangeCoutner >= this->range && this->range != -1)
		{
			this->setState(OBJECTSTATE::TYPE::DEAD);
		}
	}
}

