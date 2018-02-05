
#include "DamageSpell.h"

DamageSpell::DamageSpell(ActorObject* player, NAME name) : Spell(player)
{
	this->strength = 1;
	this->name = name;
	this->setType(SPELLTYPE::DAMAGE);
	this->setState(SPELLSTATE::READY);
	switch (this->name)
	{
	case NAME::AUTOATTACK:
		this->setCoolDown(0.3);
		break;
	case NAME::EXPLOSION:
		break;
	}
}

DamageSpell::~DamageSpell()
{
}

bool DamageSpell::castSpell()
{
	bool returnValue = true;
	if (this->getState() == SPELLSTATE::COOLDOWN)
	{
		returnValue = false;
	}
	else
	{
		ProjProp props;
		switch (this->name)
		{
		case NAME::AUTOATTACK:
			props = ProjProp(10, XMFLOAT3(200.5f, 200.5f, 0.5f), 40);
			this->spawnProj(props);

			this->setState(SPELLSTATE::COOLDOWN);

			break;
		case NAME::EXPLOSION:
			//Spawn a projectile and fire it in direction
			props = ProjProp(15, XMFLOAT3(200.5f, 0.5f, 0.5f), 5);
			this->spawnProj(props);

			this->setState(SPELLSTATE::COOLDOWN);
			break;
		}

	}

	return returnValue;
}

void DamageSpell::upgrade(float modif)
{
	this->strength *= modif;
}

void DamageSpell::spawnProj(ProjProp props)
{
	this->proj = this->getPlayer()->getPGPS()->initProjectile(this->getPlayer()->getPosition(), this->getPlayer()->getDirection(), props);
	this->proj->setSpell(this);


}

void DamageSpell::update()
{
	//if (this->proj->getState() == OBJECTSTATE::COLLISION)
	
	switch (this->name)
	{
	case NAME::AUTOATTACK:
		//While travling
		break;
	case NAME::EXPLOSION:
		if (this->getTSC() > 3)
		{
			//EXPLODE

			//Remove projectile
		}
		break;
	}
}

void DamageSpell::collision(GameObject * target)
{
	switch (this->name)
	{
	case NAME::AUTOATTACK:
		if(target->getType() == OBJECTTYPE::PLAYER)
		this->proj->setPosition(XMFLOAT3(200, 0, 200));
		break;
	
	case NAME::EXPLOSION:
		//Template behavior
		

		target->setPosition(XMFLOAT3 (200, 100, 200));
		break;
	}

	//this->proj->cleanUp();
}
