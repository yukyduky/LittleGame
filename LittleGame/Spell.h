#pragma once
#ifndef SPELL_H
#define SPELL_H

#include "Locator.h"
#include "ActorObject.h"
#include "GamePlayState.h"
#include "BlockComponent.h"
#include "GraphicsComponent.h"
#include <algorithm>


//Template for when glyphs become relevant
enum class GLYPHTYPE {NONE, GLYPH1, GLYPH2, GLYPH3};
// Type to not need to check dynamic_cast NOT USED YET
enum class SPELLTYPE {BUFF, MOBILITY, DAMAGE};
// State to have stages of spells
enum class SPELLSTATE {READY, COOLDOWN, ACTIVE, LOCKED};

// Names of spells, usd in switchcase
enum class NAME {
	//Damage
	AUTOATTACK, FIRE, BOMB
	//Mobility
	, DASH, BUFF
};

/* --- SPELLS
1. All spells inherits from Spell
2. The player will call for castSpell when using a spell
3. Has the collision for all projectiels
4. Inserting a glyph into a spell will switch spell when actor calls "switchSpell()"
*/
class Spell
{
public:
	Spell(ActorObject* player, NAME name);
	virtual ~Spell();

	// Returns false if spell in unavalible to cast
	virtual bool castSpell() = 0;
	// Adds a glyph (template version of glyph so only has a float to modiy strength)
	virtual void upgrade(float modif) = 0;
	// Function called by the projectile, spells collision should be handeld here
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
	float getCoolDown() { return this->coolDown; };

	// TSC = TimeSinceCast
	size_t getTSC() { return this->timeSinceCast; };

private:
	//Array of glyphs
	SPELLTYPE type;
	GLYPHTYPE glyph;
	SPELLSTATE state;
	NAME name;
	ActorObject * player = nullptr;

	double coolDown = 0.0f;
	double timeSinceCast = 0.0f;
	// EnergyCost
	size_t cost = 0;
};


#endif // !SPELL_H

