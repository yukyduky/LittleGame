#pragma once
#ifndef SPNO_H
#define SPNO_H

#include "EnemySpell.h"


class GamePlayState;

// No glyph
class SpNo : public EnemySpell
{
public:
	SpNo(EnemyObject* pShooter, int* pActiveEnemiesCount, NAME name) 
		: EnemySpell(pShooter, pActiveEnemiesCount, name)
	{

	}
	virtual ~SpNo() {

	}

	virtual bool castSpell() {
		return true;
	}
	// Adds a glyph (template version of glyph so only has a float to modiy strength)
	void upgrade(float modif) {

	}
	//What the spell will do with the target
	virtual void collision(GameObject* target, Projectile* proj) {

	}
	void update() {

	}
	void cleanUp() {
		(*this->pActiveEnemiesCount)--;
	}

protected:
	// Template: Modifies the spell befor glyph is implemented
	float strength = 0.0f;
	// Damge of skill to be applied on collision
	float damage = 0.0f;
	// Travel-range of spell
	float range = 0.0f;
};

#endif // !SPAUTOATTACK_H
