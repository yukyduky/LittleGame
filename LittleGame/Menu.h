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

	void addButton(Button* newButton);
	void addQuad(MenuObject* quad);
	void addGraphic(GraphicsComponent* component);

	std::list<Button*> getButtons() { return this->buttons; }
	std::vector<MenuObject*> getObjects() { return this->objects; }
	std::vector<GraphicsComponent*> getGraphics() { return this->graphics; }
	Button* GETCurrent() { return this->current; }

	void SETCurrent(Button* current) { this->current = current; }

	//Commands
	void goUp() { this->current = this->current->GETPrev(); };
	void goDown() { this->current = this->current->GETNext(); };
	void selectButton() { this->current->onPress(); };


protected:
	std::list<Button*> buttons;
	std::vector<MenuObject*> objects;
	Button* current;
	std::vector<GraphicsComponent*> graphics;
};


#endif // !MENU_H
