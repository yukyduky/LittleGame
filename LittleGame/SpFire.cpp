
#include "SpFire.h"

SpFire::SpFire(ActorObject* player) : Spell(player, NAME::FIRE)
{
	this->strength = 1;
	this->setType(SPELLTYPE::DAMAGE);
	this->setState(SPELLSTATE::READY);

	this->setCoolDown(1.3f);
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
		ProjProp props(15, XMFLOAT4(1.0f, 0.1f, 0.5f, 0.1f), 500.0f, this->range, true);
		this->spawnProj(props);

		Locator::getAudioManager()->play(SOUND::NAME::BEEP4);

		this->setState(SPELLSTATE::COOLDOWN);

		this->hits = 3;

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
		Locator::getAudioManager()->play(SOUND::NAME::ENEMYDEATH_3);

		this->hits--;
		if (this->hits == 0)
		{
			proj->setState(OBJECTSTATE::TYPE::DEAD);
		}
	}

	else if (target->getType() == OBJECTTYPE::INDESTRUCTIBLE) {
		proj->setState(OBJECTSTATE::TYPE::DEAD);
	}
}
