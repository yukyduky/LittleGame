#pragma once
#ifndef MENU_H
#define MENU_H

#include "MenuObject.h"
#include <vector>

// Template untill button is done
class Button;
class GraphicsComponent;

class Menu
{
public:
	Menu();
	~Menu();

	void addButton(Button* newButton);
	void addQuad(MenuObject* quad);
	void addGraphic(GraphicsComponent* component);

	std::vector<MenuObject*> getObjects() { return this->objects; }

protected:
	std::vector<Button*> buttons;
	std::vector<MenuObject*> objects;
	std::vector<GraphicsComponent*> graphics;
};


#endif // !MENU_H
