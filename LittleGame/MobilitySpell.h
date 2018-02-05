#pragma once
#ifndef MOBILITYSPELL_H
#define MOBILITYSPELL_H

#include "Spell.h"

enum class NAME { DASH };

class MobilitySpell : public Spell
{
public:
	MobilitySpell(ActorObject* player, NAME name);
	~MobilitySpell();

	bool castSpell();
	void upgrade(float modif);

private:
	float strength;
	NAME name;

};

#endif // !MOBILITYSPELL_H