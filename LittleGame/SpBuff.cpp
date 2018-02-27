
#include "SpBuff.h"

SpBuff::SpBuff(ActorObject* player) : Spell(player, NAME::BUFF)
{
	this->strength = 2.0f;
	this->setType(SPELLTYPE::DAMAGE);
	this->setState(SPELLSTATE::READY);

	this->setCoolDown(5.3f);
	this->duration = 1.5f;

	this->range = 20.0f;
	this->oriRadius = this->getOwner()->GETphysicsComponent()->GETBoundingSphere().Radius;
	this->active = false;
	this->floatingValue = 0.0f;
	this->oriY = this->getOwner()->GETPosition().y + this->range;
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

		this->getOwner()->setSpeed(this->strength);
		this->getOwner()->GETphysicsComponent()->updateBoundingArea(0.0f);

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
	this->updateCD();

	if (this->active)
	{
		if (this->getTSC() > this->duration)
		{
			this->getOwner()->setSpeed(1.0f);
			this->active = false;
			this->setState(SPELLSTATE::COOLDOWN);

			this->getOwner()->setPositionY(this->oriY - this->range);
			this->getOwner()->GETphysicsComponent()->updateBoundingArea(this->oriRadius);
		}
		else
		{
			this->floatingValue += 5.0f * Locator::getGameTime()->getDeltaTime();
			float parameter = this->oriY + sin(this->floatingValue) * 7.0f;

			this->getOwner()->setPositionY(parameter);
		}
	}
}

void SpBuff::cleanUp()
{
}

void SpBuff::collision(GameObject * target, Projectile* proj)
{
	
}
