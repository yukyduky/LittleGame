#pragma once
#ifndef BOSSBATTLEINTROSTATE_H_
#define BOSSBATTLEINTROSTATE_H_

#include "BossState.h"
#include "LevelManager.h"

namespace INTROPHASE {
	enum PHASE{ FIRST, STARTLOOP, INITBULLETHELL, BULLETHELL, DAMAGEPHASE, SIZE };
};

struct TeleportWave {
	int currentIndexX;
	std::vector<TILESTATE::STATE> pattern;
};

class BossBattleIntroState : public BossState
{
private:
	int waveIterations;
	int numSquareVertical;
	int numSquareHorizontal;
	bool teleported;
	float bossMaxHealth;
	std::vector<TeleportWave> waves;
	float counter = 0.0f;
	std::vector<std::vector<tileData>>* grid;
	INTROPHASE::PHASE phase = INTROPHASE::FIRST;
	std::vector<Index> tileIndex;

	void createNewWave();

public:
	BossBattleIntroState(EnemyObject& pHead, AIComponent& pBrain, GamePlayState& pGPS, float bossScale);
	void cleanUp();
	void executeBehavior();

};

#endif // !BOSSBATTLEINTRO_H_
