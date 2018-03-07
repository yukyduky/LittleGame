
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
	this->range = 300.0f;

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
			this->landed = false;
			this->yAcc = 6.0f;
			ProjProp props(30, XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f), 500.0f, this->range, false/*PROJBEHAVIOR::ENLARGE*/);
			this->theProj = this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.3f, 0.3f, 0.3f), XMFLOAT3(0.0f, 0.0001f, 0.0001f), 50));
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


		if (!this->landed)
		{
			XMFLOAT3 currPos = this->theProj->GETPosition();
			currPos.y += this->yAcc;
			this->yAcc += -15.0f * dt;
			this->theProj->setPosition(currPos);

			if (currPos.y <= 39.0f)
			{
				this->landed = true;
				this->damage = this->start;
				this->theProj->setSpeed(0.0f);
			}
		}
		else if (this->damage < this->end)
		{
			this->damage += 300.0f * dt;
			XMMATRIX scaleM = XMMatrixScaling(this->damage, this->damage, this->damage);
			this->theProj->GETphysicsComponent()->updateBoundingArea(this->damage * 1.5f);
			this->theProj->SETscaleMatrix(scaleM);
		}
		else if (this->collisionDuration < 0.2f) // Delay; bomb stops growing
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
	if (target->getType() == OBJECTTYPE::TYPE::ENEMY || target->getType() == OBJECTTYPE::TYPE::GENERATOR)
	{
		static_cast<ActorObject*>(target)->dealDmg(10000.0f);
	}
}


////////////////////////////////////////////
//// GLYPH 1 ////////////////////////////////////////////
////////////////////////////////////////////
SpBombG1::SpBombG1(ActorObject * player) : SpBomb(player)
{
	this->insertGlyph(GLYPHTYPE::GLYPH1);
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
	this->insertGlyph(GLYPHTYPE::GLYPH2);
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
	this->insertGlyph(GLYPHTYPE::GLYPH3);
	this->setCoolDown(this->getCoolDown() * 1.5f);
	this->damage *= 2.0f;
}

SpBombG3::~SpBombG3()
{
}

