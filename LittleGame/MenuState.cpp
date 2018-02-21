#include "MenuState.h"
#include "GamePlayState.h"
#include "GameManager.h"
#include "Locator.h"
#include "LineComponent.h"
#include "BlockComponent.h"
#include "KeyboardComponent.h"
#include "ControllerComponent.h"
#include "StateManager.h"
#include <SimpleMath.h>
#include <DirectXMath.h>


using namespace DirectX::SimpleMath;

MenuState MenuState::sMenuState;

void MenuState::init() {
	this->objD2D.Initialize();

	this->initStartMenu();
	this->initOptionsMenu();
	
	this->displayMenu(MENUS::START);
}

void MenuState::cleanUp()
{
	// GameObjects which will on their own clean up all of their connected components
	for (auto &iterator : this->menuObjects) {
		delete iterator;
	}
	this->menuObjects.clear();
}

void MenuState::pause() {

}

void MenuState::resume()
{
}

void MenuState::handleEvents(GameManager * gm) {
	MSG msg;

	while (gm->pollEvent(msg)) {
		// Exit the application when 'X' is pressed or the quit bool is true
		if (msg.message == WM_QUIT || this->quit) {
			gm->quit();
		}
		else if (msg.message == WM_KEYUP)
		{
			switch (msg.wParam)
			{
			case VK_UP:
			case 0x57:
				this->menus[this->currMenu]->goUp();
				break;
			case VK_DOWN:
			case 0x53:
				this->menus[this->currMenu]->goDown();
				break;
			case VK_RETURN:
			case VK_SPACE:
				this->menus[this->currMenu]->pressButton();
				break;
			default:
				break;
			}
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}


void MenuState::update(GameManager * gm)
{
}

void MenuState::render(GameManager * gm) {
	this->objD2D.OnRender(this->menuObjects);
}

void MenuState::displayMenu(MENUS::TYPE menu)
{
	this->menuObjects.clear();

	this->currMenu = menu;
	for ( auto &i : this->menus[menu]->getObjects())
	{
		this->menuObjects.push_back(i);
	}
}

void MenuState::startGame()
{
	StateManager::popState();
}

MenuState* MenuState::getInstance() {
	return &sMenuState;
}


void MenuState::initStartMenu()
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
	text = L"Start Game";
	pButton = new Button(this->objD2D.GETRenderTarget(), this->objD2D.GETTextFormat(), this, nextID, 
		{ 100,50, 200,150 }, D2D1::ColorF::Aqua, 
		text, BEHAVIOR::STARTGAME);
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


	this->menus[MENUS::START] = stMenu;
}

void MenuState::initOptionsMenu()
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

	text = L"Volume +  ";
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

	this->menus[MENUS::OPTIONS] = opMenu;
}


void MenuState::FullScreenSwitch()
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