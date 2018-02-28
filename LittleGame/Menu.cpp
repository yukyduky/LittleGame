#include "Menu.h"

Menu::Menu()
{
}

Menu::~Menu()
{
	this->cleanUp();
}

void Menu::cleanUp()
{
	this->buttons.clear();
	for (auto &i : this->objects)
	{
		if (!i)
		{
			i->~MenuObject();
			delete i;
		}
	}
	this->objects.clear();
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

void Menu::goUp(int nrOfChoosen)
{
	this->current->deSelectButton();
	this->current = this->current->GETPrev(nrOfChoosen);
	this->current->selectButton();
}

void Menu::goDown(int nrOfChoosen)
{
	this->current->deSelectButton();
	this->current = this->current->GETNext(nrOfChoosen);
	this->current->selectButton();
}

void Menu::goUp()
{
	this->current->deSelectButton();
	this->current = this->current->GETPrev(1);
	this->current->selectButton();
}

void Menu::goDown()
{
	this->current->deSelectButton();
	this->current = this->current->GETNext(1);
	this->current->selectButton();
}

