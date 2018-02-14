
#include "SpAutoAttack.h"

SpAutoAttack::SpAutoAttack(ActorObject* player) : Spell(player, NAME::AUTOATTACK)
{
	this->strength = 1;
	this->setType(SPELLTYPE::DAMAGE);
	this->setState(SPELLSTATE::READY);
	
	this->setCoolDown(0.3);
	this->damage = 1;
	this->range = 50;
}

SpAutoAttack::~SpAutoAttack()
{
}

bool SpAutoAttack::castSpell()
{
	bool returnValue = true;
	if (this->getState() == SPELLSTATE::COOLDOWN)
	{
		returnValue = false;
	}
	else
	{
		ProjProp props(10, XMFLOAT4(200.5f, 200.5f, 0.5f, 0.2f), 1000, this->range, true);
		this->spawnProj(props);

		Locator::getAudioManager()->play(SOUND::NAME::BEEP1);

		this->setState(SPELLSTATE::COOLDOWN);
	}

	return returnValue;
}

void SpAutoAttack::upgrade(float modif)
{
	this->strength *= modif;
}


void SpAutoAttack::update()
{
	
}

void SpAutoAttack::collision(GameObject * target, Projectile* proj)
{
	if (target->getType() == OBJECTTYPE::ENEMY) {
		target->setState(OBJECTSTATE::TYPE::DEAD);
		Locator::getAudioManager()->play(SOUND::NAME::ENEMYDEATH_4);

		proj->setState(OBJECTSTATE::TYPE::DEAD);
	}

	else if (target->getType() == OBJECTTYPE::INDESTRUCTIBLE) {
		proj->setState(OBJECTSTATE::TYPE::DEAD);
	}
}
