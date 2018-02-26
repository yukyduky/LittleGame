#pragma once
#ifndef ENDSTATE_H
#define ENDSTATE_H

#include "MenuState.h"

class EndState : public MenuState
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

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Virtual Function.
	2. Resume this state.
	*/
	virtual void resume();


	Menu* initRewardMenu();
};

#endif
