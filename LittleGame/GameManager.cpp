#include "GameManager.h"
#include "StateManager.h"
#include "State.h"
#include "Locator.h"
#include "GameTime.h"
#include "GamePlayState.h"

void GameManager::init(HINSTANCE hInstance, int nCmdShow)
{
	this->isRunning = true;

	window.InitializeWindow(hInstance, nCmdShow, 1920, 1080, true);

	// Creation of gameTime;
	this->gameTime = new GameTime;
	// Provide the game time object to the service locator
	Locator::provide(this->gameTime);
	// Start the game timer
	Locator::getGameTime()->StartTimer();

	// Set the first state of the game
	StateManager::changeState(GamePlayState::getInstance());
}

void GameManager::cleanup()
{
	delete this->gameTime;
}

void GameManager::changeState(State* state)
{
	StateManager::changeState(state);
}

void GameManager::handleEvents()
{
	StateManager::handleEvents(this);
}

bool GameManager::pollEvent(MSG &msg)
{
	return PeekMessage(&msg, nullptr, 0, 0, PM_REMOVE);
}

void GameManager::update()
{
	StateManager::update(this);
}

void GameManager::render()
{
	/*Color bgColor(255, 0, 255, 1.0f);
	// Clear the backbuffer
	gDevCon->ClearRenderTargetView(gFinalRTV, bgColor);*/

	StateManager::render(this);
}

void GameManager::display(State* state)
{
	/*// Present the backbuffer to the screen
	gSwapChain->Present(0, 0);*/
}

bool GameManager::getIsRunning()
{
	return this->isRunning;
}

void GameManager::quit()
{
	this->isRunning = false;
}
