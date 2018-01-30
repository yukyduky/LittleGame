#pragma once
#ifndef LOCATOR_H
#define LOCATOR_H

#include "IGameTime.h"
#include "IInputHandler.h"
#include "IAudioManager.h"

/* Service Locator pattern */

class Locator
{
private:
	static IGameTime* sGT;
	static IInputHandler* sIH;
	static IAudioManager* sAM;

public:
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Provides the address of 'gameTime'(obj) to the 'sGT'(ptr) Locator object.
	2. Passes the pointer to 'gameTime'(obj) as a parameter.
	*/
	static void provide(IGameTime* gameTime) { sGT = gameTime; }
	static void provide(IInputHandler* inputHandler) { sIH = inputHandler; }
	static void provide(IAudioManager* audioManager) { sAM = audioManager; }
	
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Returns the 'sGT'(ptr).
	2. 'sGT'(ptr) points to the address of 'gameTime'(obj), thereby returning that address.
	*/
	static IGameTime* getGameTime() { return sGT; }
	static IInputHandler* getInputHandler() { return sIH; }
	static IAudioManager* getAudioManager() { return sAM; }
};

#endif
