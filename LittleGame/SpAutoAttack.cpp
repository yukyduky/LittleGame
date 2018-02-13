
#include "SpAutoAttack.h"

SpAutoAttack::SpAutoAttack(ActorObject* player) : Spell(player, NAME::AUTOATTACK)
{
	this->strength = 1;
	this->setType(SPELLTYPE::DAMAGE);
	this->setState(SPELLSTATE::READY);
	
	this->setCoolDown(0.3);
	this->damage = 1;
	this->range = 50;
	//case NAME::EXPLOSION:
	//	this->setCoolDown(1.3);
	//	this->damage = 50;
	//	this->range = 230;
	//	break;
	//case NAME::BOMB:
	//	// start-size
	//	this->varible0 = 30;
	//	// end-size
	//	this->varible1 = 100;
	//	// only 1 bomb out
	//	this->flag0 = true;

	//	this->setCoolDown(5.3);
	//	this->damage = this->varible0;
	//	this->range = -1;
	//	break;
	//}
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
		ProjProp props(10, XMFLOAT3(200.5f, 200.5f, 0.5f), 1000, this->range);
		this->spawnProj(props);

		this->setState(SPELLSTATE::COOLDOWN);


		//ProjProp props;
		//switch (this->name)
		//{
		//case NAME::AUTOATTACK:
		//	props = ProjProp(10, XMFLOAT3(200.5f, 200.5f, 0.5f), 40);
		//	this->spawnProj(props);


		//	break;
		//case NAME::EXPLOSION:
		//	props = ProjProp(15, XMFLOAT3(200.5f, 0.5f, 0.5f), 500);
		//	this->spawnProj(props);

		//	break;
		//case NAME::BOMB:
		//	if (this->flag0)
		//	{
		//		props = ProjProp(30, XMFLOAT3(0.5f, 0.5f, 0.5f), 0);
		//		this->spawnProj(props);
		//		this->flag0 = false;
		//	}

		//	break;
		//}

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
	if (target->getType() == OBJECTTYPE::PLAYER) {
		proj->setState(OBJECTSTATE::TYPE::DEAD);
	}

	else if (target->getType() == OBJECTTYPE::ENEMY) {
		target->setState(OBJECTSTATE::TYPE::DEAD);
		proj->setState(OBJECTSTATE::TYPE::DEAD);
	}
}
