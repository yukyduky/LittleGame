#pragma once
#ifndef IGAMETIME_H
#define IGAMETIME_H

class IGameTime
{
public:
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Starts the Game Timer.
	*/
	virtual void StartTimer() = 0;
	
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Returns the total amount of time elapsed since the game was started.
	*/
	virtual double GetTime() = 0;

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Updates the 'deltaTime'(obj) since the last frame.
	*/
	virtual void UpdateFrameTime() = 0;

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Returns the 'deltaTime'(obj).
	*/
	virtual const double getDeltaTime() = 0;
};

#endif
