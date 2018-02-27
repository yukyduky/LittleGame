#pragma once
#ifndef RewardMenuState_H
#define RewardMenuState_H

#include "MenuState.h"

class RewardMenuState : public MenuState
{
private:
	static RewardMenuState sRewardMenuState;

	ActorObject* player;

public:
	static RewardMenuState* getInstance();
		
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Virtual Function.
	2. Initialize this state.
	*/
	virtual void init();


	Menu* initRewardMenu();

	void provide(ActorObject* player);
	ActorObject* GETPlayer() { return this->player; };

	void startGame();
};

#endif
