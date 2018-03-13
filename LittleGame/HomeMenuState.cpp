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
	text = L"Controls";
	pButton = new Button(this, nextID,
		{ 100.0f, 250.0f, 200.0f, 50.0f }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::GOCONTROLS);
	menu->addButton(pButton);

	nextID = this->newID();
	text = L"Options";
	pButton = new Button(this, nextID,
		{ 100.0f,350.0f, 200.0f,50.0f }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::GOOPTIONS);
	menu->addButton(pButton);

	nextID = this->newID();
	text = L"Quit";
	pButton = new Button(this, nextID,
		{ 100.0f,450.0f, 200.0f,50.0f }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::QUIT);
	menu->addButton(pButton);


	//this->menus[MENUS::START] = stMenu;
	return menu;
}

Menu* HomeMenuState::initControlsMenu()
{
	Menu* contMenu = nullptr;
	MenuObject* object = nullptr;
	Button* pButton = nullptr;
	MenuObject* pObject = nullptr;
	WCHAR* text = nullptr;
	int nextID;

	contMenu = new Menu();

	//Buttons
	text = L"Back";
	nextID = this->newID();
	pButton = new Button(this, nextID,
		{ -200.0f, 50.0f, 200.0f, 50.0f }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::GOSTART_HOME);
	contMenu->addButton(pButton);

	//Controls Description
	text = L"1: Fireball (Selectable)";
	nextID = this->newID();
	pObject = new MenuObject(nextID,
		{ -800.0f, 350.0f, 200.0f, 200.0f }, D2D1::ColorF::Orchid,
		text);
	contMenu->addQuad(pObject);

	text = L"2: Bomb (Selectable)";
	nextID = this->newID();
	pObject = new MenuObject(nextID,
		{ -400.0f, 350.0f, 200.0f, 200.0f }, D2D1::ColorF::Gray,
		text);
	contMenu->addQuad(pObject);

	text = L"3: Dash (Quickcast)";
	nextID = this->newID();
	pObject = new MenuObject(nextID,
		{ 0.0f, 350.0f, 200.0f, 200.0f }, D2D1::ColorF::Orange,
		text);
	contMenu->addQuad(pObject);

	text = L"4: Slow Time (Quickcast)";
	nextID = this->newID();
	pObject = new MenuObject(nextID,
		{ 400.0f, 350.0f, 200.0f, 200.0f }, D2D1::ColorF::RoyalBlue,
		text);
	contMenu->addQuad(pObject);

	return contMenu;
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

	text = L"Input: Keyboard";
	nextID = this->newID();
	pButton = new Button(this, nextID,
		{ 100.0f,440.0f, 200.0f,50.0f }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::USECONTROLLER);
	opMenu->addButton(pButton);


	//this->menus[MENUS::OPTIONS] = opMenu;
	return opMenu;
}