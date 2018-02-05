
#include "MobilitySpell.h"

MobilitySpell::MobilitySpell(NAME name, ActorObject* player)
{
	this->player = player;
	this->strength = 1;
	this->name = name;
}

MobilitySpell::~MobilitySpell()
{
}

bool MobilitySpell::castSpell()
{
	return false;
}

void MobilitySpell::upgrade(float modif)
{
}
