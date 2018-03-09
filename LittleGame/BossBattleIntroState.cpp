#include "BossBattleIntroState.h"
#include "AIComponent.h"
#include "GamePlayState.h"
#include "BossMoveAwayFromArenaState.h"


BossBattleIntroState::BossBattleIntroState(EnemyObject& pHead, AIComponent& pBrain, GamePlayState& pGPS, float bossScale)
	: BossState(pHead, pBrain, pGPS, bossScale)
{
	this->pBrain->pushState(*this);
	this->grid = &this->pGPS->GETgrid();
	this->pHead->turnOnInvulnerability();
	this->pHead->setState(OBJECTSTATE::TYPE::BOSSINVULNERABLE);
}

void BossBattleIntroState::cleanUp()
{
}

void BossBattleIntroState::executeBehavior()
{
	int indexX = 0;
	int indexY = 0;
	switch (this->phase)
	{
	case INTROPHASE::FIRST:
		indexX = (*this->grid).size() - 6;
		indexY = (*this->grid)[0].size() / 2;
		this->counter += Locator::getGameTime()->getDeltaTime();
		if (this->counter > 3.0f) {
			for (int i = 0; i < (*this->grid).size(); i++) {
				for (int j = 0; j < (*this->grid)[i].size(); j++) {
					if ((i == indexX || i == indexX + 1) && (j == indexY || j == indexY - 1)) {
						(*this->grid)[i][j].state = TILESTATE::TELEPORT;
						this->tileIndex.push_back(Index(i, j));
					}
				}
			}
			this->phase = INTROPHASE::SECOND;
			this->counter = 0.0f;
		}
		break;
	case INTROPHASE::SECOND:
		this->pBrain->pushCommand(AICOMMANDS::BOSSATTACK01);
		if (this->pGPS->GETplayerSteppedOnBossTile()) {
			EnemyState* bossMoveAwayFromArenaState = new BossMoveAwayFromArenaState(
				*this->pHead, *this->pBrain, *this->pGPS, this->bossScale
			);
			for (int i = 0; i < this->tileIndex.size(); i++) {
				(*this->grid)[this->tileIndex[i].x][this->tileIndex[i].y].state = TILESTATE::ACTIVE;
			}
			this->pGPS->SETplayerSteppedOnBossTile(false);
		}
		break;
	default:
		break;
	}

}