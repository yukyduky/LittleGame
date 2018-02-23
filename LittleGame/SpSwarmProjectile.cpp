#include "SpSwarmProjectile.h"
#include "Spell.h"

SpSwarmProjectile::SpSwarmProjectile(
	EnemyObject* player,
	int range, int dmg, int aggroRange, double cooldown) : Spell(player, NAME::ENEM_SWARM)
{
	this->range = range;
	this->damage = dmg;
	this->aggroRange = aggroRange;
	this->setCoolDown(1.0f);
}
SpSwarmProjectile::~SpSwarmProjectile()
{

}

bool SpSwarmProjectile::castSpell()
{
	bool returnValue = true;
	if (this->getState() == SPELLSTATE::COOLDOWN)
	{
		returnValue = false;
	}
	else
	{
		ProjProp props(5, XMFLOAT4(1.0f, 1.0f, 0.5f, 0.1f), 150, this->range, false);
		Projectile* pProj = this->spawnProj(props);
		pProj->setSeeking(this->seekSpeed, this->getPlayer());

		Locator::getAudioManager()->play(SOUND::NAME::AHEM);

		this->setState(SPELLSTATE::COOLDOWN);
	}

	return returnValue;
}
void SpSwarmProjectile::upgrade(float modif)
{

}
void SpSwarmProjectile::collision(GameObject* target, Projectile* proj)
{
	OBJECTTYPE::TYPE type = target->getType();
	switch (type) {
		case OBJECTTYPE::PLAYER: {
			static_cast<ActorObject*>(target)->dealDmg(this->damage);
			break;
		};
		case OBJECTTYPE::INDESTRUCTIBLE: {
			proj->setState(OBJECTSTATE::TYPE::DEAD);
			break;
		}								
	}
}
void SpSwarmProjectile::update()
{

}

float SpSwarmProjectile::getDamage()
{
	return this->damage;
}

float SpSwarmProjectile::getRange()
{
	return this->range;
}
