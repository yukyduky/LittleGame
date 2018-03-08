#include "RestartState.h"
#include "GameManager.h"
#include "StateManager.h"
#include "RewardMenuState.h"
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
	RewardMenuState::getInstance()->provide(this->spellPackage);
	StateManager::changeState(GamePlayState::getInstance());
	StateManager::pushState(RewardMenuState::getInstance());
}

void RestartState::provide(std::vector<Spell*> spellPackage)
{
	// First clear to avoid doubling of vectors
	this->vecGlyph.clear();

	// Find out what the current values are and save them.
	for (auto currentSpell : spellPackage) {
		this->vecGlyph.push_back((int)currentSpell->getGlyph());
	}
}