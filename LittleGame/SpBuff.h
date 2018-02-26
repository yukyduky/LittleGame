#pragma once
#ifndef SPBUFF_H
#define SPBUFF_H

#include "Spell.h"


class GamePlayState;

// Spells that use projectiles
class SpBuff : public Spell
{
public:
	SpBuff(ActorObject* player);
	~SpBuff();

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
	// If the efect is active
	bool active;
	// value to increase to make the player float
	float floatingValue = 0.0f;
	// to reset the player after efect wears of
	float oriY, oriRadius;
	// needs to be lower than CD.
	float duration = 0.0f;
};
#endif // !SPBUFF_H
