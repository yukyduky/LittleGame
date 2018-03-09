#pragma once
#ifndef SPBOMB_H
#define SPBOMB_H

#include "Spell.h"


class GamePlayState;

// Spells that use projectiles
class SpBomb : public Spell
{
public:
	SpBomb();
	virtual ~SpBomb();

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

	Projectile* theProj = nullptr;
	XMFLOAT3 currPos;
	float start, end, collisionDuration;

	bool landed = false;
	float yAcc = 0.0f;
};

////////////////////////////////////////////
//// GLYPHS ////////////////////////////////////////////
////////////////////////////////////////////
// Splinterbomb
class SpBombG1 : public SpBomb
{
public:
	SpBombG1();
	virtual ~SpBombG1();

	void update();
private:
	int nrOfSplinters = 0;
};

// Mine
class SpBombG2 : public SpBomb
{
public:
	SpBombG2();
	virtual ~SpBombG2();

	void collision(GameObject* target, Projectile* proj);
	void update();
private:
	bool trip = false;
};

// Blackhole 
class SpBombG3 : public SpBomb
{
public:
	SpBombG3();
	virtual ~SpBombG3();
private:
};

#endif // !SPBOMB_H
