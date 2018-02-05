#pragma once
#ifndef MOBILITYSPELL_H
#define MOBILITYSPELL_H

#include "Spell.h"
#include "ActorObject.h"

enum class NAME { DASH };

class MobilitySpell : public Spell
{
public:
	MobilitySpell(NAME name, ActorObject* player);
	~MobilitySpell();

	bool castSpell();
	void upgrade(float modif);

private:
	ActorObject * player;
	float strength;
	NAME name;

};

#endif // !MOBILITYSPELL_H