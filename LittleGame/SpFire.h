#pragma once
#ifndef SPFIRE_H
#define SPFIRE_H

#include "Spell.h"
#include "GameObject.h"

class GamePlayState;

// Spells that use projectiles
class SpFire : public Spell
{
public:
	SpFire(GameObject* owner);
	virtual ~SpFire();

	virtual bool castSpell();
	// Adds a glyph (template version of glyph so only has a float to modiy strength)
	void upgrade(float modif);
	//What the spell will do with the target
	virtual void collision(GameObject* target, Projectile* proj);
	virtual void update();
	void cleanUp();
protected:
	// Template: Modifies the spell befor glyph is implemented
	float strength = 0.0f;
	// Damge of skill to be applied on collision
	float damage = 0.0f;
	// Travel-range of spell
	float range = 0.0f;

	int hits = 0;
};


////////////////////////////////////////////
//// GLYPHS ////////////////////////////////////////////
////////////////////////////////////////////
// Flamethrower
class SpFireG1 : public SpFire
{
public:
	SpFireG1(GameObject* owner);
	virtual ~SpFireG1();

	bool castSpell();
private:
};

// "Snowball"-efekt
class SpFireG2 : public SpFire
{
public:
	SpFireG2(GameObject* owner);
	virtual ~SpFireG2();

	bool castSpell();
	void collision(GameObject* target, Projectile* proj);
private:
};

// Railgun
class SpFireG3 : public SpFire
{
public:
	SpFireG3(GameObject* owner);
	virtual ~SpFireG3();

	bool castSpell();
private:
};

#endif // !SPFIRE_H
