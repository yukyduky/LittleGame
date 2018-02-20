#pragma once
#ifndef SWARMERSYNCINCSTATE_H
#define SWARMERSYNCINCSTATE_H

#include "SwarmerState.h"


class SwarmerSyncingState : public SwarmerState
{
private:

public:
	SwarmerSyncingState();

	virtual void executeBehavior();
};

#endif
