#pragma once
#ifndef SPBUFF_H
#define SPBUFF_H

#include "Spell.h"


class GamePlayState;

// Spells that use projectiles
class SpBuff : public Spell
{
public:
	SpBuff(GameObject* owner);
	~SpBuff();

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
// Berserker mode - tripples all damage
class SpBuffG1 : public SpBuff
{
public:
	SpBuffG1(GameObject* owner);
	virtual ~SpBuffG1();

	bool castSpell();
	void update();
private:
};

// Enemies runs away - reverse direction vector
class SpBuffG2 : public SpBuff
{
public:
	SpBuffG2(GameObject* owner);
	virtual ~SpBuffG2();
private:
};

// Keep the movmentspeed in slow-mode
class SpBuffG3 : public SpBuff
{
public:
	SpBuffG3(GameObject* owner);
	virtual ~SpBuffG3();

	bool castSpell();
	void update();
	void collision(GameObject* target, Projectile* proj);
private:
	float timeSC = 0.0f;
};

#endif // !SPBUFF_H
