
#include "Spell.h"

Spell::Spell(ActorObject* player)
{
	this->player = player;
}

Spell::~Spell()
{
}

void Spell::updateCD()
{
	if (this->state == SPELLSTATE::COOLDOWN)
	{
		this->timeSinceCast += Locator::getGameTime()->getDeltaTime();
		if (this->timeSinceCast > this->coolDown)
		{
			this->state = SPELLSTATE::READY;
			this->timeSinceCast = 0;
		}
	}
}
