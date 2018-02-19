#include "MenuState.h"
#include "GamePlayState.h"
#include "GameManager.h"
#include "Locator.h"
#include "MenuRectComponent.h"
#include "LineComponent.h"
#include "BlockComponent.h"
#include "KeyboardComponent.h"
#include "ControllerComponent.h"
#include <SimpleMath.h>
#include <DirectXMath.h>


using namespace DirectX::SimpleMath;

MenuState MenuState::sMenuState;

void MenuState::init() {
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
			this->menus[this->currMenu]->goDown();
			this->highlight->SETPosition(this->menus[this->currMenu]->GETCurrent()->GETPosition());

			//this->graphics.pop_back();
			this->menus[this->currMenu]->getGraphics().pop_back();
			XMFLOAT3 scaleM(25, 1, 10);
			XMFLOAT4 color(0.9f, 0.9f, 0.9f, 0.9f);
			MenuRectComponent* quad = new MenuRectComponent(*this->menus[this->currMenu], *this->highlight, this->camera, color, scaleM);
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}


void MenuState::update(GameManager * gm)
{
	//The only object in each menu that will need to update
	this->highlight->updateWorldMatrix();

	displayMenu(this->currMenu);
}

void MenuState::render(GameManager * gm) {
	rio.render(this->graphics);
	gm->setupSecondRenderPass();
	rio.injectResourcesIntoSecondPass();
	gm->display(this);
}

void MenuState::displayMenu(MENUS::TYPE menu)
{
	this->menuObjects.clear();
	this->graphics.clear();

	this->currMenu = menu;
	for ( auto &i : this->menus[menu]->getObjects())
	{
		this->menuObjects.push_back(i);
	}
	for (auto &i : this->menus[menu]->getGraphics())
	{
		this->graphics.push_back(i);
	}
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
	MenuRectComponent* quad;

	int nextID;

	//Background
	XMFLOAT3 pos(500, 500.0f, 200);
	XMFLOAT3 scaleM(100, 1, 100);
	XMFLOAT4 color(0.0f, 0.0f, 0.5f, 0.2f);
	nextID = newID();
	object = new MenuObject(nextID, pos);
	quad = new MenuRectComponent(*stMenu, *object, this->camera, color, scaleM);
	stMenu->addQuad(object);

	//BUTTONS
	//Options
	pos = XMFLOAT3(450, 510.0f, 200);
	scaleM = XMFLOAT3(20, 1, 10);
	color = XMFLOAT4(0.0f, 1.0f, 0.5f, 0.2f);
	nextID = newID();
	pButton = new Button(nextID, pos, BEHAVIOR::GOOPTIONS, this);
	quad = new MenuRectComponent(*stMenu, *pButton, this->camera, color, scaleM);
	stMenu->addButton(pButton);

	//Start game
	pos = XMFLOAT3(460, 510.0f, 170);
	scaleM = XMFLOAT3(20, 1, 10);
	color = XMFLOAT4(0.0f, 0.8f, 0.2f, 0.2f);
	nextID = newID();
	pButton = new Button(nextID, pos, BEHAVIOR::STARTGAME, this);
	quad = new MenuRectComponent(*stMenu, *pButton, this->camera, color, scaleM);
	stMenu->addButton(pButton);

	//Set button to select for highlight
	stMenu->SETCurrent(stMenu->getButtons().front());

	//Highlighted button
	pos = stMenu->GETCurrent()->GETPosition();
	scaleM = XMFLOAT3(25, 1, 10);
	color = XMFLOAT4(0.9f, 0.9f, 0.9f, 0.9f);
	nextID = newID();
	this->highlight = new MenuObject(nextID, pos);
	quad = new MenuRectComponent(*stMenu, *this->highlight, this->camera, color, scaleM);
	stMenu->addQuad(this->highlight);

	this->menus[MENUS::START] = stMenu;
}

void MenuState::initOptionsMenu()
{
	Menu* opMenu;
	opMenu = new Menu();

	MenuObject* object;
	Button* pButton;
	MenuRectComponent* quad;

	int nextID;

	//Background
	XMFLOAT3 pos(500, 500.0f, 200);
	XMFLOAT3 scaleM(100, 1, 100);
	XMFLOAT4 color(0.0f, 0.7f, 0.9f, 0.2f);
	nextID = newID();
	object = new MenuObject(nextID, pos);
	quad = new MenuRectComponent(*opMenu, *object, this->camera, color, scaleM);
	opMenu->addQuad(object);


	//BUTTONS
	//Startmenu
	pos = XMFLOAT3(450, 510.0f, 200);
	scaleM = XMFLOAT3(20, 1, 10);
	color = XMFLOAT4(0.0f, 1.0f, 0.5f, 0.2f);
	nextID = newID();
	pButton = new Button(nextID, pos, BEHAVIOR::GOSTART, this);
	quad = new MenuRectComponent(*opMenu, *pButton, this->camera, color, scaleM);
	opMenu->addButton(pButton);

	//Set button to select for highlight
	opMenu->SETCurrent(opMenu->getButtons().front());

	//Highlighted button
	pos = opMenu->GETCurrent()->GETPosition();
	scaleM = XMFLOAT3(25, 1, 10);
	color = XMFLOAT4(0.9f, 0.9f, 0.9f, 0.9f);
	nextID = newID();
	this->highlight = new MenuObject(nextID, pos);
	quad = new MenuRectComponent(*opMenu, *this->highlight, this->camera, color, scaleM);
	opMenu->addQuad(this->highlight);


	this->menus[MENUS::OPTIONS] = opMenu;
}
