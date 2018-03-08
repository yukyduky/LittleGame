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
	Locator::getD2D()->saveScreen();
	RewardMenuState::getInstance()->provide(this->spellPackage);
	StateManager::changeState(GamePlayState::getInstance());
	StateManager::pushState(RewardMenuState::getInstance());
}

void RestartState::provide(std::vector<Spell*> spellPackage)
{
	this->spellPackage.clear();

	for (auto &i : spellPackage)
	{
		this->spellPackage.push_back(i);
	}
}