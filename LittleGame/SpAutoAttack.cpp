
#include "SpAutoAttack.h"

SpAutoAttack::SpAutoAttack(ActorObject* player) : Spell(player, NAME::AUTOATTACK)
{
	this->strength = 1;
	this->setType(SPELLTYPE::DAMAGE);
	this->setState(SPELLSTATE::READY);
	
	this->setCoolDown(0.3f);
	this->damage = 100.0f;
	this->range = 50.0f;
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
	
}

void SpAutoAttack::collision(GameObject * target, Projectile* proj)
{
	if (target->getType() == OBJECTTYPE::ENEMY) {
		this->getPlayer()->addEnergy(5);

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
	this->setCoolDown(0.1f);
}

SpAutoAttackG1::~SpAutoAttackG1()
{
}


////////////////////////////////////////////
//// GLYPH 2 ////////////////////////////////////////////
////////////////////////////////////////////
SpAutoAttackG2::SpAutoAttackG2(ActorObject * player) : SpAutoAttack(player)
{
	this->insertGlyph(GLYPHTYPE::GLYPH2);
	this->damage *= 1.2f;
}

SpAutoAttackG2::~SpAutoAttackG2()
{
}


////////////////////////////////////////////
//// GLYPH 3 ////////////////////////////////////////////
////////////////////////////////////////////
SpAutoAttackG3::SpAutoAttackG3(ActorObject * player) : SpAutoAttack(player)
{
	this->insertGlyph(GLYPHTYPE::GLYPH3);
	this->setCoolDown(0.5f);
	this->damage *= 2.0f;
}

SpAutoAttackG3::~SpAutoAttackG3()
{
}
