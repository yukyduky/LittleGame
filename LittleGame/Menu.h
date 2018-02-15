#pragma once
#ifndef MENU_H
#define MENU_H

#include "MenuObject.h"
#include <vector>

// Template untill button is done
class Button;

class Menu
{
public:
	Menu();
	~Menu();

	void addButton(Button* newButton);
	void addQuad(MenuObject* quad);

protected:
	std::vector<Button*> buttons;
	std::vector<MenuObject*> objects;
};


#endif // !MENU_H
