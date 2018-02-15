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
	this->ID = 0;
	
	this->pointLights.reserve(MAX_NUM_POINTLIGHTS);
	this->pointLights.push_back(Light(this->camera.GETcameraPosFloat3() , XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), 50.0f));

	//this->displayMenu(MENUS::START);
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

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}


void MenuState::update(GameManager * gm)
{
	
}

void MenuState::render(GameManager * gm) {
	rio.render(this->graphics);
	gm->setupSecondRenderPass();
	rio.injectResourcesIntoSecondPass();
	gm->display(this);
}

void MenuState::displayMenu(MENUS::TYPE menu)
{
	for ( auto &i : this->menus[menu]->getObjects())
	{
		this->menuObjects.push_back(i);
	}
}

MenuState* MenuState::getInstance() {
	return &sMenuState;
}

void MenuState::addGraphics(GraphicsComponent * graphicsComponent)
{
	this->graphics.push_back(graphicsComponent);
}

void MenuState::initStartMenu()
{
	Menu* stMenu;
	stMenu = new Menu();

	MenuObject* object;
	MenuRectComponent* background;

	int nextID = newID();


	XMFLOAT3 pos(500, 500.0f, 200);
	XMFLOAT3 scaleM(100, 1, 100);
	XMFLOAT4 color(0.0f, 0.0f, 0.5f, 0.2f);

	object = new MenuObject(nextID, pos);
	background = new MenuRectComponent(*stMenu, *object, this->camera, color, scaleM);

	//this->menuObjects.push_back(object);

	stMenu->addQuad(object);
	this->menus[MENUS::START] = stMenu;
}
