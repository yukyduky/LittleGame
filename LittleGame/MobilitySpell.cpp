
#include "MobilitySpell.h"

MobilitySpell::MobilitySpell(ActorObject* player, NAME name) : Spell(player)
{
	this->strength = 1;
	this->name = name;
	this->setType(SPELLTYPE::MOBILITY);
	this->setState(SPELLSTATE::READY);
	switch (this->name)
	{
	case NAME::DASH:
		this->setCoolDown(1.3);
		this->power = 150;
		break;
	case NAME::SPEEDBUFF:
		this->setCoolDown(3.3);
		this->power = 2;
		break;
	}
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

			XMFLOAT3 distance = {this->getPlayer()->getDirection() * this->power * this->strength};
			XMFLOAT3 newPos = { this->getPlayer()->getPosition() + distance};

			/*Check for OOB*/

			this->getPlayer()->setPosition(newPos);
			//this->getPlayer()->updateWorldMatrix(newPos);
			break;
		case NAME::SPEEDBUFF:

			this->getPlayer()->setSpeed(this->power * this->strength);
			break;
		}
		this->setState(SPELLSTATE::COOLDOWN);
		
	}

	return returnValue;
}

void MobilitySpell::upgrade(float modif)
{
}
