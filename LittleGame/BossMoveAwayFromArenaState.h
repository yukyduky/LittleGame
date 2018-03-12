#pragma once
#ifndef BOSSMOVEAWAYFROMARENASTATE_H_
#define BOSSMOVEAWAYFROMARENASTATE_H_

#include "BossState.h"

class BossMoveAwayFromArenaState : public BossState
{
private:
public:
	BossMoveAwayFromArenaState(EnemyObject& pHead, AIComponent& pBrain, GamePlayState& pGPS, float bossScale);
	void cleanUp();
	void executeBehavior();
	void changeState();
};


#endif // !BOSSMOVEAWAYFROMARENA_H_
