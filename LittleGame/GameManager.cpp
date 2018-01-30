#include "GameManager.h"
#include "D3D.h"
#include "StateManager.h"
#include "State.h"
#include "Locator.h"
#include "GameTime.h"
#include "InputHandler.h"
#include "GamePlayState.h"

void GameManager::init(HINSTANCE hInstance, int nCmdShow)
{
	this->isRunning = true;
	
	// Creation of gameTime;
	this->gameTime = new GameTime;
	// Provide the gametime object to the service locator
	Locator::provide(this->gameTime);
	// Creation of inputHandler;
	this->inputHandler = new InputHandler;
	// Provide the inputHandler object to the service locator
	Locator::provide(this->inputHandler);

	// Start the game timer
	Locator::getGameTime()->StartTimer();

	// Set the first state of the game
	StateManager::changeState(GamePlayState::getInstance());
}

void GameManager::cleanup()
{
	delete this->gameTime;
	delete this->inputHandler;
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
	StateManager::cleanup();
	D3D::Release();
}
