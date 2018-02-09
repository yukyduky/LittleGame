
#include "SpBuff.h"

SpBuff::SpBuff(ActorObject* player, NAME name) : Spell(player, name)
{
	this->strength = 1;
	this->setType(SPELLTYPE::DAMAGE);
	this->setState(SPELLSTATE::READY);

	this->setCoolDown(3.3);
	// Speedmultiplier of the players movment
	this->range = 2;

}

SpBuff::~SpBuff()
{
}

bool SpBuff::castSpell()
{
	bool returnValue = true;
	if (this->getState() == SPELLSTATE::COOLDOWN)
	{
		returnValue = false;
	}
	else
	{
		this->getPlayer()->setSpeed(this->range * this->strength);

		this->setState(SPELLSTATE::COOLDOWN);


	}

	return returnValue;
}

void SpBuff::upgrade(float modif)
{
	this->strength *= modif;
}


void SpBuff::update()
{
	if (this->getTSC() > 1.5)
	{
		this->getPlayer()->setSpeed(1);
	}
}

void SpBuff::collision(GameObject * target, Projectile* proj)
{
	if (target->getType() == OBJECTTYPE::PLAYER)
	{
		//this->proj->setPosition(XMFLOAT3(200, 40, 200));
		proj->setState(OBJECTSTATE::TYPE::DEAD);
	}


}
