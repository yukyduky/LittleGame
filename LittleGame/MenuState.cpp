#include "MenuState.h"
#include "GamePlayState.h"
#include "PauseMenuState.h"
#include "HomeMenuState.h"
#include "StatisticsMenuState.h"
#include "GameManager.h"
#include "Locator.h"
#include "StateManager.h"
#include <SimpleMath.h>
#include <DirectXMath.h>


using namespace DirectX::SimpleMath;

void MenuState::init() 
{
}

void MenuState::cleanUp()
{
	this->currMenu->cleanUp();

	for (auto &i : this->menuObjects)
	{
		i->cleanUp();
		delete i;
	}
	this->menuObjects.clear();

	this->ID = 0;
}

void MenuState::pause() {

}

void MenuState::resume()
{
}

void MenuState::handleEvents(GameManager * gm) {
	MSG msg;
	GLOBALMESSAGES globalmsg;

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

	while (Locator::getGlobalEvents()->pollEvent(globalmsg)) {
		if (globalmsg == GLOBALMESSAGES::STARTGAME) {
			StateManager::changeState(GamePlayState::getInstance());
			Locator::getD2D()->closeMenu();
		}
		else if (globalmsg == GLOBALMESSAGES::RESUMEGAME) {
			StateManager::popState();
			Locator::getD2D()->closeMenu();
		}
		else if (globalmsg == GLOBALMESSAGES::RESTARTGAME) {
			Locator::getStatsHeader()->resetStats();

			StateManager::changeState(HomeMenuState::getInstance());
			//StateManager::changeState(GamePlayState::getInstance());
			//StateManager::pushState(PauseMenuState::getInstance());
		}
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
	Locator::getD2D()->OnRender(this->menuObjects);
}

std::wstring MenuState::intToWchar(int input)
{
	std::wstring texten = std::to_wstring(input);
	return texten;
}

void MenuState::displayMenu(Menu* menu)
{
	for (auto &i : this->menuObjects)
	{
		i->cleanUp();
		delete i;
	}
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
	Locator::getGlobalEvents()->generateMessage(GLOBALMESSAGES::STARTGAME);
}

void MenuState::resumeGame()
{
	Locator::getGlobalEvents()->generateMessage(GLOBALMESSAGES::RESUMEGAME);
}

void MenuState::restartGame()
{
	Locator::getGlobalEvents()->generateMessage(GLOBALMESSAGES::RESTARTGAME);
}

void MenuState::statsWindow()
{
	StateManager::popState();
	StateManager::changeState(StatisticsMenuState::getInstance());
}

