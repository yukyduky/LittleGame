#include "GamePlayState.h"
#include "GameManager.h"
#include "InputHandler.h"

GamePlayState GamePlayState::sGamePlayState;

GamePlayState::GamePlayState()
{
}

void GamePlayState::init()
{
	InputHandler input;
}

void GamePlayState::cleanup()
{
}

void GamePlayState::pause()
{
}

void GamePlayState::resume()
{
}

void GamePlayState::handleEvents(GameManager * re)
{
	MSG msg;

	while (re->pollEvent(msg)) {
		// Exit the application when 'X' is pressed
		if (msg.message == WM_QUIT) {
			re->quit();
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}

void GamePlayState::update(GameManager * re)
{
	for (auto &c : this->commandQueue) {
		c->execute();
	}
	this->commandQueue.clear();
}

void GamePlayState::render(GameManager * re)
{
	re->display(this);
}

GamePlayState* GamePlayState::getInstance()
{
	return &sGamePlayState;
}
