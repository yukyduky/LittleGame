#pragma once
#ifndef HomeMenuState_H
#define HomeMenuState_H

#include "PauseMenuState.h"

class HomeMenuState : public PauseMenuState
{
private:
	static HomeMenuState sHomeMenuState;
public:
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Initialize the 'HomeMenuState'.
	*/
	virtual void init();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Cleanup the 'HomeMenuState'; freeing memory, default settings, etc.
	*/
	static HomeMenuState* getInstance();

	//std::array<Menu*, MENUS::SIZE> GETMenus() { return this->menus; };
	Menu* initStartMenu();
	Menu* initOptionsMenu();
};

#endif // !HomeMenuState_H
