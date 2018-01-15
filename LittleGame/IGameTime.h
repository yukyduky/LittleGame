#pragma once
#ifndef IGAMETIME_H
#define IGAMETIME_H

class IGameTime
{
public:
	// Starts the timer
	virtual void StartTimer() = 0;
	// Returns the time that the application has been running for
	virtual double GetTime() = 0;
	// Updates the delta time since the last frame
	virtual void UpdateFrameTime() = 0;
	// Get delta time
	virtual const double getDeltaTime() = 0;
};

#endif
