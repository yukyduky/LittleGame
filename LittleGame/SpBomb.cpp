
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

	this->setCoolDown(0.5f);
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
			this->theProj->GETphysicsComponent()->updateBoundingArea(this->damage * 2);
			this->theProj->SETscaleMatrix(scaleM);
		}
		else if (this->damage < (this->end + 0.2f)) // delay so that the explosion can kill targets
		{
			this->damage += 20 * dt;
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
	if (target->getType() == OBJECTTYPE::ENEMY)
	{
		//ActorObject* actorTarget = static_cast<ActorObject*>(target);

		//actorTarget->dealDmg(this->damage);

		//vColor colorHolder = target->GETgraphicsComponent()->GETcolor();

		//target->GETgraphicsComponent()->updateColor(vColor(
		//	actorTarget->GEThp() / actorTarget->GEThpMAX(),
		//	0.0f,
		//	0.0f,
		//	colorHolder.a)
		//);
		static_cast<ActorObject*>(target)->dealDmg(10000.0f);
	}
}


////////////////////////////////////////////
//// GLYPH 1 ////////////////////////////////////////////
////////////////////////////////////////////
SpBombG1::SpBombG1(ActorObject * player) : SpBomb(player)
{
	this->setCoolDown(0.1f);
}

SpBombG1::~SpBombG1()
{
}


////////////////////////////////////////////
//// GLYPH 2 ////////////////////////////////////////////
////////////////////////////////////////////
SpBombG2::SpBombG2(ActorObject * player) : SpBomb(player)
{
	this->damage *= 1.2f;
}

SpBombG2::~SpBombG2()
{
}


////////////////////////////////////////////
//// GLYPH 3 ////////////////////////////////////////////
////////////////////////////////////////////
SpBombG3::SpBombG3(ActorObject * player) : SpBomb(player)
{
	this->setCoolDown(this->getCoolDown() * 1.5f);
	this->damage *= 2.0f;
}

SpBombG3::~SpBombG3()
{
}

