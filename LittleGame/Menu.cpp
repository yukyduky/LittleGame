#include "Menu.h"

Menu::Menu()
{
	this->current = 0;
}

Menu::~Menu()
{
}

void Menu::addButton(Button * newButton)
{
	//Måste tänka på att men ändrar i back och front och inte bara i den nya

	if (this->buttons.size() > 0)
	{
		newButton->SETNext(this->buttons.front());
		newButton->SETPrev(this->buttons.back());
		this->buttons.front()->SETPrev(newButton);
		this->buttons.back()->SETNext(newButton);
	}
	this->buttons.push_back(newButton);
	this->objects.push_back(newButton);
	
}

void Menu::addQuad(MenuObject * quad)
{
	this->objects.push_back(quad);
}

void Menu::addGraphic(GraphicsComponent * component)
{
	this->graphics.push_back(component);
}
