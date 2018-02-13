
#include "SpDash.h"

SpDash::SpDash(ActorObject* player) : Spell(player, NAME::DASH)
{
	this->strength = 1;
	this->setType(SPELLTYPE::DAMAGE);
	this->setState(SPELLSTATE::READY);

	this->setCoolDown(1.3);
	// Distance to jump
	this->range = 150;

}

SpDash::~SpDash()
{
}

bool SpDash::castSpell()
{
	bool returnValue = true;
	if (this->getState() == SPELLSTATE::COOLDOWN)
	{
		returnValue = false;
	}
	else
	{
		XMFLOAT3 distance = { this->getPlayer()->getDirection() * this->range * this->strength };
		XMFLOAT3 newPos = { this->getPlayer()->GETPosition() + distance };

		XMFLOAT3 playerNewPos;

		if (newPos.z > ARENAHEIGHT - ARENASQUARESIZE)
		{
			newPos.z = ARENAHEIGHT - ARENASQUARESIZE;
		}
		else if (newPos.z < ARENASQUARESIZE)
		{
			newPos.z = ARENASQUARESIZE;
		}

		if (newPos.x > ARENAWIDTH - ARENASQUARESIZE)
		{
			newPos.x = ARENAWIDTH - ARENASQUARESIZE;
		}
		else if (newPos.x < ARENASQUARESIZE)
		{
			newPos.x = ARENASQUARESIZE;
		}

		this->getPlayer()->setPosition(newPos);

		this->setState(SPELLSTATE::COOLDOWN);


	}

	return returnValue;
}

void SpDash::upgrade(float modif)
{
	this->strength *= modif;
}


void SpDash::update()
{

}

void SpDash::collision(GameObject * target, Projectile* proj)
{
	if (target->getType() == OBJECTTYPE::PLAYER)
	{
		//this->proj->setPosition(XMFLOAT3(200, 40, 200));
		proj->setState(OBJECTSTATE::TYPE::DEAD);
	}


}
