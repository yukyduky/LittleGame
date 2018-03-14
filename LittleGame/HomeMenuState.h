#pragma once
#ifndef HomeMenuState_H
#define HomeMenuState_H

#include "MenuPauseState.h"

class HomeMenuState : public MenuPauseState
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
	Menu* initControlsMenu();
	Menu* initOptionsMenu();
};

#endif // !HomeMenuState_H
