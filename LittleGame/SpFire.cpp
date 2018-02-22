
#include "SpFire.h"

SpFire::SpFire(ActorObject* player) : Spell(player, NAME::FIRE)
{
	this->strength = 1;
	this->setType(SPELLTYPE::DAMAGE);
	this->setState(SPELLSTATE::READY);

	this->setCost(20);
	this->setCoolDown(1.3);
	this->damage = 100;
	this->range = 100;
}

SpFire::~SpFire()
{
}

bool SpFire::castSpell()
{
	bool returnValue = false;

	if (this->getState() != SPELLSTATE::COOLDOWN)
	{
		// For further info, if needed, see 'useEnergy()' description
		if (this->getPlayer()->useEnergy(this->getCost()))
		{
			returnValue = true;

			ProjProp props(15, XMFLOAT4(1.0f, 0.1f, 0.5f, 0.1f), 500, this->range, true);
			this->spawnProj(props);

			Locator::getAudioManager()->play(SOUND::NAME::BEEP4);

			this->setState(SPELLSTATE::COOLDOWN);

			this->hits = 6;
		}
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
	// IF target is an enemy AND target is NOT contained within the 'previouslyHit' list.
	if (target->getType() == OBJECTTYPE::ENEMY &&
		!(std::find(this->previouslyHit.begin(), this->previouslyHit.end(), target) != this->previouslyHit.end())) {
		
		static_cast<ActorObject*>(target)->dealDmg(this->damage);

		this->previouslyHit.push_back(target);

		this->hits--;
		if (this->hits == 0)
		{
			proj->setState(OBJECTSTATE::TYPE::DEAD);
			this->previouslyHit.clear();
		}
	}

	else if (target->getType() == OBJECTTYPE::INDESTRUCTIBLE) {
		proj->setState(OBJECTSTATE::TYPE::DEAD);
		this->previouslyHit.clear();
	}
}
