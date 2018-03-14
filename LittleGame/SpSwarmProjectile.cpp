#include "SpSwarmProjectile.h"
#include "SwarmerState.h"
#include "Spell.h"
#include "GamePlayState.h"
#include "GameObject.h"

SpSwarmProjectile::SpSwarmProjectile(
	EnemyObject* pShooter, ActorObject* pPlayer, int* pActiveEnemiesCount,
	int projectilesMaxFlyingRange, int dmg, int attackRange, double cooldown) : EnemySpell(pShooter, pActiveEnemiesCount, NAME::ENEM_SWARM)
{
	this->pPlayer = pPlayer;
	this->projectilesMaxFlyingRange = projectilesMaxFlyingRange;
	this->damage = dmg;
	this->attackRange = attackRange;
	this->setCoolDown(cooldown);
	this->seekSpeed = 0.9;
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
		Light light;
		light.pos = this->getOwner()->GETPosition();
		light.diffuse = XMFLOAT3(0.25f, 0.0f, 0.0f);
		light.ambient = XMFLOAT3(0.0f, 0.0f, 0.0f);
		light.attenuation = XMFLOAT3(0.0f, 0.0001f, 0.0001f);
		light.specPower = 0.0f;

		ProjProp props(5, XMFLOAT4(1.0f, 0.412f, 0.71f, 1.0f), 200, this->projectilesMaxFlyingRange, false);
		Projectile* pProj = this->spawnProj(props, light);
		pProj->setSeeking(this->seekSpeed, this->pPlayer);

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
	float damage = this->damage * Locator::getGameTime()->getDeltaTime();
	switch (type) {
		case OBJECTTYPE::PLAYER: {
			static_cast<ActorObject*>(target)->dealDmg(this->damage);
			proj->setState(OBJECTSTATE::TYPE::DEAD);
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
	this->updateCD();
}

void SpSwarmProjectile::cleanUp()
{
	// The owner of me is dying, so reduce the activeEnemies!
	if (this->getOwner()->getType() == OBJECTTYPE::ENEMY) {
		AIComponent* trueInput = static_cast<AIComponent*>(this->getOwner()->GETinputComponent());
		SwarmerState* trueState = static_cast<SwarmerState*>(trueInput->getCurrentState());
		trueState->removeFromGrid();
		

		(*this->pActiveEnemiesCount)--;
	}
}
