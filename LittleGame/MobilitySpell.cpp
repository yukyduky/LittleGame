
#include "MobilitySpell.h"

MobilitySpell::MobilitySpell(ActorObject* player, NAME name) : Spell(player)
{
	this->strength = 1;
	this->name = name;
	this->setType(SPELLTYPE::MOBILITY);

}

MobilitySpell::~MobilitySpell()
{
}

bool MobilitySpell::castSpell()
{
	bool returnValue = true;
	if (this->getState() == SPELLSTATE::COOLDOWN)
	{
		returnValue = false;
	}
	else
	{
		switch (this->name)
		{
		case NAME::DASH:

			XMFLOAT3 distance = {this->getPlayer()->getDirection() * 2 * this->strength};
			XMFLOAT3 newPos = {};

			this->getPlayer()->setPosition(this->getPlayer()->GETPosition() /*INSERT POS + DIRECTION * DISTANCE * STREGTH*/);

			break;
		}
		
	}

	return returnValue;
}

void MobilitySpell::upgrade(float modif)
{
}
