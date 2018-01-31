#include "Projectile.h"

Projectile::Projectile(const size_t ID, XMFLOAT3 start, XMFLOAT3 direction) : GameObject(ID, start)
{
	this->direction = direction;
	this->travelDist = 0;
	this->speed = this->getVelocity().Length();
}

Projectile::~Projectile()
{
}

void Projectile::update()
{
	//Send msg with check range to comps
	this->travelDist += this->speed * Locator::getGameTime()->getDeltaTime();
	this->send(COMPMSG::CHE_RANGE);

	//check kollison
	this->send(COMPMSG::CHE_COLISION);

	if (this->getState() == OBJECTSTATE::MOVING)
	{

		this->setPosition(this->getPosition() + this->direction * this->speed);
	}


}