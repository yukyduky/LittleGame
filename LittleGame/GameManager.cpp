#include "GameManager.h"
#include "StateManager.h"
#include "State.h"
#include "Locator.h"
#include "GameTime.h"


void GameManager::init()
{
	this->isRunning = true;

	// Creation of gameTime;
	this->gameTime = new GameTime;
	// Provide the game time object to the service locator
	Locator::provide(this->gameTime);
	// Start the game timer
	Locator::getGameTime()->StartTimer();
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

/*bool GameManager::pollEvent(sf::Event & event)
{
	return this->window.pollEvent(event);
}*/

void GameManager::update()
{
	StateManager::update(this);
}

void GameManager::render()
{
	StateManager::render(this);
}

void GameManager::display(State* state)
{
}

bool GameManager::getIsRunning()
{
	return this->isRunning;
}

void GameManager::quit()
{
	this->isRunning = false;
}
