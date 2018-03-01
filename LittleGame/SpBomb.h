#pragma once
#ifndef SPBOMB_H
#define SPBOMB_H

#include "Spell.h"


class GamePlayState;

// Spells that use projectiles
class SpBomb : public Spell
{
public:
	SpBomb(ActorObject* player);
	virtual ~SpBomb();

	bool castSpell();
	// Adds a glyph (template version of glyph so only has a float to modiy strength)
	void upgrade(float modif);
	//What the spell will do with the target
	void collision(GameObject* target, Projectile* proj);
	void update();
private:
	// Template: Modifies the spell befor glyph is implemented
	float strength = 0.0f;
	// Damge of skill to be applied on collision
	float damage = 0.0f;
	// Travel-range of spell
	float range = 0.0f;

	Projectile* theProj = nullptr;
	float start, end, collisionDuration;
};
#endif // !SPBOMB_H
