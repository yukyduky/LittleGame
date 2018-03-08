#pragma once
#ifndef RewardMenuState_H
#define RewardMenuState_H

#include "MenuState.h"

class RewardMenuState : public MenuState
{
private:
	static RewardMenuState sRewardMenuState;
	std::vector<int> vecGlyph;

	ActorObject* player = nullptr;
	int nrOfLoot;

	std::vector<Spell*> spellPackage;

	WCHAR* getGlyphName(int name, int glyph);
public:
	static RewardMenuState* getInstance();
		
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Virtual Function.
	2. Initialize this state.
	*/
	virtual void init();

	virtual void handleEvents(GameManager* gm);

	Menu* initLootMenu();
	Menu* initEnemyUpgradeMenu();
	Menu* initNextLevelMenu();
	
	void provide(std::vector<int> savedGlyphs);
	void provide(ActorObject* player);
	void provide(int nrOfLoot) { this->nrOfLoot = nrOfLoot; };
	ActorObject* GETPlayer() { return this->player; };

	void startGame();
};

#endif
