
#include "Spell.h"

Spell::Spell(ActorObject* player)
{
	this->player = player;
	this->timeSinceCast = 0.0;
	this->cost = 0;
}

Spell::~Spell()
{
}

void Spell::updateCD()
{
	if (this->state == SPELLSTATE::COOLDOWN)
	{
		this->timeSinceCast += Locator::getGameTime()->getDeltaTime();
		if (this->timeSinceCast >= this->coolDown)
		{
			this->state = SPELLSTATE::READY;
			this->timeSinceCast = 0.0;
		}
	}
}
