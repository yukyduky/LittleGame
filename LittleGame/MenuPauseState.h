#pragma once
#ifndef PauseMenuState_H
#define PauseMenuState_H

#include "MenuState.h"

class MenuPauseState : public MenuState
{
private:
	static MenuPauseState sPauseMenuState;

	BOOL IsWindowMode = TRUE;
	WINDOWPLACEMENT wpc;
	LONG HWNDStyle = 0;
	LONG HWNDStyleEx = 0;
protected:
	virtual void addOptionsButtons(Menu* menu);
public:
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Initialize the 'PauseMenuState'.
	*/
	virtual void init();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Cleanup the 'PauseMenuState'; freeing memory, default settings, etc.
	*/
	static MenuPauseState* getInstance();

	void FullScreenSwitch();

	//std::array<Menu*, MENUS::SIZE> GETMenus() { return this->menus; };
	virtual Menu* initStartMenu();
	virtual Menu* initOptionsMenu();


};

#endif // !PauseMenuState_H
