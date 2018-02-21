#pragma once
#ifndef MENU_H
#define MENU_H

#include "MenuObject.h"
#include "Button.h"
#include <vector>
#include <list>

class GraphicsComponent;

class Menu
{
public:
	Menu();
	~Menu();
	void cleanUp();

	void addButton(Button* newButton);
	void addQuad(MenuObject* quad);

	std::list<Button*> getButtons() { return this->buttons; }
	std::vector<MenuObject*> getObjects() { return this->objects; }
	Button* GETCurrent() { return this->current; }

	void SETCurrent(Button* current) { this->current = current; }

	//Commands
	void goUp();
	void goDown();
	void pressButton() { this->current->onPress(); };


protected:
	std::list<Button*> buttons;
	std::vector<MenuObject*> objects;
	Button* current = nullptr;
};


#endif // !MENU_H
