#pragma once
#ifndef PauseMenuState_H
#define PauseMenuState_H

#include "MenuState.h"

class PauseMenuState : public MenuState
{
private:
	static PauseMenuState sPauseMenuState;

	BOOL IsWindowMode = TRUE;
	WINDOWPLACEMENT wpc;
	LONG HWNDStyle = 0;
	LONG HWNDStyleEx = 0;

public:
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Initialize the 'PauseMenuState'.
	*/
	virtual void init();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Cleanup the 'PauseMenuState'; freeing memory, default settings, etc.
	*/

	static PauseMenuState* getInstance();

	void FullScreenSwitch();

	//std::array<Menu*, MENUS::SIZE> GETMenus() { return this->menus; };
	Menu* initStartMenu();
	Menu* initOptionsMenu();


};

#endif // !PauseMenuState_H
