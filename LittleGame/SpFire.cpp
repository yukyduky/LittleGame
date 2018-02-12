
#include "SpFire.h"

SpFire::SpFire(ActorObject* player, NAME name) : Spell(player, name)
{
	this->strength = 1;
	this->setType(SPELLTYPE::DAMAGE);
	this->setState(SPELLSTATE::READY);

		this->setCoolDown(1.3);
		this->damage = 50;
		this->range = 230;

}

SpFire::~SpFire()
{
}

bool SpFire::castSpell()
{
	bool returnValue = true;
	if (this->getState() == SPELLSTATE::COOLDOWN)
	{
		returnValue = false;
	}
	else
	{
		ProjProp props(15, XMFLOAT3(200.5f, 0.5f, 0.5f), 500, this->range);
			this->spawnProj(props);

		this->setState(SPELLSTATE::COOLDOWN);


	}

	return returnValue;
}

void SpFire::upgrade(float modif)
{
	this->strength *= modif;
}


void SpFire::update()
{

}

void SpFire::collision(GameObject * target, Projectile* proj)
{
	if (target->getType() == OBJECTTYPE::PLAYER)
	{
		//this->proj->setPosition(XMFLOAT3(200, 40, 200));
		proj->setState(OBJECTSTATE::TYPE::DEAD);
	}


}
