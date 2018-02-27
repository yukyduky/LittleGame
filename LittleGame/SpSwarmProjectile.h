#pragma once
#ifndef SPSWARMPROJECTILE_H
#define SPSWARMPROJECTILE_H

#include "EnemySpell.h"

class SpSwarmProjectile : public EnemySpell
{
private:
	float seekSpeed = -1;

public:
	SpSwarmProjectile(
		EnemyObject* pShooter, ActorObject* pPlayer,
		int range, int dmg, int aggroRange, double cooldown
	);
	~SpSwarmProjectile();

	// Returns false if spell in unavalible to cast
	virtual bool castSpell();
	// Adds a glyph (template version of glyph so only has a float to modiy strength)
	virtual void upgrade(float modif);
	// Function called by the projectile, spells collision should be handeld here
	virtual void collision(GameObject* target, Projectile* proj);
	virtual void update();




	
};





#endif
