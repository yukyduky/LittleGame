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
	Menu* stMenu;
	MenuObject* object;
	Button* pButton;
	WCHAR* text;
	int nextID;

	stMenu = new Menu();

	//Background
	nextID = this->newID();
	object = new MenuObject(this->objD2D.GETRenderTarget(), nextID);
	stMenu->addQuad(object);

	//Buttons
	nextID = this->newID();
	text = L"Start/Resume game";
	pButton = new Button(this->objD2D.GETRenderTarget(), this->objD2D.GETTextFormat(), this, nextID, 
		{ 100,50, 200,150 }, D2D1::ColorF::Aqua, 
		text, BEHAVIOR::RESUMEGAME);
	stMenu->addButton(pButton);

	nextID = this->newID();
	text = L"Options";
	pButton = new Button(this->objD2D.GETRenderTarget(), this->objD2D.GETTextFormat(), this, nextID, 
		{ 100,250, 200,50 }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::GOOPTIONS);
	stMenu->addButton(pButton);

	nextID = this->newID();
	text = L"Quit";
	pButton = new Button(this->objD2D.GETRenderTarget(), this->objD2D.GETTextFormat(), this, nextID,
		{ 100,350, 200,50 }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::QUIT);
	stMenu->addButton(pButton);

	nextID = this->newID();
	text = L"Auto Glyph1";
	pButton = new Button(this->objD2D.GETRenderTarget(), this->objD2D.GETTextFormat(), this, nextID,
		{ 100,450, 200,50 }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::ADDGLYPH,
		NAME::AUTOATTACK, GLYPHTYPE::GLYPH1);
	stMenu->addButton(pButton);


	//this->menus[MENUS::START] = stMenu;
	return stMenu;
}

Menu* MainMenuState::initOptionsMenu()
{
	Menu* opMenu;
	MenuObject* object;
	Button* pButton;
	WCHAR* text;
	int nextID;

	opMenu = new Menu();

	//Background
	nextID = this->newID();
	object = new MenuObject(this->objD2D.GETRenderTarget(), nextID);
	opMenu->addQuad(object);

	//Buttons
	text = L"Startmenu";
	nextID = this->newID();
	pButton = new Button( this->objD2D.GETRenderTarget(), this->objD2D.GETTextFormat(), this, nextID,
		{ 100,50, 200,50 }, D2D1::ColorF::DarkViolet,
		text, BEHAVIOR::GOSTART);
	opMenu->addButton(pButton);

	text = L"Volume +";
	nextID = this->newID();
	pButton = new Button(this->objD2D.GETRenderTarget(), this->objD2D.GETTextFormat(), this, nextID,
		{ 80,150, 120,50 }, D2D1::ColorF::Green,
		text, BEHAVIOR::VOLUMEUP);
	opMenu->addButton(pButton);

	text = L"Volume -";
	nextID = this->newID();
	pButton = new Button(this->objD2D.GETRenderTarget(), this->objD2D.GETTextFormat(), this, nextID,
		{ 260,150, 120,50 }, D2D1::ColorF::Blue,
		text, BEHAVIOR::VOLUMEDOWN);
	opMenu->addButton(pButton);

	text = L"Toggle Fullscreen";
	nextID = this->newID();
	pButton = new Button(this->objD2D.GETRenderTarget(), this->objD2D.GETTextFormat(), this, nextID,
		{ 100,250, 200,50 }, D2D1::ColorF::DarkViolet,
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