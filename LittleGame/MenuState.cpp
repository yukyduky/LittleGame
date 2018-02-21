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

	this->camera.init(1000, 900);
	this->rio.initialize(this->camera, this->pointLights);
	this->initStartMenu();
	this->initOptionsMenu();

	//this->input = new KeyboardComponent(*this->highlight);
	
	this->pointLights.reserve(MAX_NUM_POINTLIGHTS);
	this->pointLights.push_back(Light(this->camera.GETcameraPosFloat3() , XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), 50.0f));

	this->displayMenu(MENUS::START);
}

void MenuState::cleanUp()
{
	// Direct internal objects
	this->rio.cleanUp();
	// this->camera.cleanUp();

	// GameObjects which will on their own clean up all of their connected components
	for (auto &iterator : this->menuObjects) {
		//iterator->cleanUp();
		delete iterator;
	}
	this->menuObjects.clear();
	this->graphics.clear();
}

void MenuState::pause() {

}

void MenuState::resume()
{
}

void MenuState::handleEvents(GameManager * gm) {
	MSG msg;

	while (gm->pollEvent(msg)) {
		// Exit the application when 'X' is pressed
		if (msg.message == WM_QUIT) {
			gm->quit();
		}
		else if (msg.message == WM_KEYUP)
		{
			switch (msg.wParam)
			{
			case VK_UP:
				this->menus[this->currMenu]->goUp();
				break;
			case VK_DOWN:
				this->menus[this->currMenu]->goDown();
				break;
			case VK_RETURN:
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
	stMenu = new Menu();

	MenuObject* object;
	Button* pButton;
	WCHAR* text;

	int nextID;

	//Background
	nextID = this->newID();
	object = new MenuObject(this->objD2D.GETRenderTarget());
	stMenu->addQuad(object);

	//Buttons
	nextID = this->newID();
	text = L"Options      ";
	pButton = new Button(this->objD2D.GETRenderTarget(), this->objD2D.GETTextFormat(), this, nextID, 
		{50,50, 200,100}, D2D1::ColorF::Red, 
		text, BEHAVIOR::GOOPTIONS);
	stMenu->addButton(pButton);

	nextID = this->newID();
	text = L"Start      ";
	pButton = new Button(this->objD2D.GETRenderTarget(), this->objD2D.GETTextFormat(), this, nextID, 
		{ 50,150, 200,200 }, D2D1::ColorF::DarkRed, 
		text, BEHAVIOR::GOSTART);
	stMenu->addButton(pButton);

	nextID = this->newID();
	text = L"Start Game   ";
	pButton = new Button(this->objD2D.GETRenderTarget(), this->objD2D.GETTextFormat(), this, nextID, 
		{ 50,250, 200,300 }, D2D1::ColorF::Aqua, 
		text, BEHAVIOR::STARTGAME);
	stMenu->addButton(pButton);


	this->menus[MENUS::START] = stMenu;
}

void MenuState::initOptionsMenu()
{
	Menu* opMenu;
	opMenu = new Menu();

	MenuObject* object;
	Button* pButton;
	WCHAR* text;
	//MenuRectComponent* quad;

	int nextID;

	//Background
	nextID = this->newID();
	object = new MenuObject(this->objD2D.GETRenderTarget(), nextID, { 0,0, 300,500 }, D2D1::ColorF::Blue);
	opMenu->addQuad(object);

	//Buttons
	text = L"Options      ";
	nextID = this->newID();
	pButton = new Button(this->objD2D.GETRenderTarget(), this->objD2D.GETTextFormat(), this, nextID, 
		{ 50,50, 200,100 }, D2D1::ColorF::Red, 
		text, BEHAVIOR::GOOPTIONS);
	opMenu->addButton(pButton);

	text = L"Start      ";
	nextID = this->newID();
	pButton = new Button( this->objD2D.GETRenderTarget(), this->objD2D.GETTextFormat(), this, nextID,
		{ 50,150, 200,200 }, D2D1::ColorF::DarkRed, 
		text, BEHAVIOR::GOSTART
	);
	opMenu->addButton(pButton);


	this->menus[MENUS::OPTIONS] = opMenu;
}
