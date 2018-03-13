#pragma once
#ifndef BOSSGENERATORBATTLESTATE_H_
#define BOSSGENERATORBATTLESTATE_H_

#include "BossState.h"

namespace GENERATORBATTLEPHASE {
	enum PHASE { FIRST, ENEMYWAVESPHASE, GENERATORRISEPHASE, DAMAGEBOSSPHASE, SIZE };
}

class BossGeneratorBattleState : public BossState
{
private:
	GENERATORBATTLEPHASE::PHASE phase;
	std::vector<std::vector<tileData>>* grid;
	int numVerticalSquares;
	int numHorizontalSquares;
	bool teleported;
	bool generatorsSpawned;
	float counter;
	float bossMaxHealth;

public:
	BossGeneratorBattleState(EnemyObject& pHead, AIComponent& pBrain, GamePlayState& pGPS, float bossScale);
	void executeBehavior();
	void cleanUp();
};


#endif