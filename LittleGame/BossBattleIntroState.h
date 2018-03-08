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
	std::vector<Index> tileIndex;

public:
	BossBattleIntroState(EnemyObject& pHead, AIComponent& pBrain, GamePlayState& pGPS, float bossScale);
	void executeBehavior();

};

#endif // !BOSSBATTLEINTRO_H_
