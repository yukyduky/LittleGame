
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
		this->damage = 10;
		break;
	case NAME::EXPLOSION:
		this->setCoolDown(1.3);
		this->damage = 50;
		break;
	case NAME::BOMB:
		this->setCoolDown(5.3);
		this->varible0 = 30;
		this->varible1 = 100;
		this->damage = this->varible0;
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


			break;
		case NAME::EXPLOSION:
			props = ProjProp(15, XMFLOAT3(200.5f, 0.5f, 0.5f), 500);
			this->spawnProj(props);

			break;
		case NAME::BOMB:
			props = ProjProp(30, XMFLOAT3(0.5f, 0.5f, 0.5f), 0);
			this->spawnProj(props);

			break;
		}

		this->setState(SPELLSTATE::COOLDOWN);

	}

	return returnValue;
}

void DamageSpell::upgrade(float modif)
{
	this->strength *= modif;
}

void DamageSpell::spawnProj(ProjProp props)
{
	Projectile* proj;
	XMFLOAT3 distance = { this->getPlayer()->getDirection() * 40 };
	XMFLOAT3 newPos = { this->getPlayer()->GETPosition() + distance };

	proj = this->getPlayer()->getPGPS()->initProjectile(newPos, this->getPlayer()->getDirection(), props);
	proj->setSpell(this);
	proj->SETrotationMatrix(this->getPlayer()->getRotationMatrix());


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

void DamageSpell::collision(GameObject * target, Projectile* proj)
{
	switch (this->name)
	{
	case NAME::AUTOATTACK:
		if (target->getType() == OBJECTTYPE::PLAYER)
		{
			//this->proj->setPosition(XMFLOAT3(200, 40, 200));
			proj->setState(OBJECTSTATE::TYPE::DEAD);
		}

		break;
	
	case NAME::EXPLOSION:
		
		//target->applyDamage(this->damage);
		
		break;
	case NAME::BOMB:

		if (this->damage < this->varible1)
		{
			this->damage++;
			XMMATRIX scaleM = XMMatrixScaling(this->damage, this->damage, this->damage);
			proj->SETscaleMatrix(scaleM);
			//proj->getPhyComp()->updateBounding(this->damage);
		}
		else
		{
			target->setPosition(XMFLOAT3(400, 100, 200));
			this->damage = this->varible0;
			proj->setState(OBJECTSTATE::TYPE::DEAD);
		}

		//target->setPosition(XMFLOAT3 (200, 100, 200));
		break;
	}

	//this->proj->cleanUp();
}
