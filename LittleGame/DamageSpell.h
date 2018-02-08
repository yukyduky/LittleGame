#pragma once
#ifndef DAMAGESPELL_H
#define DAMAGESPELL_H

#include "Spell.h"
#include "Projectile.h"


class GamePlayState;

// Spells that use projectiles
class DamageSpell : public Spell
{
public:
	DamageSpell(ActorObject* player, NAME name);
	~DamageSpell();

	bool castSpell();
	void upgrade(float modif);

	// Spawns a projectile infront of the player
	void spawnProj(ProjProp props);
	// Template for when stages of spells is necsesary
	void update();

	//void collision(GameObject* target);
	//What the spell will do with the target
	void collision(GameObject* target, Projectile* proj);

private:
	// Template: Modifies the spell befor glyph is implemented
	float strength;
	// The name of the spell is what it dose
	NAME name;
	// Pointer to GamePlayState
	GamePlayState* pGPS;

	// Damge of skill to be applied on collision
	float damage;

	// Travel-range of spell
	int range;

	// Varibles for spells to use
	float varible0;
	float varible1;
	bool flag0;
};


#endif // !DAMAGESPELL_H
