
#include "SpFire.h"

SpFire::SpFire(GameObject* owner) : Spell(owner, NAME::FIRE)
{
	this->strength = 1;
	this->setType(SPELLTYPE::DAMAGE);
	this->setState(SPELLSTATE::READY);

	this->setCost(10);
	this->setCoolDown(0.4f);
	this->damage = 50;
	this->range = 1000;
	this->spinnValue = 0.0f;
}

SpFire::~SpFire()
{
}

bool SpFire::castSpell()
{
	this->actOwner = static_cast<ActorObject*>(this->owner);
	bool returnValue = false;

	if (this->getState() != SPELLSTATE::COOLDOWN)
	{
		// For further info, if needed, see 'useEnergy()' description
		if (this->actOwner->useEnergy(this->getCost()))
		{
			returnValue = true;

			ProjProp props(15, XMFLOAT4(1.0f, 0.1f, 0.5f, 0.1f), 500, this->range, true);

			this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.2f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0001f, 0.0001f), 50));

			Locator::getAudioManager()->play(SOUND::NAME::ABILITY1_GLYPH0);

			this->setState(SPELLSTATE::COOLDOWN);

			this->hits = 8;
		}
	}

	return returnValue;
}

void SpFire::upgrade(float modif)
{
	this->strength *= modif;
}


void SpFire::update()
{
	XMVECTOR dir = XMLoadFloat3(&this->owner->getDirection());
	XMMATRIX rotM = XMLoadFloat4x4(&this->owner->getRotationMatrix());
	this->spinnValue += 0.02f;
	this->owner->SETrotationMatrix(rotM * XMMatrixRotationAxis(dir, static_cast<float>(this->spinnValue)));
}

void SpFire::cleanUp()
{
}

void SpFire::collision(GameObject * target, Projectile* proj)
{
	OBJECTTYPE::TYPE type = target->getType();
	// IF target is an enemy AND target is NOT contained within the 'previouslyHit' list.
	if ((type == OBJECTTYPE::ENEMY || type == OBJECTTYPE::TYPE::GENERATOR || type == OBJECTTYPE::BOSS) &&
		!(std::find(proj->getPreviouslyHitList()->begin(), proj->getPreviouslyHitList()->end(), target)
			!=
			proj->getPreviouslyHitList()->end())) {
		
		static_cast<ActorObject*>(target)->dealDmg(this->damage);

		proj->getPreviouslyHitList()->push_back(target);

		this->hits--;
		if (this->hits == 0)
		{
			proj->setState(OBJECTSTATE::TYPE::DEAD);
			proj->getPreviouslyHitList()->clear();
		}
	}

	else if (target->getType() == OBJECTTYPE::INDESTRUCTIBLE) {
		proj->setState(OBJECTSTATE::TYPE::DEAD);
		proj->getPreviouslyHitList()->clear();
	}
}


////////////////////////////////////////////
//// GLYPH 1 ////////////////////////////////////////////
////////////////////////////////////////////
SpFireG1::SpFireG1(GameObject* owner) : SpFire(owner)
{
	// WHEN BALANCING, DONT FORGET THAT THERE IS A CAP ON PROJECTILES FOR THIS SPELL
	this->insertGlyph(GLYPHTYPE::GLYPH1);
	this->setCoolDown(0.07f);
	this->setCost(0.1f);
	this->range = 150.0f;
	this->damage = 10.0f;
}

SpFireG1::~SpFireG1()
{
}

bool SpFireG1::castSpell()
{
	this->actOwner = static_cast<ActorObject*>(this->owner);
	bool returnValue = false;

	if (this->getState() != SPELLSTATE::COOLDOWN)
	{
		// For further info, if needed, see 'useEnergy()' description
		if (this->actOwner->useEnergy(this->getCost()))
		{
			returnValue = true;

			ProjProp props(10, XMFLOAT4(1.0f, 0.1f, 0.5f, 0.1f), 300, this->range, false);

			XMVECTOR direction = XMLoadFloat3(&this->actOwner->getDirection());
			XMVECTOR axis = { 0.0f, 1.0f, 0.0f };
			
			XMVECTOR leDir = XMVector3Rotate(direction, XMQuaternionRotationAxis(axis, -0.3f));
			XMVECTOR riDir = XMVector3Rotate(direction, XMQuaternionRotationAxis(axis, 0.3f));

			this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.2f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0001f, 0.0001f), 50)
			)->setDirection(leDir);
			this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.2f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0001f, 0.0001f), 50)
			);
			this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.2f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0001f, 0.0001f), 50)
			)->setDirection(riDir);
			


			Locator::getAudioManager()->play(SOUND::NAME::ABILITY1_GLYPH1);

			this->setState(SPELLSTATE::COOLDOWN);

			this->hits = 8;
		}
	}

	return returnValue;
}


////////////////////////////////////////////
//// GLYPH 2 ////////////////////////////////////////////
////////////////////////////////////////////
SpFireG2::SpFireG2(GameObject* owner) : SpFire(owner)
{
	this->insertGlyph(GLYPHTYPE::GLYPH2);
	this->setCoolDown(this->getCoolDown() * 3.0f);
	this->damage = 200.0f;
	this->setCost(30.0f);
	this->range = 1000.0f;

	this->size = 0.0f;
}

SpFireG2::~SpFireG2()
{
}

bool SpFireG2::castSpell()
{
	this->actOwner = static_cast<ActorObject*>(this->owner);
	bool returnValue = false;

	if (this->getState() != SPELLSTATE::COOLDOWN)
	{
		// For further info, if needed, see 'useEnergy()' description
		if (this->actOwner->useEnergy(this->getCost()))
		{
			returnValue = true;

			ProjProp props(1, XMFLOAT4(1.0f, 0.1f, 0.5f, 0.1f), 400, this->range, PROJBEHAVIOR::ENLARGE);

			this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.2f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0001f, 0.0001f), 50));

			Locator::getAudioManager()->play(SOUND::NAME::ABILITY1_GLYPH2);

			this->setState(SPELLSTATE::COOLDOWN);
		}
	}

	return returnValue;
}

void SpFireG2::update()
{
	this->size += 70.0f * Locator::getGameTime()->getDeltaTime();
	XMMATRIX scaleM = XMMatrixScaling(this->size, this->size, this->size);
	this->owner->GETphysicsComponent()->updateBoundingArea(this->size);
	this->owner->SETscaleMatrix(scaleM);
}

void SpFireG2::collision(GameObject * target, Projectile * proj)
{
	float dt = Locator::getGameTime()->getDeltaTime();

	OBJECTTYPE::TYPE type = target->getType();
	// IF target is an enemy AND target is NOT contained within the 'previouslyHit' list.
	if ((type == OBJECTTYPE::ENEMY || type == OBJECTTYPE::TYPE::GENERATOR || type == OBJECTTYPE::BOSS)) 
	{
		static_cast<ActorObject*>(target)->dealDmg(this->damage * dt);
	}

	else if (target->getType() == OBJECTTYPE::INDESTRUCTIBLE) {
		proj->setState(OBJECTSTATE::TYPE::DEAD);
	}
}


////////////////////////////////////////////
//// GLYPH 3 ////////////////////////////////////////////
////////////////////////////////////////////
SpFireG3::SpFireG3(GameObject* owner) : SpFire(owner)
{
	this->insertGlyph(GLYPHTYPE::GLYPH3);
	this->setCoolDown(this->getCoolDown() * 4.5f);
	this->damage = 250.0f;
	this->cost = 10.0f;

	// Higher starts a crash
	this->range = 30;
}

SpFireG3::~SpFireG3()
{
}

bool SpFireG3::castSpell()
{
	this->actOwner = static_cast<ActorObject*>(this->owner);
	bool returnValue = false;

	if (this->getState() != SPELLSTATE::COOLDOWN)
	{
		// For further info, if needed, see 'useEnergy()' description
		if (this->actOwner->useEnergy(this->getCost()))
		{
			returnValue = true;
			XMFLOAT3 plyPos = this->getOwner()->GETPosition();

			//Slow speed to compensate for the gap between the boxes
			ProjProp props(5, XMFLOAT4(1.0f, 0.0f, 0.0f, 0.2f), 100, 10, false);

			for (int i = 1; i < this->range; i++)
			{
				Projectile* proj = this->spawnProj(props, 
					Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.2f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0001f, 0.0001f),
						50));
				proj->setPosition(plyPos + (this->actOwner->getDirection(i * props.size * 10)));
				// The multiplier below is half of above
				XMMATRIX scaleM = XMMatrixScaling(props.size * 5.0f, props.size, props.size); 
				proj->SETscaleMatrix(scaleM);
			}
			Locator::getAudioManager()->play(SOUND::NAME::ABILITY1_GLYPH3);

			this->setState(SPELLSTATE::COOLDOWN);
		}
	}

	return returnValue;
}
