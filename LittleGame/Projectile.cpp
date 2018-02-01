#include "Projectile.h"

Projectile::Projectile(const size_t ID, XMFLOAT3 pos, float spd) : GameObject(ID, pos)
{
	this->speed = spd;
	this->setState(OBJECTSTATE::MOVING);
}

Projectile::~Projectile()
{

}

void Projectile::cleanUp()
{
}
