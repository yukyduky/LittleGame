
#include "SpBomb.h"

SpBomb::SpBomb(ActorObject* player) : Spell(player, NAME::BOMB)
{
	this->strength = 1;
	this->setType(SPELLTYPE::DAMAGE);
	this->setState(SPELLSTATE::READY);

	// start-size
	this->start = 0.0f;
	// end-size
	this->end = 100;
	// Time bomb has to kill enemies
	this->collisionDuration = 0.0f;
	// only 1 bomb out
	this->active = false;

	this->setCoolDown(1.5f);
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
			ProjProp props(30, XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f), 0.0f, this->range, false);
			this->theProj = this->spawnProj(props);
			this->damage = this->start;
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
	if (this->active)
	{
		float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());

		if (this->damage < this->end)
		{
			this->damage += 300 * dt;
			XMMATRIX scaleM = XMMatrixScaling(this->damage, this->damage, this->damage);
			this->theProj->GETphysicsComponent()->updateBoundingArea(this->damage * 1.5f);
			this->theProj->SETscaleMatrix(scaleM);
		}
		else if (this->collisionDuration < 0.2f) // delay so that the explosion can kill targets
		{
			this->collisionDuration += dt;
		}
		else
		{
			this->active = false;
			this->theProj->setState(OBJECTSTATE::TYPE::DEAD);
			this->damage = this->start;
			this->collisionDuration = 0.0f;
		}
	}
}

void SpBomb::collision(GameObject * target, Projectile* proj)
{
	if (target->getType() == OBJECTTYPE::TYPE::ENEMY)
	{
		static_cast<ActorObject*>(target)->dealDmg(10000.0f);
	}
}
