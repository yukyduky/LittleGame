#pragma once
#ifndef BOSSMOVETOARENASTATE_H_
#define BOSSMOVETOARENASTATE_H_

#include "BossState.h"
class AIComponent;

class BossMoveToArenaState : public BossState
{
private:

public:
	BossMoveToArenaState(EnemyObject& pHead, AIComponent& pBrain, GamePlayState& pGPS, float bossScale);
	void cleanUp();
	void executeBehavior(); 
};

#endif // !BOSSINTROSTATE_H_
