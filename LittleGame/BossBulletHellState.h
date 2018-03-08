#pragma once
#ifndef BOSSBULLETHELLSTATE_H_
#define BOSSBULLETHELLSTATE_H_

#include "BossState.h"

namespace BULLETHELLPHASE {
	enum PHASE {
		FAN, RANDOM, FLAMETHROWER, SIZE
	};
}

class BossBulletHellState : public BossState
{
private:
	float startHealth;
	float counter;
	float reload;
	int currPhase;
public:
	BossBulletHellState(EnemyObject& pHead, AIComponent& pBrain, GamePlayState& pGPS, float bossScale);
	void cleanUp();
	void executeBehavior();
};

#endif