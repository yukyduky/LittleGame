
#include "SpAutoAttack.h"

SpAutoAttack::SpAutoAttack(GameObject* owner) : Spell(owner, NAME::AUTOATTACK)
{
	this->strength = 1;
	this->setType(SPELLTYPE::DAMAGE);
	this->setState(SPELLSTATE::READY);
	
	this->setCoolDown(0.3f);
	this->damage = 100.0f;
	this->range = 1000.0f;
}

SpAutoAttack::~SpAutoAttack()
{
}

bool SpAutoAttack::castSpell()
{
	this->actOwner = static_cast<ActorObject*>(this->owner);
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
	OBJECTTYPE::TYPE type = target->getType();
	if (type == OBJECTTYPE::ENEMY || type == OBJECTTYPE::GENERATOR ||
		type == OBJECTTYPE::BOSS) {
		GamePlayState::getInstance()->addEnergyToPlayer(this->cost);

		static_cast<ActorObject*>(target)->dealDmg(this->damage);

		proj->setState(OBJECTSTATE::TYPE::DEAD);
	}
	else if (type == OBJECTTYPE::INDESTRUCTIBLE) {
		proj->setState(OBJECTSTATE::TYPE::DEAD);
	}
}

////////////////////////////////////////////
//// GLYPH 1 ////////////////////////////////////////////
////////////////////////////////////////////
SpAutoAttackG1::SpAutoAttackG1(GameObject* owner) : SpAutoAttack(owner)
{
	this->insertGlyph(GLYPHTYPE::GLYPH1);
	this->setCoolDown(this->getCoolDown() * 2.0f);
	this->damage = (this->damage * 0.8f);
	this->cost *= 0.4f;
}

SpAutoAttackG1::~SpAutoAttackG1()
{
}

bool SpAutoAttackG1::castSpell()
{
	this->actOwner = static_cast<ActorObject*>(this->getOwner());
	bool returnValue = true;
	if (this->getState() == SPELLSTATE::COOLDOWN)
	{
		returnValue = false;
	}
	else
	{
		ProjProp props(10, XMFLOAT4(200.5f, 200.5f, 0.5f, 0.2f), 1000.0f, this->range, true);
		XMFLOAT3 dir = this->actOwner->getDirection();
		XMFLOAT3 distance = { dir * 80 };

		this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.5f, 0.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0001f, 0.0001f), 
			50));

		this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.5f, 0.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0001f, 0.0001f), 
			50))->setPosition(this->getOwner()->GETPosition() + distance);

		distance = { dir * 120 };

		this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.5f, 0.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0001f, 0.0001f),
			50))->setPosition(this->getOwner()->GETPosition() + distance);

		Locator::getAudioManager()->play(SOUND::NAME::BEEP1);

		this->setState(SPELLSTATE::COOLDOWN);
	}

	return returnValue;
}


////////////////////////////////////////////
//// GLYPH 2 ////////////////////////////////////////////
////////////////////////////////////////////
SpAutoAttackG2::SpAutoAttackG2(GameObject* owner) : SpAutoAttack(owner)
{
	this->insertGlyph(GLYPHTYPE::GLYPH2);
	this->setCoolDown(this->getCoolDown() * 3.0f);
	this->damage = (this->damage * 5.0f);
	this->cost *= 5.0f;
}

SpAutoAttackG2::~SpAutoAttackG2()
{
}

bool SpAutoAttackG2::castSpell()
{
	this->actOwner = static_cast<ActorObject*>(this->getOwner());
	bool returnValue = true;
	if (this->getState() == SPELLSTATE::COOLDOWN)
	{
		returnValue = false;
	}
	else
	{
		ProjProp props(4, XMFLOAT4(200.5f, 200.5f, 0.5f, 0.2f), 1500.0f, this->range, true);
		XMFLOAT3 dir = this->actOwner->getDirection();
		XMFLOAT3 distance = { dir * 80 };

		this->spawnProj(props, Light(XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.5f, 0.5f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0001f, 0.0001f),
			50));

		Locator::getAudioManager()->play(SOUND::NAME::BEEP1);

		this->setState(SPELLSTATE::COOLDOWN);
	}

	return returnValue;
}

void SpAutoAttackG2::collision(GameObject * target, Projectile * proj)
{
	OBJECTTYPE::TYPE type = target->getType();
	if (type == OBJECTTYPE::ENEMY || type == OBJECTTYPE::GENERATOR ||
		type == OBJECTTYPE::BOSS) {
		GamePlayState::getInstance()->addEnergyToPlayer(this->cost);

		static_cast<ActorObject*>(target)->dealDmg(this->damage);

	}
	else if (type == OBJECTTYPE::INDESTRUCTIBLE) {
		proj->setState(OBJECTSTATE::TYPE::DEAD);
	}
}


////////////////////////////////////////////
//// GLYPH 3 ////////////////////////////////////////////
////////////////////////////////////////////
SpAutoAttackG3::SpAutoAttackG3(GameObject* owner) : SpAutoAttack(owner)
{
	this->insertGlyph(GLYPHTYPE::GLYPH3);
	this->setCoolDown(this->getCoolDown() * 0.5f);
	this->damage = (this->damage * 0.5f);
}

SpAutoAttackG3::~SpAutoAttackG3()
{
}
