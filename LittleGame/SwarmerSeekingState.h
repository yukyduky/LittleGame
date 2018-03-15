#pragma once
#ifndef SWARMERSEEKINGSTATE_H
#define SWARMERSEEKINGSTATE_H

#include "SwarmerState.h"
#include "BossState.h"
#include "AIComponent.h"


class SwarmerSeekingState : public SwarmerState
{
private:
	struct Scale {
		float max = 5;
		float pulse = 0.2;
		float cooldown = 0.2;
		float velocity = 60;
		float range = 100;
	};
	Scale scale;

public:
	SwarmerSeekingState(EnemyObject& pHead, AIComponent& pBrain, Grid* pGrid_, size_t swarmerID);
	void cleanUp();
	void executeBehavior();

};


#endif
