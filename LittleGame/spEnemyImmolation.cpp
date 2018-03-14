#include "SpEnemyImmolation.h"
#include "EnemySpell.h"
#include "IncludeSpells.h"

SpEnemyImmolation::SpEnemyImmolation(
	EnemyObject* pShooter, ActorObject* pPlayer, int* pActiveEnemiesCount,
	float damage, float attackCooldown, float attackRange) : EnemySpell(pShooter, pActiveEnemiesCount, NAME::ENEM_IMMO)
{
	this->setpPlayer(pPlayer);
	this->setDamage(damage);
	this->setCoolDown(attackCooldown);
	this->setAttackRange(attackRange);
}

bool SpEnemyImmolation::castSpell()
{
	this->actOwner = static_cast<ActorObject*>(this->getOwner());
	// Only coded to work against 1 player atm!
	float dt = Locator::getGameTime()->getDeltaTime();
	this->GETpPlayer()->dealDmg(this->damage * dt);

	// Generates an ATTACK sound effect: 1 of 11 possibilities
	switch (Locator::getRandomGenerator()->GenerateInt(1, 11)) {
		case 1: {
			Locator::getAudioManager()->play(SOUND::NAME::ENEMYATTACK_1);
			break;
		}
		case 2: {
			Locator::getAudioManager()->play(SOUND::NAME::ENEMYATTACK_2);
			break;
		}
		case 3: {
			Locator::getAudioManager()->play(SOUND::NAME::ENEMYATTACK_3);
			break;
		}
		case 4: {
			Locator::getAudioManager()->play(SOUND::NAME::ENEMYATTACK_4);
			break;
		}
		case 5: {
			Locator::getAudioManager()->play(SOUND::NAME::ENEMYATTACK_5);
			break;
		}
	}

	return true;
}

void SpEnemyImmolation::upgrade(float modif)
{
	this->damage *= modif;
}

void SpEnemyImmolation::collision(GameObject * target, Projectile * proj)
{
	// No collision for spells without projectiles
}

void SpEnemyImmolation::update()
{
	this->updateCD();
}

void SpEnemyImmolation::cleanUp()
{
	// The owner of me is dying, so reduce the activeEnemies!
	if (this->getOwner()->getType() == OBJECTTYPE::ENEMY) {
		(*this->pActiveEnemiesCount)--;
	}
}
