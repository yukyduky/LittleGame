#pragma once
#ifndef SPDASH_H
#define SPDASH_H

#include "Spell.h"


class GamePlayState;

// Spells that use projectiles
class SpDash : public Spell
{
public:
	SpDash(ActorObject* player);
	~SpDash();

	bool castSpell();
	// Adds a glyph (template version of glyph so only has a float to modiy strength)
	void upgrade(float modif);
	//What the spell will do with the target
	void collision(GameObject* target, Projectile* proj);
	void update();
	void cleanUp();

private:
	// Template: Modifies the spell befor glyph is implemented
	float strength = 0.0f;
	// Damge of skill to be applied on collision
	float damage = 0.0f;
	// Travel-range of spell
	int range = 0;

	std::vector<Projectile*> flames;
	int nrOfFlames = 0;
	float flameSize = 0.0f;
	// Workaround to making sure that the flames are gone before the user spawns new
	bool burning;
};
#endif // !SPDASH_H
