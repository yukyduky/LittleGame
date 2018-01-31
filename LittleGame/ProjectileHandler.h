#pragma once
#ifndef PROJECTILEHANDLER_H
#define PROJECTILEHANDLER_H

#include "Projectile.h"

class ProjectileHandler
{
public:
	ProjectileHandler();
	~ProjectileHandler();

	void addProj(Projectile &proj);
	void update();

private:
	std::vector<Projectile*> projectiles;
	size_t nrOf = 0;

};

#endif //PROJECTILEHANDLER_H