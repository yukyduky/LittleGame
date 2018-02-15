#include "RestartState.h"
#include "GameManager.h"
#include "StateManager.h"
#include "GamePlayState.h"

RestartState RestartState::sRestartState;
bool RestartState::flag = true;

RestartState * RestartState::getInstance()
{
	return &sRestartState;
}

void RestartState::init()
{
	this->flag = true;
}
void RestartState::cleanUp()
{

}
void RestartState::pause()
{

}
void RestartState::resume()
{

}
void RestartState::handleEvents(GameManager* gm)
{

}
void RestartState::update(GameManager* gm)
{

}
void RestartState::render(GameManager* gm)
{
	int size = StateManager::GETallStates().size();
	// -2 because GamePlayState is 1 step behind RestartState + an array starts at 0.
	StateManager::GETallStates().at(size - 2)->cleanUp();
	StateManager::GETallStates().at(size - 2)->init();

	StateManager::popState();
}