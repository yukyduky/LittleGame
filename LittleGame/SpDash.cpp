
#include "SpDash.h"

SpDash::SpDash(GameObject* owner) : Spell(owner, NAME::DASH)
{
	this->setType(SPELLTYPE::DAMAGE);
	this->setState(SPELLSTATE::READY);

	this->setCost(10.0f);
	this->setCoolDown(2.0f);
	this->strength = this->getCoolDown();
	// Distance to jump
	this->range = 200;
	this->nrOfFlames = 6;
	this->damage = 250.0f;

	this->flameSize = this->range / static_cast<float>((this->nrOfFlames * 2));
}

SpDash::~SpDash()
{
}

bool SpDash::castSpell()
{
	this->actOwner = static_cast<ActorObject*>(this->owner);
	bool returnValue = false;
	//Temporary template for the light
	Light light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.2f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0001f, 0.0001f), 50);

	if (this->getState() != SPELLSTATE::COOLDOWN)
	{
		// For further info, if needed, see 'useEnergy()' description
		if (this->actOwner->useEnergy(this->getCost()))
		{
			returnValue = true;

			XMFLOAT3 oldPos = this->getOwner()->GETPosition();
			XMFLOAT3 distance = { this->actOwner->getDirection() * this->range};
			XMFLOAT3 newPos = { oldPos + distance };

			//XMFLOAT3 playerNewPos;

			if (newPos.z > static_cast<float>(ARENADATA::GETarenaHeight() - ARENADATA::GETsquareSize()))
			{
				newPos.z = static_cast<float>(ARENADATA::GETarenaHeight() - ARENADATA::GETsquareSize());
			}
			else if (newPos.z < ARENADATA::GETsquareSize())
			{
				newPos.z = static_cast<float>(ARENADATA::GETsquareSize());
			}

			if (newPos.x > static_cast<float>(ARENADATA::GETarenaWidth() - ARENADATA::GETsquareSize()))
			{
				newPos.x = static_cast<float>(ARENADATA::GETarenaWidth() - ARENADATA::GETsquareSize());
			}
			else if (newPos.x < static_cast<float>(ARENADATA::GETsquareSize()))
			{
				newPos.x = static_cast<float>(ARENADATA::GETsquareSize());
			}

			this->getOwner()->setPosition(newPos);

			for (int i = 0; i < this->nrOfFlames; i++)
			{
				ProjProp props(flameSize, XMFLOAT4(1.0f, 1.0f, 0.0f, 0.2f), 0, -1, false);
				this->spawnProj(props, light)
					->setPosition(oldPos + (this->actOwner->getDirection(i * flameSize * 2)));
			}
			//ProjProp props(10.0f, XMFLOAT3(1.0f, 1.0f, 0.0f), 0, -1);
			//this->spawnProj(props)->SETscaleMatrix(XMMatrixScaling(this->range - 40.0f, props.size, props.size));


			Locator::getAudioManager()->play(SOUND::NAME::ABILITY3_GLYPH0);

			this->setState(SPELLSTATE::COOLDOWN);
		}
	}
	return returnValue;
}

void SpDash::upgrade(float modif)
{
	this->strength *= modif;
}


void SpDash::update()
{
	this->updateCD();

	/*if (this->getState() == SPELLSTATE::READY)
	{
		this->burning = false;
		for (auto &i : this->flames)
		{
			i->setState(OBJECTSTATE::TYPE::DEAD);
		}
		this->flames.clear();

		this->strength = this->getCoolDown();
	}
	else */
	float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());
	this->strength -= dt;
	if (this->strength > 0.0f)
	{
		this->owner->SETscaleMatrix(XMMatrixScaling(this->flameSize, this->flameSize * this->strength, this->flameSize));
	}
	else
	{
		this->owner->setState(OBJECTSTATE::TYPE::DEAD);
	}
}

void SpDash::cleanUp()
{
}

void SpDash::collision(GameObject * target, Projectile* proj)
{
	OBJECTTYPE::TYPE type = target->getType();
	if (type == OBJECTTYPE::ENEMY || type == OBJECTTYPE::TYPE::GENERATOR ||
		type == OBJECTTYPE::BOSS) static_cast<ActorObject*>(target)->dealDmg(this->damage);
}


////////////////////////////////////////////
//// GLYPH 1 ////////////////////////////////////////////
////////////////////////////////////////////
SpDashG1::SpDashG1(GameObject* owner) : SpDash(owner)
{
	this->insertGlyph(GLYPHTYPE::GLYPH1);
	this->setCoolDown(1.0f);
	// Damage will heal the player in this skill
	this->damage = 10.0f;
}

SpDashG1::~SpDashG1()
{
}

bool SpDashG1::castSpell()
{
	this->actOwner = static_cast<ActorObject*>(this->owner);
	bool returnValue = false;

	if (this->getState() != SPELLSTATE::COOLDOWN)
	{
		// For further info, if needed, see 'useEnergy()' description
		if (this->actOwner->useEnergy(this->getCost()))
		{
			returnValue = true;

			XMFLOAT3 oldPos = this->getOwner()->GETPosition();
			XMFLOAT3 distance = { this->actOwner->getDirection() * this->range };
			XMFLOAT3 newPos = { oldPos - distance };

			//XMFLOAT3 playerNewPos;

			if (newPos.z > static_cast<float>(ARENADATA::GETarenaHeight() - ARENADATA::GETsquareSize()))
			{
				newPos.z = static_cast<float>(ARENADATA::GETarenaHeight() - ARENADATA::GETsquareSize());
			}
			else if (newPos.z < ARENADATA::GETsquareSize())
			{
				newPos.z = static_cast<float>(ARENADATA::GETsquareSize());
			}

			if (newPos.x > static_cast<float>(ARENADATA::GETarenaWidth() - ARENADATA::GETsquareSize()))
			{
				newPos.x = static_cast<float>(ARENADATA::GETarenaWidth() - ARENADATA::GETsquareSize());
			}
			else if (newPos.x < static_cast<float>(ARENADATA::GETsquareSize()))
			{
				newPos.x = static_cast<float>(ARENADATA::GETsquareSize());
			}

			this->getOwner()->setPosition(newPos);
			
			
			this->actOwner->dealDmg(-this->damage);

			Locator::getAudioManager()->play(SOUND::NAME::ABILITY3_GLYPH1);

			this->setState(SPELLSTATE::COOLDOWN);
		}
	}
	return returnValue;
}

// Empty because it dose not use the flames
void SpDashG1::collision(GameObject * target, Projectile * proj)
{
}

// Empty because it dose not use the flames
void SpDashG1::update()
{
}


////////////////////////////////////////////
//// GLYPH 2 ////////////////////////////////////////////
////////////////////////////////////////////
SpDashG2::SpDashG2(GameObject* owner) : SpDash(owner)
{
	this->insertGlyph(GLYPHTYPE::GLYPH2);
	this->setCost(this->getCost() * 0.6f);
	this->setCoolDown(this->getCoolDown() * 3.0f);
	float multiplier = 3.0f;
	this->range *= multiplier;
	this->nrOfFlames *= multiplier;
	this->damageFromMiss = 40.0f;
}

SpDashG2::~SpDashG2()
{
}

bool SpDashG2::castSpell()
{
	this->actOwner = static_cast<ActorObject*>(this->owner);
	bool returnValue = false;

	if (this->getState() != SPELLSTATE::COOLDOWN)
	{
		// For further info, if needed, see 'useEnergy()' description
		if (this->actOwner->useEnergy(this->getCost()))
		{
			returnValue = true;

			XMFLOAT3 oldPos = this->getOwner()->GETPosition();
			XMFLOAT3 distance = { this->actOwner->getDirection() * this->range };
			XMFLOAT3 newPos = { oldPos + distance };

			//XMFLOAT3 playerNewPos;

			if (newPos.z > static_cast<float>(ARENADATA::GETarenaHeight() - ARENADATA::GETsquareSize()))
			{
				newPos.z = static_cast<float>(ARENADATA::GETarenaHeight() - ARENADATA::GETsquareSize());
				this->actOwner->dealDmg(this->damageFromMiss);
			}
			else if (newPos.z < ARENADATA::GETsquareSize())
			{
				newPos.z = static_cast<float>(ARENADATA::GETsquareSize());
				this->actOwner->dealDmg(this->damageFromMiss);
			}

			if (newPos.x > static_cast<float>(ARENADATA::GETarenaWidth() - ARENADATA::GETsquareSize()))
			{
				newPos.x = static_cast<float>(ARENADATA::GETarenaWidth() - ARENADATA::GETsquareSize());
				this->actOwner->dealDmg(this->damageFromMiss);
			}
			else if (newPos.x < static_cast<float>(ARENADATA::GETsquareSize()))
			{
				newPos.x = static_cast<float>(ARENADATA::GETsquareSize());
				this->actOwner->dealDmg(this->damageFromMiss);
			}

			for (int i = 0; i < this->nrOfFlames; i++)
			{
				ProjProp props(flameSize, XMFLOAT4(1.0f, 1.0f, 0.0f, 0.2f), 0, -1, false);
				this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.5f, 0.5f, 0.0f), XMFLOAT3(0.0f, 0.0001f, 0.0001f), 50))
					->setPosition(oldPos + (this->actOwner->getDirection(i * flameSize * 2)));
			}
			//ProjProp props(10.0f, XMFLOAT3(1.0f, 1.0f, 0.0f), 0, -1);
			//this->spawnProj(props)->SETscaleMatrix(XMMatrixScaling(this->range - 40.0f, props.size, props.size));

			this->getOwner()->setPosition(newPos);

			Locator::getAudioManager()->play(SOUND::NAME::ABILITY3_GLYPH0);

			this->setState(SPELLSTATE::COOLDOWN);
		}
	}
	return returnValue;
}


////////////////////////////////////////////
//// GLYPH 3 ////////////////////////////////////////////
////////////////////////////////////////////
SpDashG3::SpDashG3(GameObject* owner) : SpDash(owner)
{
	this->insertGlyph(GLYPHTYPE::GLYPH3);
	this->setCoolDown(this->getCoolDown() * 2.5f);
	this->setCost(this->getCost() * 0.2f);
	this->damage = 5.0f;
}

SpDashG3::~SpDashG3()
{
}

bool SpDashG3::castSpell()
{
	this->actOwner = static_cast<ActorObject*>(this->owner);
	bool returnValue = false;

	if (this->getState() != SPELLSTATE::COOLDOWN)
	{
		// For further info, if needed, see 'useEnergy()' description
		if (this->actOwner->useEnergy(this->getCost()))
		{
			for (auto &i : this->flames)
			{
				i->setState(OBJECTSTATE::TYPE::DEAD);
				//i->cleanUp();
			}
			this->flames.clear();

			returnValue = true;

			XMFLOAT3 oldPos = this->getOwner()->GETPosition();
			XMFLOAT3 distance = { this->actOwner->getDirection() * this->range };
			XMFLOAT3 newPos = { oldPos + distance };


			if (newPos.z > static_cast<float>(ARENADATA::GETarenaHeight() - ARENADATA::GETsquareSize()))
			{
				newPos.z = static_cast<float>(ARENADATA::GETarenaHeight() - ARENADATA::GETsquareSize());
			}
			else if (newPos.z < ARENADATA::GETsquareSize())
			{
				newPos.z = static_cast<float>(ARENADATA::GETsquareSize());
			}

			if (newPos.x > static_cast<float>(ARENADATA::GETarenaWidth() - ARENADATA::GETsquareSize()))
			{
				newPos.x = static_cast<float>(ARENADATA::GETarenaWidth() - ARENADATA::GETsquareSize());
			}
			else if (newPos.x < static_cast<float>(ARENADATA::GETsquareSize()))
			{
				newPos.x = static_cast<float>(ARENADATA::GETsquareSize());
			}

			for (int i = 0; i < this->nrOfFlames; i++)
			{
				ProjProp props(flameSize, XMFLOAT4(1.0f, 1.0f, 0.0f, 0.2f), 0, -1, false);
				this->flames.push_back(this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.5f, 0.5f, 0.0f), XMFLOAT3(0.0f, 0.0001f, 0.0001f), 50)));
				this->flames.back()->setPosition(oldPos + (this->actOwner->getDirection(i * flameSize * 2)));
			}

			this->getOwner()->setPosition(newPos);

			Locator::getAudioManager()->play(SOUND::NAME::ABILITY3_GLYPH0);

			this->setState(SPELLSTATE::COOLDOWN);
		}
	}
	return returnValue;;
}

// Empty because it dose not use the flames
void SpDashG3::update()
{
}
