#include "GamePlayState.h"
#include "GameManager.h"
#include "Locator.h"
#include "BlockComponent.h"
#include "KeyboardComponent.h"
#include "ControllerComponent.h"


#include "ActorObject.h"

GamePlayState GamePlayState::sGamePlayState;



void GamePlayState::init() {
	this->rio.initialize(this->camera);

	this->go = new GameObject(0);
	this->actorObject = new ActorObject(0);		// HAS TO BE 0 FOR THE ACTOR OBJECT!!!! ControllerComponent::generateCommands() --> XInputGetState()
	//this->playerInput[0] = new KeyboardComponent(*this->actorObject);
	this->playerInput[0] = new ControllerComponent(*this->actorObject, 0);


	this->blocks.push_back(new BlockComponent(*this->go, 0.0f, 1.0f, 0.0f, 1.0f));

	for (auto &i : this->blocks) {
		this->rio.addGraphics(i);
	}
}


void GamePlayState::cleanup()
{

}

void GamePlayState::pause() {

}

void GamePlayState::resume()
{
	
}

void GamePlayState::handleEvents(GameManager * gm) {
	MSG msg;

	while (gm->pollEvent(msg)) {
		// Exit the application when 'X' is pressed
		if (msg.message == WM_QUIT) {
			gm->quit();
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}


void GamePlayState::update(GameManager * gm)
{
	for (auto &iterator : playerInput) {
		iterator->generateCommands();
		iterator->execute();
	}
}

void GamePlayState::render(GameManager * gm) {
	this->rio.render();
	gm->display(this);
}

GamePlayState* GamePlayState::getInstance() {
	return &sGamePlayState;
}
