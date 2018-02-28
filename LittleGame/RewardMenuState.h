#pragma once
#ifndef RewardMenuState_H
#define RewardMenuState_H

#include "MenuState.h"

class RewardMenuState : public MenuState
{
private:
	static RewardMenuState sRewardMenuState;

	ActorObject* player = nullptr;
	int nrOfLoot;

public:
	static RewardMenuState* getInstance();
		
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Virtual Function.
	2. Initialize this state.
	*/
	virtual void init();

	virtual void handleEvents(GameManager* gm);

	Menu* initRewardMenu();

	void provide(ActorObject* player);
	void provide(int nrOfLoot) { this->nrOfLoot = nrOfLoot; };
	ActorObject* GETPlayer() { return this->player; };

	void startGame();
};

#endif
