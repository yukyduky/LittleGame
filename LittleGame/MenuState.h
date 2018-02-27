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
	std::vector<Menu*> menus;

	D2D objD2D;
private:

	int ID = 0;

	// Handlers for different menus
	//std::array<Menu*, MENUS::SIZE> menus;
	//MENUS::TYPE currMenu;
	Menu* currMenu;

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

	//Button functions
	void displayMenu(Menu* menu);
	void startGame();
	void quitMenu() { this->quit = true; };

};

#endif // !MENUSTATE_H
#pragma once
