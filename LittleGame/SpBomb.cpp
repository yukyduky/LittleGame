
#include "SpBomb.h"

SpBomb::SpBomb(ActorObject* player) : Spell(player, NAME::BOMB)
{
	this->strength = 1;
	this->setType(SPELLTYPE::DAMAGE);
	this->setState(SPELLSTATE::READY);

	// start-size
	this->start = 30;
	// end-size
	this->end = 100;
	// only 1 bomb out
	this->active = false;

	this->setCoolDown(5.3);
	this->damage = this->start;
	this->range = -1;

}

SpBomb::~SpBomb()
{
}

bool SpBomb::castSpell()
{
	bool returnValue = true;
	if (this->getState() == SPELLSTATE::COOLDOWN)
	{
		returnValue = false;
	}
	else
	{
		if (!this->active)
		{
			this->active = true;
			ProjProp props(30, XMFLOAT4(0.9f, 0.4f, 0.0f, 0.2f), 0, this->range, false);
			this->theProj = this->spawnProj(props);
		}

		this->setState(SPELLSTATE::COOLDOWN);
	}

	return returnValue;
}

void SpBomb::upgrade(float modif)
{
	this->strength *= modif;
}


void SpBomb::update()
{
	this->updateCD();

	if (this->active)
	{
		if (this->damage < this->end)
		{
			this->damage += 40 * Locator::getGameTime()->getDeltaTime();
			XMMATRIX scaleM = XMMatrixScaling(this->damage, this->damage, this->damage);
			this->theProj->GETphysicsComponent()->updateBoundingArea(this->damage);
			this->theProj->SETscaleMatrix(scaleM);
		}
		else if (this->damage < this->end + 0.2) // delay so that the explosion can kill targets
		{
			this->damage += 20 * Locator::getGameTime()->getDeltaTime();
		}
		else
		{
			this->active = false;
			this->theProj->setState(OBJECTSTATE::TYPE::DEAD);
			this->damage = this->start;
		}
	}
}

void SpBomb::collision(GameObject * target, Projectile* proj)
{
	if (this->damage >= this->end && target->getType() == OBJECTTYPE::ENEMY)
	{
		target->setState(OBJECTSTATE::TYPE::DEAD);
	}
}
