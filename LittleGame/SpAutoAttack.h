#pragma once
#ifndef SPAUTOATTACK_H
#define SPAUTOATTACK_H

#include "Spell.h"


class GamePlayState;

// Spells that use projectiles
class SpAutoAttack : public Spell
{
public:
	SpAutoAttack(ActorObject* player);
	virtual ~SpAutoAttack();

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
};

////////////////////////////////////////////
//// GLYPHS ////////////////////////////////////////////
////////////////////////////////////////////
class SpAutoAttackG1 : public SpAutoAttack
{
public:
	SpAutoAttackG1(ActorObject* player);
	virtual ~SpAutoAttackG1();
private:
};


class SpAutoAttackG2 : public SpAutoAttack
{
public:
	SpAutoAttackG2(ActorObject* player);
	virtual ~SpAutoAttackG2();
private:
};


class SpAutoAttackG3 : public SpAutoAttack
{
public:
	SpAutoAttackG3(ActorObject* player);
	virtual ~SpAutoAttackG3();
private:
};

#endif // !SPAUTOATTACK_H
