
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

	if (!this->burning && this->getState() != SPELLSTATE::COOLDOWN)
	{
		// For further info, if needed, see 'useEnergy()' description
		if (this->getPlayer()->useEnergy(this->getCost()))
		{
			returnValue = true;

			XMFLOAT3 oldPos = this->getPlayer()->GETPosition();
			XMFLOAT3 distance = { this->getPlayer()->getDirection() * this->range };
			XMFLOAT3 newPos = { oldPos + distance };

			//XMFLOAT3 playerNewPos;

		if (newPos.z > ARENADATA::GETarenaHeight() - ARENADATA::GETsquareSize())
		{
			newPos.z = ARENADATA::GETarenaHeight() - ARENADATA::GETsquareSize();
		}
		else if (newPos.z < ARENADATA::GETsquareSize())
		{
			newPos.z = ARENADATA::GETsquareSize();
		}

		if (newPos.x > ARENADATA::GETarenaWidth() - ARENADATA::GETsquareSize())
		{
			newPos.x = ARENADATA::GETarenaWidth() - ARENADATA::GETsquareSize();
		}
		else if (newPos.x < ARENADATA::GETsquareSize())
		{
			newPos.x = ARENADATA::GETsquareSize();
		}

			for (int i = 0; i < this->nrOfFlames; i++)
			{
				ProjProp props(flameSize, XMFLOAT4(1.0f, 1.0f, 0.0f, 0.2f), 0, -1, false);
				flames.push_back(this->spawnProj(props));
				flames[i]->setPosition(oldPos + (this->getPlayer()->getDirection(i * flameSize * 2)));
			}
			//ProjProp props(10.0f, XMFLOAT3(1.0f, 1.0f, 0.0f), 0, -1);
			//this->spawnProj(props)->SETscaleMatrix(XMMatrixScaling(this->range - 40.0f, props.size, props.size));

			this->getPlayer()->setPosition(newPos);

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

void SpDash::collision(GameObject * target, Projectile* proj)
{
	if (target->getType() == OBJECTTYPE::ENEMY)
		static_cast<ActorObject*>(target)->dealDmg(this->damage);
}
