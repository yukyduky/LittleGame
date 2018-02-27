#pragma once
#ifndef SPENEMYIMMOLATION_H
#define SPENEMYIMMOLATION_H

#include "EnemySpell.h"

class SpEnemyImmolation : public EnemySpell
{
private:

public:
	SpEnemyImmolation(
		EnemyObject* pShooter, ActorObject* pPlayer, int* pActiveEnemiesCount,
		float damage, float attackCooldown, float attackRange
	);

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
