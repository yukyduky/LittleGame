#pragma once
#ifndef SPDASH_H
#define SPDASH_H

#include "Spell.h"


class GamePlayState;

// Spells that use projectiles
class SpDash : public Spell
{
public:
	SpDash(ActorObject* player, NAME name);
	~SpDash();

	bool castSpell();
	// Adds a glyph (template version of glyph so only has a float to modiy strength)
	void upgrade(float modif);
	//What the spell will do with the target
	void collision(GameObject* target, Projectile* proj);
	void update();
private:
	// Template: Modifies the spell befor glyph is implemented
	float strength;
	// Damge of skill to be applied on collision
	float damage;
	// Travel-range of spell
	int range;
};
#endif // !SPDASH_H
