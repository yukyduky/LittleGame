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

	virtual bool castSpell();
	// Adds a glyph (template version of glyph so only has a float to modiy strength)
	void upgrade(float modif);
	//What the spell will do with the target
	virtual void collision(GameObject* target, Projectile* proj);
	virtual void update();
protected:
	// Template: Modifies the spell befor glyph is implemented
	float strength = 0.0f;
	// Damge of skill to be applied on collision
	float damage = 0.0f;
	// Travel-range of spell
	float range = 0.0f;

	std::vector<Projectile*> flames;
	int nrOfFlames = 0;
	float flameSize = 0.0f;
	// Workaround to making sure that the flames are gone before the user spawns new
	bool burning;
};

////////////////////////////////////////////
//// GLYPHS ////////////////////////////////////////////
////////////////////////////////////////////
class SpDashG1 : public SpDash
{
public:
	SpDashG1(ActorObject* player);
	virtual ~SpDashG1();

	bool castSpell();
	void collision(GameObject* target, Projectile* proj);
	void update();
private:
};


class SpDashG2 : public SpDash
{
public:
	SpDashG2(ActorObject* player);
	virtual ~SpDashG2();

	bool castSpell();
private:
	float damageFromMiss;
};


class SpDashG3 : public SpDash
{
public:
	SpDashG3(ActorObject* player);
	virtual ~SpDashG3();
private:
	bool castSpell();
	void update();
};

#endif // !SPDASH_H
