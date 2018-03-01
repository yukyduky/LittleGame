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
protected:
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



////////////////////////////////////////////
//// GLYPHS ////////////////////////////////////////////
////////////////////////////////////////////
class SpBuffG1 : public SpBuff
{
public:
	SpBuffG1(ActorObject* player);
	virtual ~SpBuffG1();
private:
};


class SpBuffG2 : public SpBuff
{
public:
	SpBuffG2(ActorObject* player);
	virtual ~SpBuffG2();
private:
};


class SpBuffG3 : public SpBuff
{
public:
	SpBuffG3(ActorObject* player);
	virtual ~SpBuffG3();
private:
};

#endif // !SPBUFF_H
