#pragma once
#ifndef BOSSBATTLEINTROSTATE_H_
#define BOSSBATTLEINTROSTATE_H_

#include "BossState.h"
#include "LevelManager.h"

namespace INTROPHASE {
	enum PHASE{ FIRST, SECOND, SIZE };
};

class BossBattleIntroState : public BossState
{
private:
	float counter = 0.0f;
	std::vector<std::vector<tileData>>* grid;
	INTROPHASE::PHASE phase = INTROPHASE::FIRST;

public:
	BossBattleIntroState(EnemyObject& pHead, AIComponent& pBrain, GamePlayState& pGPS, float bossScale) : BossState(pHead, pBrain, pGPS, bossScale)
	{
		this->pBrain->pushState(*this);
		this->grid = &this->pGPS->GETgrid();
	}

	void executeBehavior() 
	{
		int indexX = 0;
		switch (this->phase)
		{
		case INTROPHASE::FIRST:
			indexX = (*this->grid).size() - 4;
			this->counter += Locator::getGameTime()->getDeltaTime();
			if (this->counter > 3.0f) {
				for (int i = 0; i < (*this->grid).size(); i++) {
					for (int j = 0; j < (*this->grid)[i].size(); j++) {
						if (i > indexX) {
							(*this->grid)[i][j].state = TILESTATE::BOSSTILE;
						}
					}
				}
				this->phase = INTROPHASE::SECOND;
				this->counter = 0.0f;
			}
			break;
		case INTROPHASE::SECOND:
			this->counter += Locator::getGameTime()->getDeltaTime();
			if (this->counter > 0.2f) {
				this->pBrain->pushCommand(AICOMMANDS::ATTACK);
			}
			break;
		default:
			break;
		}
		
		int test = 0;
	}

};

#endif // !BOSSBATTLEINTRO_H_
