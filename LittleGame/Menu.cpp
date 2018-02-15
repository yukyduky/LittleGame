#include "Menu.h"

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::addButton(Button* newButton)
{
	this->buttons.push_back(newButton);
	// Add when button is done
	//this->objects.push_back(newButton);
}

void Menu::addQuad(MenuObject * quad)
{
	this->objects.push_back(quad);
}

void Menu::addGraphic(GraphicsComponent * component)
{
	this->graphics.push_back(component);
}
