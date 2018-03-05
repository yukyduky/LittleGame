
#include "SpFire.h"

SpFire::SpFire(ActorObject* player) : Spell(player, NAME::FIRE)
{
	this->strength = 1;
	this->setType(SPELLTYPE::DAMAGE);
	this->setState(SPELLSTATE::READY);

	this->setCost(10);
	this->setCoolDown(0.2f);
	this->damage = 50;
	this->range = 100;
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
		if (this->getPlayer()->useEnergy(this->getCost()))
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
	this->insertGlyph(GLYPHTYPE::GLYPH1);
	this->setCoolDown(0.1f);
}

SpFireG1::~SpFireG1()
{
}


////////////////////////////////////////////
//// GLYPH 2 ////////////////////////////////////////////
////////////////////////////////////////////
SpFireG2::SpFireG2(ActorObject * player) : SpFire(player)
{
	this->insertGlyph(GLYPHTYPE::GLYPH2);
	this->damage *= 1.2f;
}

SpFireG2::~SpFireG2()
{
}


////////////////////////////////////////////
//// GLYPH 3 ////////////////////////////////////////////
////////////////////////////////////////////
SpFireG3::SpFireG3(ActorObject * player) : SpFire(player)
{
	this->insertGlyph(GLYPHTYPE::GLYPH3);
	this->setCoolDown(this->getCoolDown() * 1.5f);
	this->damage *= 2.0f;
}

SpFireG3::~SpFireG3()
{
}
