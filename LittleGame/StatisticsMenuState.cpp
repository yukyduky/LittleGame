#include "StatisticsMenuState.h"

StatisticsMenuState StatisticsMenuState::sStatisticsMenuState;

StatisticsMenuState * StatisticsMenuState::getInstance()
{
	return &sStatisticsMenuState;
}

void StatisticsMenuState::init()
{
	MenuState::init();

	this->displayMenu(this->initStatsMenu());
}

Menu * StatisticsMenuState::initStatsMenu()
{
	Menu* menu = nullptr;
	MenuObject* object = nullptr;
	Button* pButton = nullptr;
	WCHAR* text = nullptr;
	int nextID;

	menu = new Menu();

	//Background
	nextID = this->newID();
	object = new MenuObject(nextID);
	menu->addQuad(object);

	//Buttons
	text = L"2";
	nextID = this->newID();
	pButton = new Button(this, nextID,
		{ 100.0f,50.0f, 200.0f,50.0f }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::GOSTART);
	menu->addButton(pButton);


	return menu;
}
