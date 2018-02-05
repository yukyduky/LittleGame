#pragma once
#ifndef DAMAGESPELL_H
#define DAMAGESPELL_H

#include "Spell.h"
#include "Projectile.h"

class GamePlayState;

enum class NAME { EXPLOSION };

class DamageSpell : public Spell
{
public:
	DamageSpell(ActorObject* player, NAME name);
	~DamageSpell();

	bool castSpell();
	void upgrade(float modif);
	void spawnProj();
	void update();

private:
	float strength;
	NAME name;
	Projectile* proj;
	GamePlayState* pGPS;

};


#endif // !DAMAGESPELL_H
