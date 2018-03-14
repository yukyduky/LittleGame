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
		case 6: {
			Locator::getAudioManager()->play(SOUND::NAME::ENEMYATTACK_6);
			break;
		}
		case 7: {
			Locator::getAudioManager()->play(SOUND::NAME::ENEMYATTACK_7);
			break;
		}
		case 8: {
			Locator::getAudioManager()->play(SOUND::NAME::ENEMYATTACK_8);
			break;
		}
		case 9: {
			Locator::getAudioManager()->play(SOUND::NAME::ENEMYATTACK_9);
			break;
		}
		case 10: {
			Locator::getAudioManager()->play(SOUND::NAME::ENEMYATTACK_10);
			break;
		}
		case 11: {
			Locator::getAudioManager()->play(SOUND::NAME::ENEMYATTACK_11);
			break;
		}
	}
	// Generates an ATTACK-GRUNT sound effect: 1 of 9 possibilities
	switch (Locator::getRandomGenerator()->GenerateInt(1, 9)) {
		case 1: {
			Locator::getAudioManager()->play(SOUND::NAME::ATTACKGRUNT_1);
			break;
		}
		case 2: {
			Locator::getAudioManager()->play(SOUND::NAME::ATTACKGRUNT_2);
			break;
		}
		case 3: {
			Locator::getAudioManager()->play(SOUND::NAME::ATTACKGRUNT_3);
			break;
		}
		case 4: {
			Locator::getAudioManager()->play(SOUND::NAME::ATTACKGRUNT_4);
			break;
		}
		case 5: {
			Locator::getAudioManager()->play(SOUND::NAME::ATTACKGRUNT_5);
			break;
		}
		case 6: {
			Locator::getAudioManager()->play(SOUND::NAME::ATTACKGRUNT_6);
			break;
		}
		case 7: {
			Locator::getAudioManager()->play(SOUND::NAME::ATTACKGRUNT_7);
			break;
		}
		case 8: {
			Locator::getAudioManager()->play(SOUND::NAME::ATTACKGRUNT_8);
			break;
		}
		case 9: {
			Locator::getAudioManager()->play(SOUND::NAME::ATTACKGRUNT_9);
			break;
		}
	};
	this->GETpPlayer()->dealDmg(this->damage);

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
	case 6: {
		Locator::getAudioManager()->play(SOUND::NAME::ENEMYATTACK_6);
		break;
	}
	case 7: {
		Locator::getAudioManager()->play(SOUND::NAME::ENEMYATTACK_7);
		break;
	}
	case 8: {
		Locator::getAudioManager()->play(SOUND::NAME::ENEMYATTACK_8);
		break;
	}
	case 9: {
		Locator::getAudioManager()->play(SOUND::NAME::ENEMYATTACK_9);
		break;
	}
	case 10: {
		Locator::getAudioManager()->play(SOUND::NAME::ENEMYATTACK_10);
		break;
	}
	case 11: {
		Locator::getAudioManager()->play(SOUND::NAME::ENEMYATTACK_11);
		break;
	}
	}
	// Generates an ATTACK-GRUNT sound effect: 1 of 9 possibilities
	switch (Locator::getRandomGenerator()->GenerateInt(1, 9)) {
	case 1: {
		Locator::getAudioManager()->play(SOUND::NAME::ATTACKGRUNT_1);
		break;
	}
	case 2: {
		Locator::getAudioManager()->play(SOUND::NAME::ATTACKGRUNT_2);
		break;
	}
	case 3: {
		Locator::getAudioManager()->play(SOUND::NAME::ATTACKGRUNT_3);
		break;
	}
	case 4: {
		Locator::getAudioManager()->play(SOUND::NAME::ATTACKGRUNT_4);
		break;
	}
	case 5: {
		Locator::getAudioManager()->play(SOUND::NAME::ATTACKGRUNT_5);
		break;
	}
	case 6: {
		Locator::getAudioManager()->play(SOUND::NAME::ATTACKGRUNT_6);
		break;
	}
	case 7: {
		Locator::getAudioManager()->play(SOUND::NAME::ATTACKGRUNT_7);
		break;
	}
	case 8: {
		Locator::getAudioManager()->play(SOUND::NAME::ATTACKGRUNT_8);
		break;
	}
	case 9: {
		Locator::getAudioManager()->play(SOUND::NAME::ATTACKGRUNT_9);
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
