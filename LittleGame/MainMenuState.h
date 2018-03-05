#pragma once
#ifndef MainMenuState_H
#define MainMenuState_H

#include "MenuState.h"

class MainMenuState : public MenuState
{
private:
	static MainMenuState sMainMenuState;

	BOOL IsWindowMode = TRUE;
	WINDOWPLACEMENT wpc;
	LONG HWNDStyle = 0;
	LONG HWNDStyleEx = 0;

public:
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Initialize the 'MainMenuState'.
	*/
	virtual void init();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Cleanup the 'MainMenuState'; freeing memory, default settings, etc.
	*/

	static MainMenuState* getInstance();

	void FullScreenSwitch();

	//std::array<Menu*, MENUS::SIZE> GETMenus() { return this->menus; };
	Menu* initStartMenu();
	Menu* initOptionsMenu();


};

#endif // !MainMenuState_H
