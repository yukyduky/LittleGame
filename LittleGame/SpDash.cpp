
#include "SpDash.h"

SpDash::SpDash(ActorObject* player) : Spell(player, NAME::DASH)
{
	this->setType(SPELLTYPE::DAMAGE);
	this->setState(SPELLSTATE::READY);

	this->setCoolDown(2.3);
	this->strength = this->getCoolDown();
	// Distance to jump
	this->range = 200;
	this->nrOfFlames = 6;
	this->damage = 2.0f;

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
		XMFLOAT3 distance = { this->getPlayer()->getDirection() * this->range};
		XMFLOAT3 newPos = { oldPos + distance };

		//XMFLOAT3 playerNewPos;

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
		static_cast<ActorObject*>(target)->dealDmg(this->damage);
}
