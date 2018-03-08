
#include "SpAutoAttack.h"

SpAutoAttack::SpAutoAttack(ActorObject* player) : Spell(player, NAME::AUTOATTACK)
{
	this->strength = 1;
	this->setType(SPELLTYPE::DAMAGE);
	this->setState(SPELLSTATE::READY);
	
	this->setCoolDown(0.3f);
	this->damage = 100.0f;
	this->range = 2000.0f;
}

SpAutoAttack::~SpAutoAttack()
{
}

bool SpAutoAttack::castSpell()
{
	bool returnValue = true;
	if (this->getState() == SPELLSTATE::COOLDOWN)
	{
		returnValue = false;
	}
	else
	{
		ProjProp props(10, XMFLOAT4(200.5f, 200.5f, 0.5f, 0.2f), 1000.0f, this->range, true);

		this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.5f, 0.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0001f, 0.0001f), 50));

		Locator::getAudioManager()->play(SOUND::NAME::BEEP1);

		this->setState(SPELLSTATE::COOLDOWN);
	}

	return returnValue;
}

void SpAutoAttack::upgrade(float modif)
{
	this->strength *= modif;
}


void SpAutoAttack::update()
{
	this->updateCD();
}

void SpAutoAttack::cleanUp()
{
}

void SpAutoAttack::collision(GameObject * target, Projectile* proj)
{
	if (target->getType() == OBJECTTYPE::ENEMY || target->getType() == OBJECTTYPE::GENERATOR) {
		this->getOwner()->addEnergy(5);

		static_cast<ActorObject*>(target)->dealDmg(this->damage);

		proj->setState(OBJECTSTATE::TYPE::DEAD);
	}

	else if (target->getType() == OBJECTTYPE::INDESTRUCTIBLE) {
		proj->setState(OBJECTSTATE::TYPE::DEAD);
	}
}

////////////////////////////////////////////
//// GLYPH 1 ////////////////////////////////////////////
////////////////////////////////////////////
SpAutoAttackG1::SpAutoAttackG1(ActorObject * player) : SpAutoAttack(player)
{
	this->insertGlyph(GLYPHTYPE::GLYPH1);
	this->setCoolDown(this->getCoolDown() * 2.0f);
}

SpAutoAttackG1::~SpAutoAttackG1()
{
}

bool SpAutoAttackG1::castSpell()
{
	bool returnValue = true;
	if (this->getState() == SPELLSTATE::COOLDOWN)
	{
		returnValue = false;
	}
	else
	{
		ProjProp props(10, XMFLOAT4(200.5f, 200.5f, 0.5f, 0.2f), 1000.0f, this->range, true);
		XMFLOAT3 distance = { this->getPlayer()->getDirection() * 80 };

		this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.5f, 0.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0001f, 0.0001f), 
			50));
		this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.5f, 0.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0001f, 0.0001f), 
			50))->setPosition(this->getPlayer()->GETPosition() + distance);
		distance = { this->getPlayer()->getDirection() * 120 };
		this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.5f, 0.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0001f, 0.0001f),
			50))->setPosition(this->getPlayer()->GETPosition() + distance);

		Locator::getAudioManager()->play(SOUND::NAME::BEEP1);

		this->setState(SPELLSTATE::COOLDOWN);
	}

	return returnValue;
}


////////////////////////////////////////////
//// GLYPH 2 ////////////////////////////////////////////
////////////////////////////////////////////
SpAutoAttackG2::SpAutoAttackG2(ActorObject * player) : SpAutoAttack(player)
{
	this->insertGlyph(GLYPHTYPE::GLYPH2);
	this->damage *= 2.5f;
	this->setCoolDown(this->getCoolDown() * 2.0f);
}

SpAutoAttackG2::~SpAutoAttackG2()
{
}

bool SpAutoAttackG2::castSpell()
{
	bool returnValue = true;
	if (this->getState() == SPELLSTATE::COOLDOWN)
	{
		returnValue = false;
	}
	else
	{
		ProjProp props(4, XMFLOAT4(200.5f, 200.5f, 0.5f, 0.2f), 1500.0f, this->range, true);
		XMFLOAT3 distance = { this->getPlayer()->getDirection() * 80 };

		this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.5f, 0.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0001f, 0.0001f),
			50));

		Locator::getAudioManager()->play(SOUND::NAME::BEEP1);

		this->setState(SPELLSTATE::COOLDOWN);
	}

	return returnValue;
}

void SpAutoAttackG2::collision(GameObject * target, Projectile * proj)
{
	if (target->getType() == OBJECTTYPE::ENEMY || target->getType() == OBJECTTYPE::GENERATOR) {
		this->getPlayer()->addEnergy(5);

		static_cast<ActorObject*>(target)->dealDmg(this->damage);

	}

	else if (target->getType() == OBJECTTYPE::INDESTRUCTIBLE) {
		proj->setState(OBJECTSTATE::TYPE::DEAD);
	}
}


////////////////////////////////////////////
//// GLYPH 3 ////////////////////////////////////////////
////////////////////////////////////////////
SpAutoAttackG3::SpAutoAttackG3(ActorObject * player) : SpAutoAttack(player)
{
	this->insertGlyph(GLYPHTYPE::GLYPH3);
	this->damage *= 0.5f;
	this->setCoolDown(this->getCoolDown() * 0.5f);
}

SpAutoAttackG3::~SpAutoAttackG3()
{
}
