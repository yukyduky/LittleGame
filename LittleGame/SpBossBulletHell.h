#pragma once
#ifndef SPBOSSBULLETHELL_H_
#define SPBOSSBULLETHELL_H_

#include "EnemySpell.h"

class SpBossBulletHell : public EnemySpell
{
private:
	float radians = 0.3f;
public:
	SpBossBulletHell(EnemyObject* pShooter, ActorObject* pPlayer, int* pActiveEnemiesCount,
		int range, int dmg, int attackRange, double cooldown
	);
	~SpBossBulletHell();
	// 
	bool castSpell();
	// Adds a glyph (template version of glyph so it only has a float to modify strength)
	void upgrade(float modif);
	// Function called by the projectile, spells collision should be handled here
	void collision(GameObject* target, Projectile* proj);
	void update();
	void cleanUp();

};
#endif