#pragma once
#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"
#include <vector>
#include <array>
#include <list>

#include "Menu.h"
#include "D2D.h"

class MenuState : public State
{
protected:
	// All objects
	std::vector<MenuObject*> menuObjects;

	Menu* currMenu;

	D2D* objD2D;
private:

	std::array<bool, 3> keyWasPressed;

	int ID = 0;

	bool quit;


public:
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Initialize the 'MenuState'.
	*/
	virtual void init();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Cleanup the 'MenuState'; freeing memory, default settings, etc.
	*/
	virtual void cleanUp();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Pause the 'MenuState'.
	*/
	virtual void pause();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Resume the 'MenuState'.
	*/
	virtual void resume();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Handle the events generated in the MenuState.
	*/
	virtual void handleEvents(GameManager* gm);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Update the MenuState.
	*/
	virtual void update(GameManager* gm);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Render the 'MenuState'
	*/
	virtual void render(GameManager* gm);

	/*RETURNS THE NEW ID*/
	int newID() { return this->ID++; }

	std::wstring intToWchar(int input);

	void addLoadOut(Menu* menu);
	WCHAR* getCurrSpellText(NAME name);

	//Button functions
	void displayMenu(Menu* menu);
	void startGame();
	void resumeGame();
	void restartGame();
	void quitMenu() { this->quit = true; };
	void statsWindow();
};

#endif // !MENUSTATE_H
#pragma once
