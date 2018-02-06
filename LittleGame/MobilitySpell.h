#pragma once
#ifndef MOBILITYSPELL_H
#define MOBILITYSPELL_H

#include "Spell.h"


class MobilitySpell : public Spell
{
public:
	MobilitySpell(ActorObject* player, NAME name);
	~MobilitySpell();

	bool castSpell();
	void upgrade(float modif);

private:
	//Modifier to be upgraded
	float strength;
	NAME name;
	//For balance
	float power;
};

#endif // !MOBILITYSPELL_H