#pragma once
#ifndef SPELL_H
#define SPELL_H

#include "Locator.h"

enum class GLYPHTYPE {GLYPH1, GLYPH2, GLYPH3};
enum class SPELLTYPE {BUFF, MOBILITY, DAMAGE};
enum class SPELLSTATE {READY, COOLDOWN, LOCKED};

class Spell
{
public:
	Spell();
	~Spell();

	virtual bool castSpell() = 0;
	virtual void upgrade() = 0;
	void updateCD();

	void setType(SPELLTYPE input) { this->type = input; };
	void insertGlyph(GLYPHTYPE input) { this->glyph = input; };
	void setState(SPELLSTATE input) { this->state = input; };
	void setCoolDown(size_t input) { this->coolDown = input; };

private:
	//Array of glyphs
	SPELLTYPE type;
	GLYPHTYPE glyph;
	SPELLSTATE state;

	size_t coolDown;
	size_t timeSinceCast;
	size_t cost;
};


#endif // !SPELL_H

