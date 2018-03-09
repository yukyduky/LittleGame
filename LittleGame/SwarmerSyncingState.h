#pragma once
#ifndef SWARMERSYNCINCSTATE_H
#define SWARMERSYNCINCSTATE_H

#include "SwarmerState.h"


class SwarmerSyncingState : public SwarmerState
{
private:

public:
	SwarmerSyncingState(EnemyObject& pHead, AIComponent& pBrain, Grid* pGrid_, size_t swarmerID);

	virtual void executeBehavior();
};

#endif
