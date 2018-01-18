#pragma once
#ifndef LOCATOR_H
#define LOCATOR_H

#include "IGameTime.h"
#include "IInputHandler.h"

/* Service Locator pattern */

class Locator
{
private:
	static IGameTime* sGT;
	static IInputHandler* sIH;

public:
	static void provide(IGameTime* gameTime) { sGT = gameTime; }
	static void provide(IInputHandler* inputHandler) { sIH = inputHandler; }
	
	static IGameTime* getGameTime() { return sGT; }
	static IInputHandler* getInputHandler() { return sIH; }
};

#endif
