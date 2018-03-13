#pragma once
#ifndef BOSSCHARGERSTATE_H_
#define BOSSCHARGERSTATE_H_

#include "BossState.h"

namespace CHARGERPHASE {
	enum PHASE {
		FIRST, SECOND, SIZE
	};
}

class BossChargerState : public BossState
{
private:
	CHARGERPHASE::PHASE phase;
	bool startedSubmerging;
	float counter;
public:
	BossChargerState(EnemyObject& pHead, AIComponent& pBrain, GamePlayState& pGPS, float bossScale);
	void executeBehavior();
	void cleanUp();

};

#endif
