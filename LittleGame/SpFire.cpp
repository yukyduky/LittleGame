
#include "SpFire.h"

SpFire::SpFire(ActorObject* player) : Spell(player, NAME::FIRE)
{
	this->strength = 1;
	this->setType(SPELLTYPE::DAMAGE);
	this->setState(SPELLSTATE::READY);

		this->setCoolDown(1.3);
		this->damage = 10;
		this->range = 100;

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
	if (target->getType() == OBJECTTYPE::ENEMY) {
		target->setState(OBJECTSTATE::TYPE::DEAD);
	}

	else if (target->getType() == OBJECTTYPE::INDESTRUCTIBLE) {
		proj->setState(OBJECTSTATE::TYPE::DEAD);
	}
}
