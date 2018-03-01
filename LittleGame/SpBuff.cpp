
#include "SpBuff.h"

SpBuff::SpBuff(ActorObject* player) : Spell(player, NAME::BUFF)
{
	this->strength = 2.0f;
	this->setType(SPELLTYPE::DAMAGE);
	this->setState(SPELLSTATE::READY);

	this->setCost(15.0f);
	this->setCoolDown(10.0f);
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
		if (this->getPlayer()->useEnergy(this->getCost()))
		{
			this->active = true;
			this->setState(SPELLSTATE::ACTIVE);

			this->getPlayer()->setSpeed(this->strength);
			this->getPlayer()->GETphysicsComponent()->updateBoundingArea(0.0f);

			Locator::getAudioManager()->play(SOUND::NAME::ABILITYSOUND_SPEEDBOOST);
		}
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
		float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());

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
			this->floatingValue += 5.0f * dt;
			float parameter = this->oriY + sin(this->floatingValue) * 7.0f;

			this->getPlayer()->setPositionY(parameter);
		}
	}
}

void SpBuff::collision(GameObject * target, Projectile* proj)
{
	
}


////////////////////////////////////////////
//// GLYPH 1 ////////////////////////////////////////////
////////////////////////////////////////////
SpBuffG1::SpBuffG1(ActorObject * player) : SpBuff(player)
{
	this->setCoolDown(0.1f);
}

SpBuffG1::~SpBuffG1()
{
}


////////////////////////////////////////////
//// GLYPH 2 ////////////////////////////////////////////
////////////////////////////////////////////
SpBuffG2::SpBuffG2(ActorObject * player) : SpBuff(player)
{
	this->setCost(this->getCost() * 0.6f);
}

SpBuffG2::~SpBuffG2()
{
}


////////////////////////////////////////////
//// GLYPH 3 ////////////////////////////////////////////
////////////////////////////////////////////
SpBuffG3::SpBuffG3(ActorObject * player) : SpBuff(player)
{
	this->setCoolDown(this->getCoolDown() * 1.5f);
	this->setCost(this->getCost() * 0.2f);
}

SpBuffG3::~SpBuffG3()
{
}
