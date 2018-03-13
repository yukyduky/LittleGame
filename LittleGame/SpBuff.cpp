
#include "SpBuff.h"

SpBuff::SpBuff(GameObject* owner) :  Spell(owner, NAME::BUFF)
{
	this->strength = 100.0f;
	this->setType(SPELLTYPE::DAMAGE);
	this->setState(SPELLSTATE::READY);

	this->setCost(15.0f);
	this->setCoolDown(5.0f);
	this->duration = 1.5f;
	this->setCoolDown(8.0f);

	this->range = 20.0f;
	this->oriRadius = this->getOwner()->GETphysicsComponent()->GETBoundingSphere().Radius;
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
			ProjProp props(0, XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f), 0.0f, -1, false/*PROJBEHAVIOR::ENLARGE*/);
			this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.3f, 0.3f, 0.3f), XMFLOAT3(0.0f, 0.0001f, 0.0001f), 50))
				;

			this->setState(SPELLSTATE::COOLDOWN);
			Locator::getGameTime()->setMultiplier(0.3);
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
	float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());
	this->timeSC += dt;
	if (this->timeSC >= this->duration)
	{
		Locator::getGameTime()->setMultiplier(1.0);
		this->owner->setState(OBJECTSTATE::TYPE::DEAD);
	}
	else
	{
		XMFLOAT3 actPos = this->actOwner->GETPosition();
		actPos.z += 1.0f;
		this->owner->setPosition(actPos);
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
	this->duration = 1.5f;
	this->setCoolDown(8.0f);
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
			ProjProp props(0, XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f), 0.0f, -1, false/*PROJBEHAVIOR::ENLARGE*/);
			this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.3f, 0.3f, 0.3f), XMFLOAT3(0.0f, 0.0001f, 0.0001f), 50))
				;

			this->setState(SPELLSTATE::COOLDOWN);
			GamePlayState::getInstance()->setBerserkerMode(true);
			Locator::getAudioManager()->play(SOUND::NAME::ABILITYSOUND_SPEEDBOOST);
		}
	}

	return returnValue;
}

void SpBuffG1::update()
{
	float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());
	this->timeSC += dt;
	if (this->timeSC >= this->duration)
	{
		GamePlayState::getInstance()->setBerserkerMode(false);
		this->owner->setState(OBJECTSTATE::TYPE::DEAD);
	}
	else
	{
		XMFLOAT3 actPos = this->actOwner->GETPosition();
		actPos.z += 1.0f;
		this->owner->setPosition(actPos);
	}
	
}


////////////////////////////////////////////
//// GLYPH 2 ////////////////////////////////////////////
////////////////////////////////////////////
SpBuffG2::SpBuffG2(GameObject* owner) :  SpBuff(owner)
{
	this->insertGlyph(GLYPHTYPE::GLYPH2);
	this->setCost(this->getCost() * 1.0f);
	this->range = 300.0f;

	this->duration = 1.5f;
	this->setCoolDown(8.0f);
	this->timeSC = 0.0f;
}

SpBuffG2::~SpBuffG2()
{
}

bool SpBuffG2::castSpell()
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
			ProjProp props(0, XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f), 0.0f, -1, false/*PROJBEHAVIOR::ENLARGE*/);
			this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.3f, 0.3f, 0.3f), XMFLOAT3(0.0f, 0.0001f, 0.0001f), 50))
				->GETphysicsComponent()->updateBoundingArea(this->range);

			Locator::getAudioManager()->play(SOUND::NAME::ABILITYSOUND_SPEEDBOOST);
			this->setState(SPELLSTATE::COOLDOWN);
		}
	}

	return returnValue;
}

void SpBuffG2::update()
{
	float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());
	this->timeSC += dt;
	if (this->timeSC >= this->duration)
	{
		this->owner->setState(OBJECTSTATE::TYPE::DEAD);
	}
	else
	{
		XMFLOAT3 actPos = this->actOwner->GETPosition();
		actPos.z += 1.0f;
		this->owner->setPosition(actPos);
	}
}

void SpBuffG2::collision(GameObject * target, Projectile * proj)
{
	if (target->getType() == OBJECTTYPE::TYPE::ENEMY)
	{
		XMVECTOR pushDir = XMVectorSubtract(XMLoadFloat3(&target->GETPosition()), XMLoadFloat3(&proj->GETPosition()));

		pushDir = XMVector3Normalize(pushDir);

		XMFLOAT3 kinvectorFloat3;
		XMStoreFloat3(&kinvectorFloat3, pushDir);
		static_cast<ActorObject*>(target)->setkineticVector(kinvectorFloat3 * 300.0f);
	}
}


////////////////////////////////////////////
//// GLYPH 3 ////////////////////////////////////////////
////////////////////////////////////////////
SpBuffG3::SpBuffG3(GameObject* owner) :  SpBuff(owner)
{
	this->insertGlyph(GLYPHTYPE::GLYPH3);
	this->strength = 10.0f;

	this->timeSC = 0.0f;
}

SpBuffG3::~SpBuffG3()
{
}

bool SpBuffG3::castSpell()
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
			ProjProp props(0, XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f), 0.0f, -1, false/*PROJBEHAVIOR::ENLARGE*/);
			this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.3f, 0.3f, 0.3f), XMFLOAT3(0.0f, 0.0001f, 0.0001f), 50))
				;

			this->setState(SPELLSTATE::COOLDOWN);
			this->actOwner->SETvelocityMagnitude(300.0f);
			this->actOwner->SETtopSpeedMagnitude(3.0f);
			Locator::getGameTime()->setMultiplier(0.3);
			Locator::getAudioManager()->play(SOUND::NAME::ABILITYSOUND_SPEEDBOOST);
		}
	}

	return returnValue;
}

void SpBuffG3::update()
{
	float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());
	this->timeSC += dt;
	if (this->timeSC >= this->duration)
	{
		this->owner->setState(OBJECTSTATE::TYPE::DEAD);
		this->actOwner->SETvelocityMagnitude(100.0f);
		this->actOwner->SETtopSpeedMagnitude(1.0f);
		Locator::getGameTime()->setMultiplier(1.0);
	}
	else
	{
		XMFLOAT3 actPos = this->actOwner->GETPosition();
		actPos.z += 1.0f;
		this->owner->setPosition(actPos);
	}
}

void SpBuffG3::collision(GameObject * target, Projectile * proj)
{
}
