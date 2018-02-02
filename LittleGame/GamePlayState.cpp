#include "GamePlayState.h"
#include "GameManager.h"
#include "Locator.h"
#include "RectangleComponent.h"
#include "LineComponent.h"
#include "BlockComponent.h"
#include "KeyboardComponent.h"
#include "ControllerComponent.h"
#include <SimpleMath.h>
#include <DirectXMath.h>
#include "ActorObject.h"
#include "ArenaObject.h"

using namespace DirectX::SimpleMath;

GamePlayState GamePlayState::sGamePlayState;

void GamePlayState::updatePhysicsComponents()
{
	for (auto&& i : physicsListDynamic) {
		if (this->gameObjectsArray.at(i->getID())->getState() != OBJECTSTATE::DEAD) {
			i->updateBoundingArea(this->gameObjectsArray.at(i->getID())->getPosition());
		}
	}
}

void GamePlayState::checkCollisions() {
	// LOOP 1: Looping through each DYNAMIC physicsComponent
	for (auto&& i : this->physicsListDynamic) {
		// Comparing to all other DYNAMIC & STATIC physComponents.
		// NOTE: Skipping if object state = DEAD.
		if (this->gameObjectsArray.at(i->getID())->getState() != OBJECTSTATE::DEAD) {
			// LOOP 2.1: DYNAMIC <--> DYNAMIC Collision
			for (auto&& k : this->physicsListDynamic) {
				if (this->gameObjectsArray.at(k->getID())->getState() != OBJECTSTATE::DEAD) {

					if (i->checkCollision(k->getBoundingSphere())) {
						// Call COLLISION-CLASS function
						this->collisionHandler.executeCollision(
							this->gameObjectsArray.at(i->getID()),
							this->gameObjectsArray.at(k->getID()),
							&i->getBoundingSphere(),
							&k->getBoundingSphere()
						);
					}
				}
			}
			// LOOP 2.2: DYNAMIC <--> STATIC Collision
			for (auto&& k : this->physicsListStatic) {
				if (this->gameObjectsArray.at(k->getID())->getState() != OBJECTSTATE::DEAD) {

					if (i->checkCollision(k->getBoundingSphere())) {
						// Call COLLISION-CLASS function
						this->collisionHandler.executeCollision(
							this->gameObjectsArray.at(i->getID()),
							this->gameObjectsArray.at(k->getID()),
							&i->getBoundingSphere(),
							&k->getBoundingSphere()
						);
					}
				}
			}
		}
	}
}


void GamePlayState::init() {
	this->camera.init(ARENAWIDTH, ARENAHEIGHT);
	this->rio.initialize(this->camera);
	this->initPlayer();
	lm.initArena(ARENAWIDTH, ARENAHEIGHT, this->grid, this->arenaObjects, this->graphics, this->physicsListStatic);

	for (auto &i : this->graphics) {
		this->rio.addGraphics(i);
	}
}

void GamePlayState::cleanUp()
{
	// Direct internal objects
	// this->rio.cleanUp();
	// this->camera.cleanUp();


	// GameObjects which will on their own clean up all of their connected components
	for (auto &iterator : this->arenaObjects) {
		iterator->cleanUp();
		delete iterator;
	}
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

void GamePlayState::initPlayer()
{
	ActorObject* actor;
	BlockComponent* block;
	InputComponent* input;		// THIS IS CORRECT!
	PhysicsComponent* physics;
	int nextID = this->arenaObjects.size();
	
	//Create the new ActorObject
	XMFLOAT3 playerScales(10.0f, 40.0f, 10.0f);
	XMFLOAT3 playerPos((float)(ARENAWIDTH / 2), playerScales.y, (float)(ARENAHEIGHT / 2));
	actor = new ActorObject(nextID, playerPos);
	/// PHYSICS COMPONENT:
	// 1: We new a PhysicsComponent, using the actor's address as a parameter.
	physics = new PhysicsComponent(*actor);
	// 2: We add this component to the Dynamic list because actor = dynamic.
	this->physicsListDynamic.push_back(physics);
	// 3: We add this component to actor's list of components.
	actor->addComponent(this->physicsListDynamic.back());
	XMFLOAT3 playerVelocity(300.0f, 300.0f, 300.0f);
	actor->setVelocity(playerVelocity);

	//Create the playerColor and the new BlockComponent that will represent the players body.
	vColor playerColor(50.0f, 205.0f, 50.0f, 255.0f);
	block = new BlockComponent(*actor, playerColor.r, playerColor.g, playerColor.b, playerColor.a);
	
	//Create the world-, scale-, translation- and rotationmatrix and hand them to the ActorObject.
	XMVECTOR playerTranslation = XMLoadFloat3(&playerPos);
	XMMATRIX worldMatrix;
	XMMATRIX translationM = XMMatrixTranslationFromVector(playerTranslation);
	XMMATRIX rotationM = XMMatrixIdentity();
	XMMATRIX scaleM = XMMatrixScaling(playerScales.x, playerScales.y, playerScales.z);
	worldMatrix = scaleM * rotationM * translationM;

	actor->SETtranslationMatrix(translationM);
	actor->SETscaleMatrix(scaleM);
	actor->SETrotationMatrix(rotationM);
	actor->SETworldMatrix(worldMatrix);
	actor->addComponent(block);

	//Create the new InputComponent (KeyboardComponent or ControllerComponent) and hand it to the ActorObject.
	input = new ControllerComponent(*actor, 0);
	//input = new KeyboardComponent(*actor);
	this->playerInput[0] = input;
	this->arenaObjects.push_back(actor);
	this->graphics.push_back(block);
}