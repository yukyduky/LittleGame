#include "BossBulletHellState.h"
#include "Locator.h"

BossBulletHellState::BossBulletHellState(EnemyObject& pHead, AIComponent& pBrain, GamePlayState& pGPS, float bossScale)
	: BossState(pHead, pBrain, pGPS, bossScale)
{
	//Initialize variables
	this->counter = 0.0f;
	this->reload = 0.0f;
	this->currPhase = 0;
	//Make sure the boss is the correct color and is able to take damage
	this->pHead->turnOffInvulnerability();
	this->pHead->setState(OBJECTSTATE::TYPE::BOSSVULNERABLE);
}

void BossBulletHellState::executeBehavior()
{
	this->counter += Locator::getGameTime()->getDeltaTime();
	if (this->counter > 10.0f) {
		Locator::getRandomGenerator()->GenerateInt(0, BULLETHELLPHASE::SIZE - 1);
		this->counter = 0.0f;
	}
	switch (this->currPhase)
	{
	case BULLETHELLPHASE::FAN:
		if (this->reload > 1.0f) {
			
			
			this->reload = 0.0f;
		}
		break;
	case BULLETHELLPHASE::RANDOM:
		if (this->reload > 3.0f) {
			this->reload = 0.0f;
		}
		break;
	case BULLETHELLPHASE::FLAMETHROWER:
		if (this->reload > 3.0f) {
			this->reload = 0.0f;
		}
		break;
	default:
		break;
	}
}