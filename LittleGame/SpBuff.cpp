
#include "SpBuff.h"

SpBuff::SpBuff(GameObject* owner) :  Spell(owner, NAME::BUFF)
{
	this->strength = 2.0f;
	this->setType(SPELLTYPE::DAMAGE);
	this->setState(SPELLSTATE::READY);

	this->setCost(15.0f);
	this->setCoolDown(10.0f);
	this->duration = 3.5f;

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
	this->actOwner = static_cast<ActorObject*>(this->getOwner());
	bool returnValue = true;
	if (this->getState() == SPELLSTATE::COOLDOWN || this->getState() == SPELLSTATE::ACTIVE)
	{
		returnValue = false;
	}
	else
	{
		if (this->actOwner->useEnergy(this->getCost()))
		{
			this->active = true;
			this->setState(SPELLSTATE::ACTIVE);

			this->getOwner()->SETvelocityMagnitude(this->strength);
			this->getOwner()->GETphysicsComponent()->updateBoundingArea(0.0f);

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
	this->updateCD();

	if (this->active)
	{
		float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());

		if (this->getTSC() > this->duration)
		{
			Locator::getGameTime()->setMultiplier(1.0);
			this->getOwner()->SETvelocityMagnitude(1.0f);
			this->active = false;
			this->setState(SPELLSTATE::COOLDOWN);

			this->getOwner()->setPositionY(this->oriY - this->range);
			this->getOwner()->GETphysicsComponent()->updateBoundingArea(this->oriRadius);
		}
		else
		{
			Locator::getGameTime()->setMultiplier(0.3);
			this->floatingValue += 5.0f * dt;
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


////////////////////////////////////////////
//// GLYPH 1 ////////////////////////////////////////////
////////////////////////////////////////////
SpBuffG1::SpBuffG1(GameObject* owner) :  SpBuff(owner)
{
	this->insertGlyph(GLYPHTYPE::GLYPH1);
	//this->duration *= 3.0f;
}

SpBuffG1::~SpBuffG1()
{
}

bool SpBuffG1::castSpell()
{
	this->actOwner = static_cast<ActorObject*>(this->getOwner());
	bool returnValue = true;
	if (this->getState() == SPELLSTATE::COOLDOWN || this->getState() == SPELLSTATE::ACTIVE)
	{
		returnValue = false;
	}
	else
	{
		if (this->actOwner->useEnergy(this->getCost()))
		{
			this->active = true;
			this->setState(SPELLSTATE::ACTIVE);

			this->actOwner->getPGPS()->setBerserkerMode(true);

			Locator::getAudioManager()->play(SOUND::NAME::ABILITYSOUND_SPEEDBOOST);
		}
	}

	return returnValue;
}

void SpBuffG1::update()
{
	if (this->active)
	{
		float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());

		if (this->getTSC() > this->duration)
		{
			Locator::getGameTime()->setMultiplier(1.0);
			this->active = false;
			this->setState(SPELLSTATE::COOLDOWN);

			this->actOwner->getPGPS()->setBerserkerMode(false);

		}
	}
}


////////////////////////////////////////////
//// GLYPH 2 ////////////////////////////////////////////
////////////////////////////////////////////
SpBuffG2::SpBuffG2(GameObject* owner) :  SpBuff(owner)
{
	this->insertGlyph(GLYPHTYPE::GLYPH2);
	this->setCost(this->getCost() * 0.6f);
}

SpBuffG2::~SpBuffG2()
{
}


////////////////////////////////////////////
//// GLYPH 3 ////////////////////////////////////////////
////////////////////////////////////////////
SpBuffG3::SpBuffG3(GameObject* owner) :  SpBuff(owner)
{
	this->insertGlyph(GLYPHTYPE::GLYPH3);
	this->strength *= 2.0f;
}

SpBuffG3::~SpBuffG3()
{
}

bool SpBuffG3::castSpell()
{
	this->actOwner = static_cast<ActorObject*>(this->owner);
	bool returnValue = true;
	if (this->getState() == SPELLSTATE::COOLDOWN || this->getState() == SPELLSTATE::ACTIVE)
	{
		returnValue = false;
	}
	else
	{
		if (this->actOwner->useEnergy(this->getCost()))
		{
			this->active = true;
			this->setState(SPELLSTATE::ACTIVE);

			this->getOwner()->SETvelocityMagnitude(this->strength);
			this->getOwner()->GETphysicsComponent()->updateBoundingArea(0.0f);

			Locator::getAudioManager()->play(SOUND::NAME::ABILITYSOUND_SPEEDBOOST);
		}
	}

	return returnValue;
}

void SpBuffG3::update()
{
	if (this->active)
	{
		float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());

		if (this->getTSC() > this->duration)
		{
			Locator::getGameTime()->setMultiplier(1.0);
			this->getOwner()->SETvelocityMagnitude(1.0f);
			this->active = false;
			this->setState(SPELLSTATE::COOLDOWN);

			this->getOwner()->GETphysicsComponent()->updateBoundingArea(this->oriRadius);
		}
		else
		{
			Locator::getGameTime()->setMultiplier(0.3);
		}
	}
}
