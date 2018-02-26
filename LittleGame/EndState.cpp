#include "EndState.h"
#include "GameManager.h"
#include "Button.h"
#include "StateManager.h"

EndState EndState::sEndState;

EndState * EndState::getInstance()
{
	return &sEndState;
}

void EndState::init()
{
	MenuState::init();

	this->displayMenu(this->initRewardMenu());
}

void EndState::resume()
{

}

Menu * EndState::initRewardMenu()
{
	Menu* menu;
	MenuObject* object;
	Button* pButton;
	WCHAR* text;
	int nextID;

	menu = new Menu();

	//Background
	nextID = this->newID();
	object = new MenuObject(this->objD2D.GETRenderTarget(), nextID);
	menu->addQuad(object);

	//Buttons
	nextID = this->newID();
	text = L"Start/Resume game";
	pButton = new Button(this->objD2D.GETRenderTarget(), this->objD2D.GETTextFormat(), this, nextID,
		{ 100,50, 200,150 }, D2D1::ColorF::Aqua,
		text, BEHAVIOR::RESUMEGAME);
	menu->addButton(pButton);

	nextID = this->newID();
	text = L"Options";
	pButton = new Button(this->objD2D.GETRenderTarget(), this->objD2D.GETTextFormat(), this, nextID,
		{ 100,250, 200,50 }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::GOOPTIONS);
	menu->addButton(pButton);

	nextID = this->newID();
	text = L"Quit";
	pButton = new Button(this->objD2D.GETRenderTarget(), this->objD2D.GETTextFormat(), this, nextID,
		{ 100,350, 200,50 }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::QUIT);
	menu->addButton(pButton);


	//this->menus[MENUS::START] = menu;
	return menu;
}
