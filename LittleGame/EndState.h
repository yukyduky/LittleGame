#pragma once
#ifndef ENDSTATE_H
#define ENDSTATE_H

#include "State.h"

class EndState : public State
{
private:
	static EndState sEndState;

public:
	static EndState* getInstance();
		
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Virtual Function.
	2. Initialize this state.
	*/
	virtual void init();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Virtual Function.
	2. Cleanup this state; freeing memory and setting settings for it back to default.
	*/
	virtual void cleanUp();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Virtual Function.
	2. Pause this state.
	*/
	virtual void pause();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Virtual Function.
	2. Resume this state.
	*/
	virtual void resume();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Virtual Function.
	2. Handle the events generated in this state.
	*/
	virtual void handleEvents(GameManager* gm);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Virtual Function.
	2. Update this state.
	*/
	virtual void update(GameManager* gm);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Virtual Function.
	2. Render this state.
	*/
	virtual void render(GameManager* gm);
};

#endif
