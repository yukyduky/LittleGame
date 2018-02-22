#pragma once
#ifndef SPAUTOATTACK_H
#define SPAUTOATTACK_H

#include "Spell.h"


class GamePlayState;

// Spells that use projectiles
class SpAutoAttack : public Spell
{
public:
	SpAutoAttack(ActorObject* player);
	virtual ~SpAutoAttack();

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
};
#endif // !SPAUTOATTACK_H
