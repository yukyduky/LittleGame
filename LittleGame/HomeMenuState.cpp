#include "HomeMenuState.h"
#include "GameManager.h"
#include "Button.h"
#include "StateManager.h"

HomeMenuState HomeMenuState::sHomeMenuState;

void HomeMenuState::init() 
{
	MenuState::init();

	this->displayMenu(this->initStartMenu());
}

HomeMenuState* HomeMenuState::getInstance() {
	return &sHomeMenuState;
}

Menu* HomeMenuState::initStartMenu()
{
	Menu* menu = nullptr;
	MenuObject* object = nullptr;
	Button* pButton = nullptr;
	WCHAR* text = nullptr;
	std::wstring textStr;
	int nextID;

	menu = new Menu();

	//Background
	nextID = this->newID();
	object = new MenuObject(nextID);
	menu->addQuad(object);
	textStr = L"Home menu";
	nextID = this->newID();
	object = new MenuObject(nextID,
		{ 50.0f,-100.0f, 300.0f,100.0f }, D2D1::ColorF::DeepSkyBlue,
		textStr);
	menu->addQuad(object);

	//Buttons
	nextID = this->newID();
	text = L"Start game";
	pButton = new Button(this, nextID,
		{ 100.0f,50.0f, 200.0f,150.0f }, D2D1::ColorF::Aqua,
		text, BEHAVIOR::STARTGAME);
	menu->addButton(pButton);

	nextID = this->newID();
	text = L"Options";
	pButton = new Button(this, nextID,
		{ 100.0f,250.0f, 200.0f,50.0f }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::GOOPTIONS);
	menu->addButton(pButton);

	nextID = this->newID();
	text = L"Quit";
	pButton = new Button(this, nextID,
		{ 100.0f,350.0f, 200.0f,50.0f }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::QUIT);
	menu->addButton(pButton);


	//this->menus[MENUS::START] = stMenu;
	return menu;
}

Menu* HomeMenuState::initOptionsMenu()
{
	Menu* opMenu = nullptr;
	MenuObject* object = nullptr;
	Button* pButton = nullptr;
	WCHAR* text = nullptr;
	int nextID;

	opMenu = new Menu();

	//Background
	nextID = this->newID();
	object = new MenuObject(nextID);
	opMenu->addQuad(object);

	//Buttons
	text = L"Back to home";
	nextID = this->newID();
	pButton = new Button(this, nextID,
		{ 100.0f,50.0f, 200.0f,50.0f }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::GOSTART_HOME);
	opMenu->addButton(pButton);

	this->addOptionsButtons(opMenu);

	//this->menus[MENUS::OPTIONS] = opMenu;
	return opMenu;
}