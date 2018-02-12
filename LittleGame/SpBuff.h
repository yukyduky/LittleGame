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
	float strength;
	// Damge of skill to be applied on collision
	float damage;
	// Travel-range of spell
	int range;
};
#endif // !SPBUFF_H
