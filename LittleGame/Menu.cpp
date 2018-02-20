#include "Menu.h"

Menu::Menu()
{
}

Menu::~Menu()
{
}

void Menu::addButton(Button * newButton)
{
	
	if (this->buttons.size() > 0)
	{
		newButton->SETNext(this->buttons.front());
		newButton->SETPrev(this->buttons.back());
		this->buttons.front()->SETPrev(newButton);
		this->buttons.back()->SETNext(newButton);
	}
	this->buttons.push_back(newButton);
	this->objects.push_back(newButton);

	this->current = this->buttons.front();
	this->buttons.front()->selectButton();
}

void Menu::addQuad(MenuObject * quad)
{
	this->objects.push_back(quad);
}

void Menu::addGraphic(GraphicsComponent * component)
{
	this->graphics.push_back(component);
}

void Menu::goUp()
{
	this->current->deSelectButton();
	this->current = this->current->GETPrev();
	this->current->selectButton();
}

void Menu::goDown()
{
	this->current->deSelectButton();
	this->current = this->current->GETNext();
	this->current->selectButton();
}
