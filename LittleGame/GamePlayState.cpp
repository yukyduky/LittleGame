#include "GamePlayState.h"
#include "GameManager.h"
#include "Locator.h"
#include "BlockComponent.h"
#include "KeyboardComponent.h"
#include "ControllerComponent.h"

GamePlayState GamePlayState::sGamePlayState;


void GamePlayState::init()
{
	this->go = new GameObject(0);

	for (auto &iterator : this->playerInput) {
		iterator = new KeyboardComponent(*this->go);
	}

	this->blocks.push_back(new BlockComponent(*this->go, 0.0f, 1.0f, 0.0f, 1.0f));

	for (auto &i : this->blocks) {
		this->rio.addGraphics(i);
	}
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
}

void GamePlayState::update(GameManager * gm)
{
	for (auto &iterator : playerInput) {
		iterator->generateCommands();
		iterator->execute();
	}
}

void GamePlayState::render(GameManager * gm)
{
	this->rio.render();
	gm->display(this);
}

GamePlayState* GamePlayState::getInstance()
{
	return &sGamePlayState;
}


void GamePlayState::shootProjectile() 
{
	size_t nextID = this->projectiles.size();

	Projectile proj(nextID, DirectX::XMFLOAT3(1, 1, 1), DirectX::XMFLOAT3(0, 0, 0));

	this->projectiles.push_back(&proj);
	BlockComponent block(*projectiles.back(), 1, 0, 1, 1);
	this->projGraph.push_back(&block);


	this->projectiles.back()->addComponent(this->projGraph.back());
}