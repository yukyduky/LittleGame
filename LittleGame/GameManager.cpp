#include "GameManager.h"
#include "D3D.h"
#include "StateManager.h"
#include "State.h"
#include "Locator.h"
#include "GameTime.h"
#include "RandomGeneration.h"
#include "GamePlayState.h"
#include "MenuPauseState.h"
#include "HomeMenuState.h"
#include "Renderer.h"
#include "AudioManager.h"
#include "GlobalEvents.h"
#include "StatsHeader.h"

void GameManager::init(HINSTANCE hInstance, int nCmdShow)
{
	this->isRunning = true;

	this->renderer.init();

	// Creation of gameTime;
	this->gameTime = new GameTime;
	this->randomGenerator = new RandomGeneration;
	this->globalEvents = new GlobalEvents;
	this->stats = new StatsHeader;
	// Provide the gametime object to the service locator
	Locator::provide(this->gameTime);
	Locator::provide(this->randomGenerator);
	Locator::provide(this->globalEvents);
	Locator::provide(this->stats);

	//// Create the AudioManager
	this->audio = new AudioManager;
	// Provide the audioManager object to the service locator
	Locator::provide(this->audio);
	// Play music (MVP, this will/should be changed later on)
	this->audio->play(MUSIC::MENU_MUSIC);

	// Start the game timer

	// Set the first state of the game
	//StateManager::pushState(GamePlayState::getInstance());
	StateManager::pushState(HomeMenuState::getInstance());
}

void GameManager::cleanUp()
{
	StateManager::cleanUp();
	if (this->gameTime != nullptr) {
		delete this->gameTime;
		this->gameTime = nullptr;
	}
	if (this->audio != nullptr) {
		this->audio->cleanUp();
		delete this->audio;
		this->audio = nullptr;
	}
	if (this->randomGenerator != nullptr) {
		delete this->randomGenerator;
		this->randomGenerator = nullptr;
	}
	this->renderer.cleanUp();
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
	this->renderer.firstPass();
	StateManager::render(this);
}

void GameManager::display(State* state)
{
	this->renderer.secondPass();
}

void GameManager::setupSecondRenderPass()
{
	this->renderer.secondPassSetup();
}

bool GameManager::getIsRunning()
{
	return this->isRunning;
}

void GameManager::quit()
{
	this->isRunning = false;
}
