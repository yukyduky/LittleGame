#pragma once
#ifndef SWARMERSEEKINGSTATE_H
#define SWARMERSEEKINGSTATE_H

#include "SwarmerState.h"
#include "BossState.h"
#include "AIComponent.h"


class SwarmerSeekingState : public SwarmerState
{
private:

public:
	SwarmerSeekingState(EnemyObject& pHead, AIComponent& pBrain, Grid* pGrid_, size_t swarmerID);
	void cleanUp();
	void executeBehavior();

};


#endif
