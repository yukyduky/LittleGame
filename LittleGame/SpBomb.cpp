
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
			ProjProp props(30, XMFLOAT3(0.5f, 0.5f, 0.5f), 0, this->range);
			this->spawnProj(props);
		}

		//	if (this->flag0)
		//	{
		//		props = ProjProp(30, XMFLOAT3(0.5f, 0.5f, 0.5f), 0);
		//		this->spawnProj(props);
		//		this->flag0 = false;
		//	}

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

}

void SpBomb::collision(GameObject * target, Projectile* proj)
{
		if (this->damage < this->end)
		{
			this->damage += 20 * Locator::getGameTime()->getDeltaTime();
			XMMATRIX scaleM = XMMatrixScaling(this->damage, this->damage, this->damage);
			proj->GETphysicsComponent()->updateBoundingArea(this->damage);
			proj->SETscaleMatrix(scaleM);
			//proj->getPhyComp()->updateBounding(this->damage);
		}
		else
		{
			target->setPosition(XMFLOAT3(400, 40, 200));
			this->damage = this->start;
			proj->setState(OBJECTSTATE::TYPE::DEAD);
			this->active = false;
		}


}
