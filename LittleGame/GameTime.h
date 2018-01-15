#pragma once
#ifndef GAMETIME_H
#define GAMETIME_H

#include "IGameTime.h"

class GameTime : public IGameTime
{
private:
	// Variables
	double frequency;
	__int64 CounterStart;
	__int64 prevCurrentCount;
	double deltaTime;

public:
	GameTime();

	// Starts the timer
	void StartTimer();
	// Returns the time that the application has been running for
	double GetTime();
	// Updates the delta time since the last frame
	void UpdateFrameTime();
	// Get delta time
	const double getDeltaTime();
};

#endif
