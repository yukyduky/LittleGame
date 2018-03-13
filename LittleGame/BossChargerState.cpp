#include "BossChargerState.h"
#include "AIComponent.h"
#include "GamePlayState.h"
#include "BlockComponent.h"

BossChargerState::BossChargerState(EnemyObject & pHead, AIComponent & pBrain, GamePlayState & pGPS, float bossScale)
	: BossState(pHead, pBrain, pGPS, bossScale)
{
	this->pBrain->pushState(*this);
	this->phase = CHARGERPHASE::FIRST;
	this->pHead->turnOnInvulnerability();
	this->startedSubmerging = false;
	this->counter = 0.0f;
}

void BossChargerState::executeBehavior()
{
	switch (this->phase)
	{
	// Prepare for the last phase. Make boss submerge under the floor and then return as three
	// smaller enemies(Chargers).
	case CHARGERPHASE::FIRST:
		if (!this->startedSubmerging) {
			this->pHead->setState(OBJECTSTATE::TYPE::BOSSSUBMERGE);
			this->startedSubmerging = true;
		}
		else {
			this->counter += Locator::getGameTime()->getDeltaTime();
			if (this->counter > 5.0f) {
				this->pGPS->spawnBossChargers(this->pHead->GEThp());
				this->counter = 0.0f;
				this->phase = CHARGERPHASE::SECOND;
			}
		}
		break;
	case CHARGERPHASE::SECOND:
		if (this->pGPS->checkBossChargersHealth() == 0.0f) {
			this->pHead->setState(OBJECTSTATE::TYPE::DEAD);
		}
		else {
			this->counter += Locator::getGameTime()->getDeltaTime();
			if (this->counter >= 5.0f) {
				this->pGPS->createABossWave();
				this->counter = 0.0f;
			}
		}
		break;
	default:
		break;
	}
}

void BossChargerState::cleanUp()
{
}