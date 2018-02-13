
#include "SpDash.h"

SpDash::SpDash(ActorObject* player) : Spell(player, NAME::DASH)
{
	this->setType(SPELLTYPE::DAMAGE);
	this->setState(SPELLSTATE::READY);

	this->setCoolDown(2.3);
	this->strength = this->getCoolDown();
	// Distance to jump
	this->range = 150;
	this->nrOfFlames = 6;

	this->flameSize = this->range / (this->nrOfFlames * 2);
	this->burning = false;
}

SpDash::~SpDash()
{
}

bool SpDash::castSpell()
{
	bool returnValue = true;
	if (this->getState() == SPELLSTATE::COOLDOWN)
	{
		returnValue = false;
	}
	else if (!this->burning)
	{
		XMFLOAT3 oldPos = this->getPlayer()->GETPosition();
		XMFLOAT3 distance = { this->getPlayer()->getDirection() * this->range * this->strength };
		XMFLOAT3 newPos = { oldPos + distance };

		XMFLOAT3 playerNewPos;

		if (newPos.z > ARENAHEIGHT - ARENASQUARESIZE)
		{
			newPos.z = ARENAHEIGHT - ARENASQUARESIZE;
		}
		else if (newPos.z < ARENASQUARESIZE)
		{
			newPos.z = ARENASQUARESIZE;
		}

		if (newPos.x > ARENAWIDTH - ARENASQUARESIZE)
		{
			newPos.x = ARENAWIDTH - ARENASQUARESIZE;
		}
		else if (newPos.x < ARENASQUARESIZE)
		{
			newPos.x = ARENASQUARESIZE;
		}

		for (int i = 0; i < this->nrOfFlames; i++)
		{
			ProjProp props(flameSize, XMFLOAT3(1.0f, 1.0f, 0.0f), 0, -1);
			flames.push_back(this->spawnProj(props));
			flames[i]->setPosition(oldPos + (flames[i]->getDirection() * i * flameSize * 2));
		}
		//ProjProp props(10.0f, XMFLOAT3(1.0f, 1.0f, 0.0f), 0, -1);
		//this->spawnProj(props)->SETscaleMatrix(XMMatrixScaling(this->range - 40.0f, props.size, props.size));

		this->getPlayer()->setPosition(newPos);

		this->setState(SPELLSTATE::COOLDOWN);
		this->burning = true;

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
		this->strength -= Locator::getGameTime()->getDeltaTime();

		for (auto &i : this->flames)
		{
			i->SETscaleMatrix(XMMatrixScaling(this->flameSize, this->flameSize * this->strength, this->flameSize));
		}
	}
}

void SpDash::collision(GameObject * target, Projectile* proj)
{
	if (target->getType() == OBJECTTYPE::ENEMY)
	{
		//this->proj->setPosition(XMFLOAT3(200, 40, 200));
		proj->setState(OBJECTSTATE::TYPE::DEAD);
		target->setState(OBJECTSTATE::TYPE::DEAD);

	}


}
