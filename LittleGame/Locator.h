#pragma once
#ifndef LOCATOR_H
#define LOCATOR_H

#include "IGameTime.h"

/* Service Locator pattern */

class Locator
{
private:
	static IGameTime* sGT;

public:
	static void provide(IGameTime* gameTime) { sGT = gameTime; }
	
	static IGameTime* getGameTime() { return sGT; }
};

#endif
