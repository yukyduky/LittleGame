#include "MainMenuState.h"
#include "GameManager.h"
#include "Button.h"
#include "StateManager.h"

MainMenuState MainMenuState::sMainMenuState;

void MainMenuState::init() 
{
	MenuState::init();

	this->displayMenu(this->initStartMenu());
}

MainMenuState* MainMenuState::getInstance() {
	return &sMainMenuState;
}

Menu* MainMenuState::initStartMenu()
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
	text = L"Start/Resume game";
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

Menu* MainMenuState::initOptionsMenu()
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
	text = L"Startmenu";
	nextID = this->newID();
	pButton = new Button(this, nextID,
		{ 100.0f,50.0f, 200.0f,50.0f }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::GOSTART);
	opMenu->addButton(pButton);

	text = L"Volume +";
	nextID = this->newID();
	pButton = new Button(this, nextID,
		{ 80.0f,150.0f, 120.0f,50.0f }, D2D1::ColorF::Green,
		text, BEHAVIOR::VOLUMEUP);
	opMenu->addButton(pButton);

	text = L"Volume -";
	nextID = this->newID();
	pButton = new Button(this, nextID,
		{ 260.0f,150.0f, 120.0f,50.0f }, D2D1::ColorF::Blue,
		text, BEHAVIOR::VOLUMEDOWN);
	opMenu->addButton(pButton);

	text = L"Toggle Fullscreen";
	nextID = this->newID();
	pButton = new Button(this, nextID,
		{ 100.0f,250.0f, 200.0f,50.0f }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::WINDOWSWITCH);
	opMenu->addButton(pButton);

	//this->menus[MENUS::OPTIONS] = opMenu;
	return opMenu;
}


void MainMenuState::FullScreenSwitch()
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