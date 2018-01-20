#include "GamePlayState.h"
#include "GameManager.h"
#include "GamePlaySelectCommand.h"
#include "Locator.h"

GamePlayState GamePlayState::sGamePlayState;

void GamePlayState::mapKeys()
{
	Locator::getInputHandler()->mapCommandToKeyboardKey(KEYBOARD::W, Key(this->selectCommand, COMMANDTYPE::TAP));
	Locator::getInputHandler()->mapCommandToControllerKey(CONTROLLER::A, Key(this->selectCommand, COMMANDTYPE::TAP));
	Locator::getInputHandler()->mapCommandToLeftThumbStick(this->selectCommand);
}

void GamePlayState::init()
{
	this->selectCommand = new GamePlaySelectCommand();
	this->mapKeys();
}

void GamePlayState::cleanup()
{
	delete this->selectCommand;
}

void GamePlayState::pause()
{
	Locator::getInputHandler()->resetKeyBindings();
}

void GamePlayState::resume()
{
	this->mapKeys();
}

void GamePlayState::handleEvents(GameManager * gm)
{
	MSG msg;

	while (gm->pollEvent(msg)) {
		// Exit the application when 'X' is pressed
		if (msg.message == WM_QUIT) {
			gm->quit();
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// Update input devices
	Locator::getInputHandler()->update(this->commandQueue);
}

void GamePlayState::update(GameManager * gm)
{
	// Execute any generated commands
	for (auto &i : this->commandQueue) {
		i.command->execute(i.player);
	}
	this->commandQueue.clear();
}

void GamePlayState::render(GameManager * gm)
{
	gm->display(this);
}

void GamePlayState::commandSelect(size_t player)
{
	int test = player;
}

GamePlayState* GamePlayState::getInstance()
{
	return &sGamePlayState;
}
