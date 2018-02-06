#pragma once
#ifndef SPELL_H
#define SPELL_H

#include "Locator.h"
#include "ActorObject.h"
#include "GamePlayState.h"

enum class GLYPHTYPE {GLYPH1, GLYPH2, GLYPH3};
enum class SPELLTYPE {BUFF, MOBILITY, DAMAGE};
enum class SPELLSTATE {READY, COOLDOWN, TRAVLING, LOCKED};
//Spells
enum class NAME {
	//Damage
	AUTOATTACK, EXPLOSION,
	//Mobility
	DASH, SPEEDBUFF
};

class Spell
{
public:
	Spell(ActorObject* player);
	~Spell();

	//Returns false if spell in unavalible to cast
	virtual bool castSpell() = 0;
	//adds a glyph (template version of glyph so only has a float to modiy strength)
	virtual void upgrade(float modif) = 0;
	virtual void updateCD();

	ActorObject* getPlayer() { return this->player; };
	void setType(SPELLTYPE input) { this->type = input; };
	SPELLTYPE getType() { return this->type; };
	void insertGlyph(GLYPHTYPE input) { this->glyph = input; };
	void setState(SPELLSTATE input) { this->state = input; };
	SPELLSTATE getState() { return this->state; };
	void setCoolDown(double input) { this->coolDown = input; };

	size_t getTSC() { return this->timeSinceCast; };

private:
	//Array of glyphs
	SPELLTYPE type;
	GLYPHTYPE glyph;
	SPELLSTATE state;
	ActorObject * player;

	double coolDown;
	double timeSinceCast;
	size_t cost;
};


#endif // !SPELL_H

