
#include "SpDash.h"

SpDash::SpDash(ActorObject* player) : Spell(player, NAME::DASH)
{
	this->setType(SPELLTYPE::DAMAGE);
	this->setState(SPELLSTATE::READY);

	this->setCost(0.0f);
	this->setCoolDown(0.1f);
	this->strength = this->getCoolDown();
	// Distance to jump
	this->range = 200;
	this->nrOfFlames = 6;
	this->damage = 40.0f;

	this->flameSize = this->range / static_cast<float>((this->nrOfFlames * 2));
	this->burning = false;
}

SpDash::~SpDash()
{
}

bool SpDash::castSpell()
{
	bool returnValue = false;
	//Temporary template for the light
	Light light;
	light.pos = this->getOwner()->GETPosition();
	light.diffuse = XMFLOAT3(0.0f, 0.0f, 0.0f);
	light.ambient = XMFLOAT3(0.0f, 0.0f, 0.0f);
	light.attenuation = XMFLOAT3(0.0f, 0.0f, 0.0f);
	light.specPower = 0.0f;

	if (!this->burning && this->getState() != SPELLSTATE::COOLDOWN)
	{
		// For further info, if needed, see 'useEnergy()' description
		if (this->getOwner()->useEnergy(this->getCost()))
		{
			returnValue = true;

			XMFLOAT3 oldPos = this->getOwner()->GETPosition();
			XMFLOAT3 distance = { this->getOwner()->getDirection() * this->range };
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

			for (int i = 0; i < this->nrOfFlames; i++)
			{
				ProjProp props(flameSize, XMFLOAT4(1.0f, 1.0f, 0.0f, 0.2f), 0, -1, false);
				flames.push_back(this->spawnProj(props, light));
				flames[i]->setPosition(oldPos + (this->getOwner()->getDirection(i * flameSize * 2)));
			}
			//ProjProp props(10.0f, XMFLOAT3(1.0f, 1.0f, 0.0f), 0, -1);
			//this->spawnProj(props)->SETscaleMatrix(XMMatrixScaling(this->range - 40.0f, props.size, props.size));

			this->getOwner()->setPosition(newPos);

			Locator::getAudioManager()->play(SOUND::NAME::ABILITYSOUND_TELEPORT);

			this->setState(SPELLSTATE::COOLDOWN);
			this->burning = true;
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

	if (this->getState() == SPELLSTATE::READY)
	{
		this->burning = false;
		for (auto &i : this->flames)
		{
			i->setState(OBJECTSTATE::TYPE::DEAD);
		}
		this->flames.clear();

		this->strength = this->getCoolDown();
	}
	else if (this->burning)
	{
		float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());
		this->strength -= dt;

		for (auto &i : this->flames)
		{
			i->SETscaleMatrix(XMMatrixScaling(this->flameSize, this->flameSize * this->strength, this->flameSize));
		}
	}
}

void SpDash::cleanUp()
{
}

void SpDash::collision(GameObject * target, Projectile* proj)
{
	if (target->getType() == OBJECTTYPE::ENEMY || target->getType() == OBJECTTYPE::TYPE::GENERATOR)
		static_cast<ActorObject*>(target)->dealDmg(this->damage);
}


////////////////////////////////////////////
//// GLYPH 1 ////////////////////////////////////////////
////////////////////////////////////////////
SpDashG1::SpDashG1(ActorObject * player) : SpDash(player)
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
	bool returnValue = false;

	if (!this->burning && this->getState() != SPELLSTATE::COOLDOWN)
	{
		// For further info, if needed, see 'useEnergy()' description
		if (this->getOwner()->useEnergy(this->getCost()))
		{
			returnValue = true;

			XMFLOAT3 oldPos = this->getOwner()->GETPosition();
			XMFLOAT3 distance = { this->getOwner()->getDirection() * this->range };
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
			
			this->getOwner()->dealDmg(-this->damage);

			Locator::getAudioManager()->play(SOUND::NAME::ABILITYSOUND_TELEPORT);

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
SpDashG2::SpDashG2(ActorObject * player) : SpDash(player)
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
	bool returnValue = false;

	if (!this->burning && this->getState() != SPELLSTATE::COOLDOWN)
	{
		// For further info, if needed, see 'useEnergy()' description
		if (this->getOwner()->useEnergy(this->getCost()))
		{
			returnValue = true;

			XMFLOAT3 oldPos = this->getOwner()->GETPosition();
			XMFLOAT3 distance = { this->getOwner()->getDirection() * this->range };
			XMFLOAT3 newPos = { oldPos + distance };

			//XMFLOAT3 playerNewPos;

			if (newPos.z > static_cast<float>(ARENADATA::GETarenaHeight() - ARENADATA::GETsquareSize()))
			{
				newPos.z = static_cast<float>(ARENADATA::GETarenaHeight() - ARENADATA::GETsquareSize());
				this->getOwner()->dealDmg(this->damageFromMiss);
			}
			else if (newPos.z < ARENADATA::GETsquareSize())
			{
				newPos.z = static_cast<float>(ARENADATA::GETsquareSize());
				this->getOwner()->dealDmg(this->damageFromMiss);
			}

			if (newPos.x > static_cast<float>(ARENADATA::GETarenaWidth() - ARENADATA::GETsquareSize()))
			{
				newPos.x = static_cast<float>(ARENADATA::GETarenaWidth() - ARENADATA::GETsquareSize());
				this->getOwner()->dealDmg(this->damageFromMiss);
			}
			else if (newPos.x < static_cast<float>(ARENADATA::GETsquareSize()))
			{
				newPos.x = static_cast<float>(ARENADATA::GETsquareSize());
				this->getOwner()->dealDmg(this->damageFromMiss);
			}

			for (int i = 0; i < this->nrOfFlames; i++)
			{
				ProjProp props(flameSize, XMFLOAT4(1.0f, 1.0f, 0.0f, 0.2f), 0, -1, false);
				flames.push_back(this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.5f, 0.5f, 0.0f), XMFLOAT3(0.0f, 0.0001f, 0.0001f), 50)));
				flames[i]->setPosition(oldPos + (this->getOwner()->getDirection(i * flameSize * 2)));
			}
			//ProjProp props(10.0f, XMFLOAT3(1.0f, 1.0f, 0.0f), 0, -1);
			//this->spawnProj(props)->SETscaleMatrix(XMMatrixScaling(this->range - 40.0f, props.size, props.size));

			this->getOwner()->setPosition(newPos);

			Locator::getAudioManager()->play(SOUND::NAME::ABILITYSOUND_TELEPORT);

			this->setState(SPELLSTATE::COOLDOWN);
			this->burning = true;
		}
	}
	return returnValue;
}


////////////////////////////////////////////
//// GLYPH 3 ////////////////////////////////////////////
////////////////////////////////////////////
SpDashG3::SpDashG3(ActorObject * player) : SpDash(player)
{
	this->insertGlyph(GLYPHTYPE::GLYPH3);
	this->setCoolDown(this->getCoolDown() * 2.5f);
	this->setCost(this->getCost() * 0.2f);
}

SpDashG3::~SpDashG3()
{
}

bool SpDashG3::castSpell()
{
	bool returnValue = false;

	if (!this->burning && this->getState() != SPELLSTATE::COOLDOWN)
	{
		// For further info, if needed, see 'useEnergy()' description
		if (this->getOwner()->useEnergy(this->getCost()))
		{
			for (auto &i : this->flames)
			{
				i->setState(OBJECTSTATE::TYPE::DEAD);
			}
			this->flames.clear();

			returnValue = true;

			XMFLOAT3 oldPos = this->getOwner()->GETPosition();
			XMFLOAT3 distance = { this->getOwner()->getDirection() * this->range };
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
				flames.push_back(this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.5f, 0.5f, 0.0f), XMFLOAT3(0.0f, 0.0001f, 0.0001f), 50)));
				flames[i]->setPosition(oldPos + (this->getOwner()->getDirection(i * flameSize * 2)));
			}

			this->getOwner()->setPosition(newPos);

			Locator::getAudioManager()->play(SOUND::NAME::ABILITYSOUND_TELEPORT);

			this->setState(SPELLSTATE::COOLDOWN);
		}
	}
	return returnValue;;
}

// Empty because it dose not use the flames
void SpDashG3::update()
{
}
