#include "RestartState.h"
#include "GameManager.h"
#include "StateManager.h"
#include "RewardMenuState.h"

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
	StateManager::changeState(GamePlayState::getInstance());
	StateManager::pushState(RewardMenuState::getInstance());
}
