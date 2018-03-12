#include "PauseMenuState.h"
#include "GameManager.h"
#include "Button.h"
#include "StateManager.h"

PauseMenuState PauseMenuState::sPauseMenuState;

void PauseMenuState::addOptionsButtons(Menu * menu)
{
	Button* pButton = nullptr;
	WCHAR* text = nullptr;
	int nextID;

	text = L"Master Volume +";
	nextID = this->newID();
	pButton = new Button(this, nextID,
		{ 20.0f,150.0f, 170.0f,50.0f }, D2D1::ColorF::Green,
		text, BEHAVIOR::VOLUMEUP);
	menu->addButton(pButton);

	text = L"Master Volume -";
	nextID = this->newID();
	pButton = new Button(this, nextID,
		{ 210.0f,150.0f, 170.0f,50.0f }, D2D1::ColorF::Blue,
		text, BEHAVIOR::VOLUMEDOWN);
	menu->addButton(pButton);

	text = L"Effect Volume +";
	nextID = this->newID();
	pButton = new Button(this, nextID,
		{ 20.0f,210.0f, 170.0f,50.0f }, D2D1::ColorF::Green,
		text, BEHAVIOR::VOLUMEUP_E);
	menu->addButton(pButton);

	text = L"Effect Volume -";
	nextID = this->newID();
	pButton = new Button(this, nextID,
		{ 210.0f,210.0f, 170.0f,50.0f }, D2D1::ColorF::Blue,
		text, BEHAVIOR::VOLUMEDOWN_E);
	menu->addButton(pButton);

	text = L"Music Volume +";
	nextID = this->newID();
	pButton = new Button(this, nextID,
		{ 20.0f,270.0f, 170.0f,50.0f }, D2D1::ColorF::Green,
		text, BEHAVIOR::VOLUMEUP_M);
	menu->addButton(pButton);

	text = L"Music Volume -";
	nextID = this->newID();
	pButton = new Button(this, nextID,
		{ 210.0f,270.0f, 170.0f,50.0f }, D2D1::ColorF::Blue,
		text, BEHAVIOR::VOLUMEDOWN_M);
	menu->addButton(pButton);

	text = L"Toggle Fullscreen";
	nextID = this->newID();
	pButton = new Button(this, nextID,
		{ 100.0f,370.0f, 200.0f,50.0f }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::WINDOWSWITCH);
	menu->addButton(pButton);
}

void PauseMenuState::init()
{
	MenuState::init();

	Locator::getD2D()->saveScreen();
	this->displayMenu(this->initStartMenu());
}

PauseMenuState* PauseMenuState::getInstance() {
	return &sPauseMenuState;
}

Menu* PauseMenuState::initStartMenu()
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
	textStr = L"Current level: " + std::to_wstring(Locator::getStatsHeader()->getStats().level) + L" of 10";
	nextID = this->newID();
	object = new MenuObject(nextID,
		{ 50.0f,-100.0f, 300.0f,100.0f }, D2D1::ColorF::DeepSkyBlue,
		textStr);
	menu->addQuad(object);

	//Buttons
	nextID = this->newID();
	text = L"Resume game";
	pButton = new Button(this, nextID,
		{ 100.0f,50.0f, 200.0f,150.0f }, D2D1::ColorF::Aqua,
		text, BEHAVIOR::RESUMEGAME);
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

Menu* PauseMenuState::initOptionsMenu()
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
	text = L"Back";
	nextID = this->newID();
	pButton = new Button(this, nextID,
		{ 100.0f,50.0f, 200.0f,50.0f }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::GOSTART);
	opMenu->addButton(pButton);

	this->addOptionsButtons(opMenu);

	//this->menus[MENUS::OPTIONS] = opMenu;
	return opMenu;
}


void PauseMenuState::FullScreenSwitch()
{
	if (this->IsWindowMode)
	{
		this->IsWindowMode = FALSE;
		GetWindowPlacement(Locator::getD3D()->GEThwnd(), &wpc);
		if (this->HWNDStyle == 0)
			this->HWNDStyle = GetWindowLong(Locator::getD3D()->GEThwnd(), GWL_STYLE);
		if (this->HWNDStyleEx == 0)
			this->HWNDStyleEx = GetWindowLong(Locator::getD3D()->GEThwnd(), GWL_EXSTYLE);

		LONG NewHWNDStyle = this->HWNDStyle;
		NewHWNDStyle &= ~WS_BORDER;
		NewHWNDStyle &= ~WS_DLGFRAME;
		NewHWNDStyle &= ~WS_THICKFRAME;

		LONG NewHWNDStyleEx = this->HWNDStyleEx;
		NewHWNDStyleEx &= ~WS_EX_WINDOWEDGE;

		SetWindowLong(Locator::getD3D()->GEThwnd(), GWL_STYLE, NewHWNDStyle | WS_POPUP);
		SetWindowLong(Locator::getD3D()->GEThwnd(), GWL_EXSTYLE, NewHWNDStyleEx | WS_EX_TOPMOST);
		ShowWindow(Locator::getD3D()->GEThwnd(), SW_SHOWMAXIMIZED);
	}
	else
	{
		this->IsWindowMode = TRUE;
		SetWindowLong(Locator::getD3D()->GEThwnd(), GWL_STYLE, this->HWNDStyle);
		SetWindowLong(Locator::getD3D()->GEThwnd(), GWL_EXSTYLE, this->HWNDStyleEx);
		ShowWindow(Locator::getD3D()->GEThwnd(), SW_SHOWNORMAL);
		SetWindowPlacement(Locator::getD3D()->GEThwnd(), &wpc);
	}
}