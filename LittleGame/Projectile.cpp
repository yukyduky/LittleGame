#include "Projectile.h"

Projectile::Projectile(const size_t ID, XMFLOAT3 direction, float travelDist) : GameObject(ID)
{
	this->direction = direction;
	this->travelDist = travelDist;
}

Projectile::~Projectile()
{
}

void Projectile::update()
{
	//Send msg with check range to comps
	//check kollison

	if (this->getState() == OBJECTSTATE::MOVING)
	{
		//this->travelDist += this->getVelocity() * Locator::getGameTime()->getDeltaTime();

		if (true)//check if range has been reached
		{

			this->setPosition(this->getPosition() + this->direction * this->getVelocity());

			//render
		}
		else
		{
			this->setState(OBJECTSTATE::STOP);
		}


	}
}