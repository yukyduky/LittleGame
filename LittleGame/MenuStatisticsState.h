#pragma once
#ifndef STATISTICSMENUSTATE_H
#define STATISTICSMENUSTATE_H

#include "MenuState.h"
#include "Locator.h"

class MenuStatisticsState : public MenuState
{
public:
	static MenuStatisticsState* getInstance();

	virtual void init();

	Menu* initStatsMenu();
private:

	static MenuStatisticsState sStatisticsMenuState;

};

#endif //!STATISTICSMENUSTATE_H