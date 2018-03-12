#pragma once
#ifndef GAMETIME_H
#define GAMETIME_H

#include "IGameTime.h"

class GameTime : public IGameTime
{
private:
	// Variables
	double frequency = 0.0;
	__int64 CounterStart;
	__int64 prevCurrentCount;
	double deltaTime = 0.0;
	double multiplier = 1.0;

public:
	GameTime();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Starts the Game Timer.
	*/
	void StartTimer();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Returns the total amount of time elapsed since the game was started.
	*/
	double GetTime();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Updates the 'deltaTime'(obj) since the last frame.
	*/
	void UpdateFrameTime();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Returns the 'deltaTime'(obj).
	*/
	const double getDeltaTime();

	void setMultiplier(double val) {
		multiplier = val;
	}
	double getMultiplier() {
		return this->multiplier;
	}
};

#endif
