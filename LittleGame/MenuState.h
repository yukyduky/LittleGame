#pragma once
#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"
#include <vector>
#include <array>
#include "Commands.h"
#include <list>

#include "Menu.h"

#include "D2D.h"

namespace MENUS {
	enum TYPE {
		START, OPTIONS,
		SIZE
	};
}

class Command;

class MenuState : public State
{
private:
	static MenuState sMenuState;
	//GameManager* pGM;

	D2D objD2D;

	int ID = 0;

	// Handlers for different menus
	std::array<Menu*, MENUS::SIZE> menus;
	MENUS::TYPE currMenu;
	// All objects
	std::vector<MenuObject*> menuObjects;

	bool quit;

	BOOL IsWindowMode = TRUE;
	WINDOWPLACEMENT wpc;
	LONG HWNDStyle = 0;
	LONG HWNDStyleEx = 0;

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

	static MenuState* getInstance();

	//void addGraphics(GraphicsComponent* graphicsComponent);

	/*RETURNS THE NEW ID*/
	int newID() { return this->ID++; }

	//Button functions
	void displayMenu(MENUS::TYPE menu);
	void startGame();
	void quitMenu() { this->quit = true; };
	void FullScreenSwitch();

	//std::array<Menu*, MENUS::SIZE> GETMenus() { return this->menus; };
	void initStartMenu();
	void initOptionsMenu();


};

#endif // !MENUSTATE_H
