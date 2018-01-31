#include "GameManager.h"
#include "D3D.h"
#include "StateManager.h"
#include "State.h"
#include "Locator.h"
#include "GameTime.h"
#include "GamePlayState.h"
#include "Renderer.h"
#include "AudioManager.h"

void GameManager::init(HINSTANCE hInstance, int nCmdShow)
{
	this->isRunning = true;
	
	this->renderer.init();

	// Creation of gameTime;
	this->gameTime = new GameTime;
	// Provide the gametime object to the service locator
	Locator::provide(this->gameTime);

	// Create the AudioManager
	this->audio = new AudioManager;
	// Provide the audioManager object to the service locator
	Locator::provide(this->audio);
	// Initaiate the audio, loads in all sound and music
	Locator::getAudioManager()->init();

	// Start the game timer
	Locator::getGameTime()->StartTimer();

	// Set the first state of the game
	StateManager::changeState(GamePlayState::getInstance());

	Locator::getAudioManager()->play(MUSIC::ONEPUNCH);


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
	this->renderer.firstPass();
	StateManager::render(this);
}

void GameManager::display(State* state)
{
	this->renderer.secondPass();
}

bool GameManager::getIsRunning()
{
	return this->isRunning;
}

void GameManager::quit()
{
	this->isRunning = false;
	StateManager::cleanup();
}
