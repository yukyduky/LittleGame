#include "Projectile.h"
#include "AutoAttackComponent.h"

Projectile::Projectile(const size_t ID, XMFLOAT3 direction, XMFLOAT3 startPos) : GameObject(ID)
{
	this->direction = direction;
	this->startPos = startPos;
}

Projectile::~Projectile()
{
}