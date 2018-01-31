#include "ProjectileHandler.h"


ProjectileHandler::ProjectileHandler()
{
}

ProjectileHandler::~ProjectileHandler()
{
}

Projectile* ProjectileHandler::makeProjectile(XMFLOAT3 start, XMFLOAT3 dir)
{
	Projectile proj(nrOf, start, dir);
	
	this->addProj(proj);

	return &proj;
}

void ProjectileHandler::addProj(Projectile &proj)
{
	this->projectiles.push_back(&proj);
	this->nrOf = this->projectiles.size();
}

void ProjectileHandler::update()
{
	for (size_t i = 0; i < this->nrOf; i++)
	{
		this->projectiles[i]->update();
		if (this->projectiles[i]->getState() == OBJECTSTATE::STOP)
		{
			this->projectiles.erase(this->projectiles.begin() + i);
		}
	}
}
