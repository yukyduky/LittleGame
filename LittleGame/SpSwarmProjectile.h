#pragma once
#ifndef SPSWARMPROJECTILE_H
#define SPSWARMPROJECTILE_H

#include "EnemySpell.h"

class SpSwarmProjectile : public EnemySpell
{
private:
	float seekSpeed = -1;
	float originalVelocity;
	float currentVelocity;
	float originalRange;
	float currentRange;

public:
	SpSwarmProjectile(
		EnemyObject* pShooter, ActorObject* pPlayer, int* pActiveEnemiesCount,
		int range, int dmg, int attackRange, double cooldown, float projectileVelocity
	);
	~SpSwarmProjectile();


	void setProjectileVelocity(float projectileVelocity);
	float getOriginalProjectileVelocity();
	void setProjectileRange(float projectileRange);
	float getOriginalProjectileRange();

	// Returns false if spell in unavalible to cast
	bool castSpell();
	// Adds a glyph (template version of glyph so only has a float to modiy strength)
	void upgrade(float modif);
	// Function called by the projectile, spells collision should be handeld here
	void collision(GameObject* target, Projectile* proj);
	void update();
	void cleanUp();




	
};





#endif
