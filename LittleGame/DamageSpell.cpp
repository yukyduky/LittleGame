
#include "DamageSpell.h"

DamageSpell::DamageSpell(ActorObject* player, NAME name) : Spell(player)
{
	this->strength = 1;
	this->name = name;
	this->setType(SPELLTYPE::DAMAGE);
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
		switch (this->name)
		{
		case NAME::EXPLOSION:

			//Spawn a projectile and fire it in direction

			break;
		}

	}

	return returnValue;
}

void DamageSpell::upgrade(float modif)
{
	this->strength *= modif;
}

void DamageSpell::spawnProj()
{
	ProjProp props(15, XMFLOAT3(200.5f, 0.5f, 0.5f), 5);

	this->proj = this->getPlayer()->getPGPS()->initProjectile(this->getPlayer()->getPosition(), this->getPlayer()->getDirection(), props);
	this->proj->setSpell(this);

	this->setState(SPELLSTATE::TRAVLING);

}

void DamageSpell::update()
{
	//if (this->proj->getState() == OBJECTSTATE::COLLISION)
	
	switch (this->name)
	{
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
	case NAME::EXPLOSION:
		//Template behavior
		

		target->setPosition(XMFLOAT3 (200, 100, 200));
		break;
	}

	this->proj->cleanUp();
}
