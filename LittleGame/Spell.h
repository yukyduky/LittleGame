#pragma once
#ifndef SPELL_H
#define SPELL_H

#include "Locator.h"
#include "ActorObject.h"
#include "GamePlayState.h"

/* --- HOW TO ADD SPELLS
1. Add the name in the NAME enum
2. Add it to one of the slots in the initiation of the player
3. Make seperate switch-cases in the functions of the correct sub-class
*/

//Template for when glyphs become relevant
enum class GLYPHTYPE {NONE, GLYPH1, GLYPH2, GLYPH3};
// Type to not need to check dynamic_cast
enum class SPELLTYPE {BUFF, MOBILITY, DAMAGE};
// State to have stages of spells
enum class SPELLSTATE {READY, COOLDOWN, ACTIVE, LOCKED};

// Names of spells, usd in switchcase
enum class NAME {
	//Damage
	AUTOATTACK, FIRE, BOMB
	//Mobility
	, DASH, SPEEDBUFF
};

class Spell
{
public:
	Spell(ActorObject* player, NAME name);
	~Spell();

	// Returns false if spell in unavalible to cast
	virtual bool castSpell() = 0;
	// Adds a glyph (template version of glyph so only has a float to modiy strength)
	virtual void upgrade(float modif) = 0;
	//What the spell will do with the target
	virtual void collision(GameObject* target, Projectile* proj) = 0;
	virtual void update() = 0;

	// called in each frame to decrese the cooldown of each spell
	virtual void updateCD();
	// Spawns a projectile infront of the player
	Projectile* spawnProj(ProjProp props);

	ActorObject* getPlayer() { return this->player; };
	void setType(SPELLTYPE input) { this->type = input; };
	SPELLTYPE getType() { return this->type; };
	void insertGlyph(GLYPHTYPE input) { this->glyph = input; };
	GLYPHTYPE getGlyph() { return this->glyph; };
	NAME getName() { return this->name; };
	void setState(SPELLSTATE input) { this->state = input; };
	SPELLSTATE getState() { return this->state; };
	void setCoolDown(double input) { this->coolDown = input; };

	// TSC = TimeSinceCast
	size_t getTSC() { return this->timeSinceCast; };

private:
	//Array of glyphs
	SPELLTYPE type;
	GLYPHTYPE glyph;
	SPELLSTATE state;
	ActorObject * player;


	NAME name;

	double coolDown;
	double timeSinceCast;
	// EnergyCost
	size_t cost;
};


#endif // !SPELL_H

