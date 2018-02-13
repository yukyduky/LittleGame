#pragma once
#ifndef SPFIRE_H
#define SPFIRE_H

#include "Spell.h"


class GamePlayState;

// Spells that use projectiles
class SpFire : public Spell
{
public:
	SpFire(ActorObject* player);
	~SpFire();

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
#endif // !SPFIRE_H