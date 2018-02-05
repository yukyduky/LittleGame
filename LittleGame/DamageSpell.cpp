
#include "DamageSpell.h"

DamageSpell::DamageSpell(ActorObject* player, NAME name) : Spell(player)
{
	this->strength = 1;
	this->name = name;
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
}

void DamageSpell::spawnProj()
{
	XMFLOAT3 direction = XMFLOAT3(-std::cos(this->getPlayer()->getRotation()), 0.0f, std::sin(this->getPlayer()->getRotation()));
	ProjProp props(15, XMFLOAT3(200.5f, 0.5f, 0.5f));


	this->getPlayer()->getPGPS()->initProjectile(this->getPlayer()->getPosition(), direction, props);
}

void DamageSpell::update()
{
}
