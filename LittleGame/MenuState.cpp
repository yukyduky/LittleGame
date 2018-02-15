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
	this->camera.init(Locator::getD3D()->GETwWidth(), Locator::getD3D()->GETwHeight());
	this->rio.initialize(this->camera, this->pointLights);
	this->initStartMenu();
	
	this->pointLights.reserve(MAX_NUM_POINTLIGHTS);
	this->pointLights.push_back(Light(this->camera.GETcameraPosFloat3() , XMFLOAT3(1.0f, 1.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), 50.0f));

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
	//MSG msg;

	//while (gm->pollEvent(msg)) {
	//	// Exit the application when 'X' is pressed
	//	if (msg.message == WM_QUIT) {
	//		gm->quit();
	//	}

	//	TranslateMessage(&msg);
	//	DispatchMessage(&msg);
	//}
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

MenuState* MenuState::getInstance() {
	return &sMenuState;
}

void MenuState::addGraphics(GraphicsComponent * graphicsComponent)
{
	this->graphics.push_back(graphicsComponent);
}

void MenuState::initStartMenu()
{
	//Menu* stMenu;

	MenuObject* object;
	MenuRectComponent* background;

	int nextID = newID();


	XMFLOAT3 pos(100, -0.5f, 100);
	XMFLOAT3 scaleM(100, 0, 100);
	XMFLOAT4 color(1.0f, 0.0f, 1.0f, 1.0f);

	object = new MenuObject(nextID);
	background = new MenuRectComponent(*this, *object, this->camera, color, scaleM);

	this->menuObjects.push_back(object);

	//stMenu->addButton();
	//this->menus[DIFFMENUS::START] = stMenu;
}
