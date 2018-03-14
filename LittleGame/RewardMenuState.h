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


	WCHAR* getGlyphName(int name, int glyph);
public:
	static RewardMenuState* getInstance();
		
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Virtual Function.
	2. Initialize this state.
	*/
	virtual void init();

	Menu* initLootMenu();
	Menu* initEnemyUpgradeMenu();
	Menu* initNextLevelMenu();
	
	void provide(ActorObject* player);
	void provide(int nrOfLoot) { this->nrOfLoot = nrOfLoot; };
	ActorObject* GETPlayer() { return this->player; };
	int getLoot() { return this->nrOfLoot; };

	void startGame();
};

#endif
