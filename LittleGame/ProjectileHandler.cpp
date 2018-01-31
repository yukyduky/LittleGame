#include "ProjectileHandler.h"


ProjectileHandler::ProjectileHandler()
{
}

ProjectileHandler::~ProjectileHandler()
{
}

void ProjectileHandler::addProj(Projectile &proj)
{
	this->projectiles.push_back(&proj);
	this->nrOf++;
}

void ProjectileHandler::update()
{
	for (size_t i = 0; i < this->nrOf; i++)
	{
		this->projectiles[i]->update();
	}
}
