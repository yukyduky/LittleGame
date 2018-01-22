#pragma once
#ifndef STATE_H
#define STATE_H

class GameManager;

class State
{
public:
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Virtual Function.
	2. Initialize this state.
	*/
	virtual void init() = 0;

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Virtual Function.
	2. Cleanup this state; freeing memory and setting settings for it back to default.
	*/
	virtual void cleanup() = 0;

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Virtual Function.
	2. Pause this state.
	*/
	virtual void pause() = 0;

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Virtual Function.
	2. Resume this state.
	*/
	virtual void resume() = 0;

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Virtual Function.
	2. Handle the events generated in this state.
	*/
	virtual void handleEvents(GameManager* gm) = 0;

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Virtual Function.
	2. Update this state.
	*/
	virtual void update(GameManager* gm) = 0;

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Virtual Function.
	2. Render this state.
	*/
	virtual void render(GameManager* gm) = 0;
};

#endif
