
#include "SpFire.h"

SpFire::SpFire(ActorObject* player) : Spell(player, NAME::FIRE)
{
	this->strength = 1;
	this->setType(SPELLTYPE::DAMAGE);
	this->setState(SPELLSTATE::READY);

	this->setCost(10);
	this->setCoolDown(0.2f);
	this->damage = 50;
	this->range = 300;
}

SpFire::~SpFire()
{
}

bool SpFire::castSpell()
{
	bool returnValue = false;

	if (this->getState() != SPELLSTATE::COOLDOWN)
	{
		// For further info, if needed, see 'useEnergy()' description
		if (this->getOwner()->useEnergy(this->getCost()))
		{
			returnValue = true;

			ProjProp props(15, XMFLOAT4(1.0f, 0.1f, 0.5f, 0.1f), 500, this->range, true);

			this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.2f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0001f, 0.0001f), 50));

			Locator::getAudioManager()->play(SOUND::NAME::BEEP4);

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
	this->updateCD();
}

void SpFire::cleanUp()
{
}

void SpFire::collision(GameObject * target, Projectile* proj)
{
	// IF target is an enemy AND target is NOT contained within the 'previouslyHit' list.
	if ((target->getType() == OBJECTTYPE::ENEMY || target->getType() == OBJECTTYPE::TYPE::GENERATOR) &&
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
SpFireG1::SpFireG1(ActorObject * player) : SpFire(player)
{
	// WHEN BALANCING, DONT FORGET THAT THERE IS A CAP ON PROJECTILES FOR THIS SPELL
	this->insertGlyph(GLYPHTYPE::GLYPH1);
	this->setCoolDown(0.01f);
	this->setCost(0.1f);
	this->range = 5;
}

SpFireG1::~SpFireG1()
{
}

bool SpFireG1::castSpell()
{
	bool returnValue = false;

	if (this->getState() != SPELLSTATE::COOLDOWN)
	{
		// For further info, if needed, see 'useEnergy()' description
		if (this->getOwner()->useEnergy(this->getCost()))
		{
			returnValue = true;

			ProjProp props(10, XMFLOAT4(1.0f, 0.1f, 0.5f, 0.1f), 1000, this->range, false);

			XMVECTOR direction = XMLoadFloat3(&this->getOwner()->getDirection());
			XMVECTOR axis = { 0.0f, 1.0f, 0.0f };
			
			XMVECTOR leDir = XMVector3Rotate(direction, XMQuaternionRotationAxis(axis, -0.3f));
			XMVECTOR riDir = XMVector3Rotate(direction, XMQuaternionRotationAxis(axis, 0.3f));

			this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.2f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0001f, 0.0001f), 50)
			)->setDirection(leDir);
			this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.2f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0001f, 0.0001f), 50)
			);
			this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.2f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0001f, 0.0001f), 50)
			)->setDirection(riDir);
			


			Locator::getAudioManager()->play(SOUND::NAME::BEEP4);

			this->setState(SPELLSTATE::COOLDOWN);

			this->hits = 8;
		}
	}

	return returnValue;
}


////////////////////////////////////////////
//// GLYPH 2 ////////////////////////////////////////////
////////////////////////////////////////////
SpFireG2::SpFireG2(ActorObject * player) : SpFire(player)
{
	this->insertGlyph(GLYPHTYPE::GLYPH2);
	this->damage *= 2.2f;
	this->setCoolDown(2.0f);
	this->setCost(30.0f);
	this->range = 100.0f;
}

SpFireG2::~SpFireG2()
{
}

bool SpFireG2::castSpell()
{
	bool returnValue = false;

	if (this->getState() != SPELLSTATE::COOLDOWN)
	{
		// For further info, if needed, see 'useEnergy()' description
		if (this->getOwner()->useEnergy(this->getCost()))
		{
			returnValue = true;

			ProjProp props(1, XMFLOAT4(1.0f, 0.1f, 0.5f, 0.1f), 500, this->range, PROJBEHAVIOR::ENLARGE);

			this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.2f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0001f, 0.0001f), 50));

			Locator::getAudioManager()->play(SOUND::NAME::BEEP4);

			this->setState(SPELLSTATE::COOLDOWN);
		}
	}

	return returnValue;
}

void SpFireG2::collision(GameObject * target, Projectile * proj)
{
	// IF target is an enemy AND target is NOT contained within the 'previouslyHit' list.
	if ((target->getType() == OBJECTTYPE::ENEMY || target->getType() == OBJECTTYPE::TYPE::GENERATOR)) 
	{
		static_cast<ActorObject*>(target)->dealDmg(this->damage);
	}

	else if (target->getType() == OBJECTTYPE::INDESTRUCTIBLE) {
		proj->setState(OBJECTSTATE::TYPE::DEAD);
	}
}


////////////////////////////////////////////
//// GLYPH 3 ////////////////////////////////////////////
////////////////////////////////////////////
SpFireG3::SpFireG3(ActorObject * player) : SpFire(player)
{
	this->insertGlyph(GLYPHTYPE::GLYPH3);
	this->setCoolDown(this->getCoolDown() * 3.5f);
	this->damage *= 2.0f;

	// Higher starts a crash
	this->range = 23;
}

SpFireG3::~SpFireG3()
{
}

bool SpFireG3::castSpell()
{
	bool returnValue = false;

	if (this->getState() != SPELLSTATE::COOLDOWN)
	{
		// For further info, if needed, see 'useEnergy()' description
		if (this->getOwner()->useEnergy(this->getCost()))
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
				proj->setPosition(plyPos + (this->getOwner()->getDirection(i * props.size * 14)));
				// The multiplier below is half of above
				XMMATRIX scaleM = XMMatrixScaling(props.size * 7.0f, props.size, props.size); 
				proj->SETscaleMatrix(scaleM);
			}
			Locator::getAudioManager()->play(SOUND::NAME::BEEP4);

			this->setState(SPELLSTATE::COOLDOWN);
		}
	}

	return returnValue;
}
