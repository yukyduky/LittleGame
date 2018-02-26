#include "MenuState.h"
#include "GameManager.h"
#include "Locator.h"
#include "StateManager.h"
#include <SimpleMath.h>
#include <DirectXMath.h>


using namespace DirectX::SimpleMath;

void MenuState::init() {
	this->objD2D.Initialize();

	//this->displayMenu(MENUS::START);
}

void MenuState::cleanUp()
{
	this->currMenu->cleanUp();

	this->menuObjects.clear();
	this->objD2D.~D2D();
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
		if (msg.message == WM_QUIT) {
			gm->quit();
		}
		else if (msg.message == WM_KEYUP)
		{
			switch (msg.wParam)
			{
			case VK_UP:
			case 0x57:
				this->currMenu->goUp();
				break;
			case VK_DOWN:
			case 0x53:
				this->currMenu->goDown();
				break;
			case VK_RETURN:
			case VK_SPACE:
				this->currMenu->pressButton();
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
	if (this->quit)
	{
		gm->quit();
	}
}

void MenuState::render(GameManager * gm) {
	this->objD2D.OnRender(this->menuObjects);
}

void MenuState::displayMenu(Menu* menu)
{
	this->menuObjects.clear();
	if (this->currMenu)
	{
		this->currMenu->cleanUp();
	}

	this->currMenu = menu;
	for (auto &i : this->currMenu->getObjects())
	{
		this->menuObjects.push_back(i);
	}
}

void MenuState::startGame()
{
	StateManager::popState();
}
