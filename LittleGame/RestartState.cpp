#include "RestartState.h"
#include "GameManager.h"
#include "StateManager.h"
#include "MenuRewardState.h"
#include "IncludeSpells.h"

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
	Locator::getD2D()->saveScreen();
	StateManager::changeState(GamePlayState::getInstance());
	StateManager::pushState(MenuRewardState::getInstance());
}