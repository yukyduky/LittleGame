#pragma once
#ifndef PROJECTILEHANDLER_H
#define PROJECTILEHANDLER_H

#include "Projectile.h"
//#include "FireballComponent.h"
//#include "PhysicsComponent.h"
//#include "GraphicsComponent.h"

class ProjectileHandler
{
public:
	ProjectileHandler();
	~ProjectileHandler();

	Projectile* makeProjectile(XMFLOAT3 start, XMFLOAT3 dir);

	void update();

private:
	std::vector<Projectile*> projectiles;

	size_t nrOf = 0;
	void addProj(Projectile &proj);

};

#endif //PROJECTILEHANDLER_H