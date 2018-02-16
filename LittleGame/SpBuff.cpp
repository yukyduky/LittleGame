
#include "SpBuff.h"

SpBuff::SpBuff(ActorObject* player) : Spell(player, NAME::BUFF)
{
	this->strength = 2.0f;
	this->setType(SPELLTYPE::DAMAGE);
	this->setState(SPELLSTATE::READY);

	this->setCoolDown(5.3f);
	this->duration = 1.5f;

	this->range = 20.0f;
	this->oriRadius = this->getPlayer()->GETphysicsComponent()->GETBoundingSphere().Radius;
	this->active = false;
	this->floatingValue = 0.0f;
	this->oriY = this->getPlayer()->GETPosition().y + this->range;
}

SpBuff::~SpBuff()
{
}

bool SpBuff::castSpell()
{
	bool returnValue = true;
	if (this->getState() == SPELLSTATE::COOLDOWN || this->getState() == SPELLSTATE::ACTIVE)
	{
		returnValue = false;
	}
	else
	{
		this->active = true;
		this->setState(SPELLSTATE::ACTIVE);

		this->getPlayer()->setSpeed(this->strength);
		this->getPlayer()->GETphysicsComponent()->updateBoundingArea(0.0f);

		Locator::getAudioManager()->play(SOUND::NAME::ABILITYSOUND_SPEEDBOOST);
	}

	return returnValue;
}

void SpBuff::upgrade(float modif)
{
	this->strength *= modif;
}


void SpBuff::update()
{
	if (this->active)
	{
		if (this->getTSC() > this->duration)
		{
			this->getPlayer()->setSpeed(1.0f);
			this->active = false;
			this->setState(SPELLSTATE::COOLDOWN);

			this->getPlayer()->setPositionY(this->oriY - this->range);
			this->getPlayer()->GETphysicsComponent()->updateBoundingArea(this->oriRadius);
		}
		else
		{
			this->floatingValue += 5.0f * Locator::getGameTime()->getDeltaTime();
			float parameter = this->oriY + sin(this->floatingValue) * 7.0f;

			this->getPlayer()->setPositionY(parameter);
		}
	}
}

void SpBuff::collision(GameObject * target, Projectile* proj)
{
	
}
