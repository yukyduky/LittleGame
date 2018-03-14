
#include "SpBomb.h"

SpBomb::SpBomb(GameObject* owner) : Spell(owner, NAME::BOMB)
{
	this->strength = 1;
	this->setType(SPELLTYPE::DAMAGE);
	this->setState(SPELLSTATE::READY);

	//this->theProj = nullptr;

	// start-size
	this->start = 0.0f;
	// end-size
	this->end = 100;
	// Time bomb has to kill enemies
	this->collisionDuration = 0.0f;
	// only 1 bomb out
	this->active = true;
	this->setCoolDown(1.5f);
	this->damage = this->start;
	this->range = 300.0f;
	this->cost = 20.0f;

	this->active = true;
	this->landed = false;
	this->yAcc = 6.0f;
}

SpBomb::~SpBomb()
{
}

bool SpBomb::castSpell()
{
	this->actOwner = static_cast<ActorObject*>(this->owner);
	bool returnValue = true;
	if (this->getState() == SPELLSTATE::COOLDOWN)
	{
		returnValue = false;
	}
	else
	{
		//if (this->owner != nullptr)
		//{
		//	this->projOwner->setState(OBJECTSTATE::TYPE::DEAD);
		//}

		ProjProp props(15, XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f), 500.0f, -1, false/*PROJBEHAVIOR::ENLARGE*/);
		this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.3f, 0.3f, 0.3f), XMFLOAT3(0.0f, 0.0001f, 0.0001f), 50));

		this->setState(SPELLSTATE::COOLDOWN);

		Locator::getAudioManager()->play(SOUND::NAME::ABILITY2_GLYPH0_THROW);

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
		float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());

		if (!this->landed)
		{
			XMFLOAT3 currPos = this->owner->GETPosition();
			currPos.y += this->yAcc;
			this->yAcc += -15.0f * dt;
			this->owner->setPosition(currPos);

			if (currPos.y <= 39.0f)
			{
				this->landed = true;
				this->damage = this->start;
				this->collisionDuration = 0.0f;
				static_cast<Projectile*>(this->owner)->SETvelocityMagnitude(0.0f);

				Locator::getAudioManager()->play(SOUND::NAME::ABILITY2_GLYPH0_EXPLOSION);
			}
		}
		else if (this->damage < this->end)
		{
			this->damage += 300.0f * dt;
			XMMATRIX scaleM = XMMatrixScaling(this->damage, this->damage, this->damage);
			this->owner->GETphysicsComponent()->updateBoundingArea(this->damage);
			this->owner->SETscaleMatrix(scaleM);
		}
		else if (this->collisionDuration < 0.2f) // Delay; bomb stops growing
		{
			this->collisionDuration += dt;
		}
		else
		{
			this->active = false;
			this->owner->setState(OBJECTSTATE::TYPE::DEAD);
		}
	}
}

void SpBomb::cleanUp()
{
}

void SpBomb::collision(GameObject * target, Projectile* proj)
{
	OBJECTTYPE::TYPE type = target->getType();
	if ((type == OBJECTTYPE::TYPE::ENEMY || type == OBJECTTYPE::TYPE::GENERATOR || 
		type == OBJECTTYPE::BOSS) && this->landed)
	{
		float dt = Locator::getGameTime()->getDeltaTime();
		static_cast<ActorObject*>(target)->dealDmg(150.0f * dt);
	}
}


////////////////////////////////////////////
//// GLYPH 1 ////////////////////////////////////////////
////////////////////////////////////////////
SpBombG1::SpBombG1(GameObject* owner) : SpBomb(owner)
{
	this->insertGlyph(GLYPHTYPE::GLYPH1);
	this->setCoolDown(this->getCoolDown() * 1.5f);
	this->damage = 70.0f;
	this->nrOfSplinters = 8;
}

SpBombG1::~SpBombG1()
{
}

void SpBombG1::update()
{
	if (this->active)
	{
		float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());

		if (!this->landed)
		{
			this->currPos = this->owner->GETPosition();
			this->currPos.y += this->yAcc;
			this->yAcc += -15.0f * dt;
			this->owner->setPosition(this->currPos);

			if (this->currPos.y <= 39.0f)
			{
				this->landed = true;
				static_cast<Projectile*>(this->owner)->SETvelocityMagnitude(0.0f);
				Locator::getAudioManager()->play(SOUND::NAME::ABILITY2_GLYPH1_EXPLOSION);
			}
		}
		else
		{
			// Set the projectiles to be the same as AutoAttack base
			this->setName(NAME::AUTOATTACK);
			this->insertGlyph(GLYPHTYPE::NONE);
			ProjProp props(10, XMFLOAT4(0.3f, 0.1f, 0.3f, 0.1f), 500, 300, true);

			XMVECTOR direction = XMLoadFloat3(&static_cast<Projectile*>(this->getOwner())->getDirection());
			XMVECTOR axis = { 0.0f, 1.0f, 0.0f };

			float angle = 6.24 /*=2PI*/ / this->nrOfSplinters;
			for (int i = 0; i < this->nrOfSplinters; i++)
			{
				direction = XMVector3Rotate(direction, XMQuaternionRotationAxis(axis, angle));

				this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.2f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0001f, 0.0001f), 50))
					->setDirection(direction);
			}

			this->active = false;
			this->owner->setState(OBJECTSTATE::TYPE::DEAD);
		}
	}
}


////////////////////////////////////////////
//// GLYPH 2 ////////////////////////////////////////////
////////////////////////////////////////////
SpBombG2::SpBombG2(GameObject* owner) : SpBomb(owner)
{
	this->insertGlyph(GLYPHTYPE::GLYPH2);
	this->setCoolDown(this->getCoolDown() * 1.5f);
}

SpBombG2::~SpBombG2()
{
}

void SpBombG2::collision(GameObject * target, Projectile * proj)
{
	OBJECTTYPE::TYPE type = target->getType();
	if ((type == OBJECTTYPE::TYPE::ENEMY || type == OBJECTTYPE::TYPE::GENERATOR ||
		type == OBJECTTYPE::BOSS) && this->landed)
	{
		float dt = Locator::getGameTime()->getDeltaTime();
		static_cast<ActorObject*>(target)->dealDmg(150.0f * dt);
		this->trip = true;
	}

}

void SpBombG2::update()
{
	if (this->active)
	{

		if (!this->landed)
		{
			float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());

			this->currPos = this->owner->GETPosition();
			this->currPos.y += this->yAcc;
			this->yAcc += -25.0f * dt;
			this->owner->setPosition(this->currPos);

			if (this->currPos.y <= 0.0f)
			{
				this->landed = true;
				static_cast<Projectile*>(this->owner)->SETvelocityMagnitude(0.0f);
				this->trip = false;
				this->damage = this->start;
				Locator::getAudioManager()->play(SOUND::NAME::ABILITY2_GLYPH2_ARMED);
			}
		}
		else if (this->trip)
		{
			float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());

			if (this->damage < this->end)
			{
				if (!this->detonationStart)
				{
					Locator::getAudioManager()->play(SOUND::NAME::ABILITY2_GLYPH2_EXPLOSION);
					this->detonationStart = true;
				}

				this->damage += 300.0f * dt;
				XMMATRIX scaleM = XMMatrixScaling(this->damage, this->damage, this->damage);
				this->owner->GETphysicsComponent()->updateBoundingArea(this->damage * 1.5f);
				this->owner->SETscaleMatrix(scaleM);
			}
			else if (this->collisionDuration < 0.2f) // Delay; bomb stops growing
			{
				this->collisionDuration += dt;
			}
			else
			{
				this->detonationStart = false;
				this->active = false;
				this->trip = false;
				this->owner->setState(OBJECTSTATE::TYPE::DEAD);
			}
		}
		
	}
}


////////////////////////////////////////////
//// GLYPH 3 ////////////////////////////////////////////
////////////////////////////////////////////
SpBombG3::SpBombG3(GameObject* owner) : SpBomb(owner)
{
	this->insertGlyph(GLYPHTYPE::GLYPH3);
	this->setCoolDown(this->getCoolDown() * 4.5f);
	this->cost = 50.0f;
}

SpBombG3::~SpBombG3()
{
}

void SpBombG3::update()
{
	if (this->active)
	{
		float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());

		if (!this->landed)
		{
			XMFLOAT3 currPos = this->owner->GETPosition();
			currPos.y += this->yAcc;
			this->yAcc += -15.0f * dt;
			this->owner->setPosition(currPos);

			if (currPos.y <= 39.0f)
			{
				this->landed = true;
				this->damage = this->start;
				this->collisionDuration = 0.0f;
				static_cast<Projectile*>(this->owner)->SETvelocityMagnitude(0.0f);
				Locator::getAudioManager()->play(SOUND::NAME::ABILITY2_GLYPH3_EXPLOSION);
			}
		}
		else if (this->damage < this->end)
		{
			this->damage += 30.0f * dt;
			XMMATRIX scaleM = XMMatrixScaling(this->damage, this->damage, this->damage);
			this->owner->GETphysicsComponent()->updateBoundingArea(this->damage * 10.5f);
			this->owner->SETscaleMatrix(scaleM);
		}
		else if (this->collisionDuration < 0.2f) // Delay; bomb stops growing
		{
			this->collisionDuration += dt;
		}
		else
		{
			this->active = false;
			this->owner->setState(OBJECTSTATE::TYPE::DEAD);
		}
	}
}

void SpBombG3::collision(GameObject * target, Projectile * proj)
{
	OBJECTTYPE::TYPE type = target->getType();
	if ((type == OBJECTTYPE::TYPE::ENEMY || type == OBJECTTYPE::TYPE::GENERATOR ||
		type == OBJECTTYPE::BOSS) && this->landed)
	{
		float dt = Locator::getGameTime()->getDeltaTime();

		ActorObject* actorTarget = static_cast<ActorObject*>(target);

		XMVECTOR pullDir = XMVectorSubtract(XMLoadFloat3(&proj->GETPosition()), XMLoadFloat3(&target->GETPosition()));
		XMVECTOR pullLenghtVector = XMVector3Length(pullDir);
		float pullLenght;
		XMStoreFloat(&pullLenght, pullLenghtVector);

		if (pullLenght < this->damage)
		{
			actorTarget->dealDmg(15 * dt);
		}

		pullDir = XMVector3Normalize(pullDir);

		XMFLOAT3 kinvectorFloat3;
		XMStoreFloat3(&kinvectorFloat3, pullDir);

		actorTarget->setkineticVector((actorTarget->getkineticVector()) + (kinvectorFloat3 * (500.0f / pullLenght)));
	}
}

