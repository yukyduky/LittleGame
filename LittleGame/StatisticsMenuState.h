#pragma once
#ifndef STATISTICSMENUSTATE_H
#define STATISTICSMENUSTATE_H

#include "MenuState.h"
#include "Locator.h"

class StatisticsMenuState : public MenuState
{
public:
	static StatisticsMenuState* getInstance();

	virtual void init();

	Menu* initStatsMenu();

private:

	static StatisticsMenuState sStatisticsMenuState;

};

#endif //!STATISTICSMENUSTATE_H