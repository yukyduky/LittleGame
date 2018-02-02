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
		if (this->arenaObjects.at(i->getID())->getState() != OBJECTSTATE::DEAD) {
			i->updateBoundingArea(this->arenaObjects.at(i->getID())->getPosition());
		}
	}
}

void GamePlayState::checkCollisions() {
	// LOOP 1: Looping through each DYNAMIC physicsComponent
	for (auto&& i : this->physicsListDynamic) {
		// Comparing to all other DYNAMIC & STATIC physComponents.
		// NOTE: Skipping if object state = DEAD.
		int iID = i->getID();
		if (this->arenaObjects.at(iID)->getState() != OBJECTSTATE::DEAD) {
			// LOOP 2.1: DYNAMIC <--> DYNAMIC Collision
			for (auto&& k : this->physicsListDynamic) {
				int kID = k->getID();
				if (iID != kID)
				{
					if (this->arenaObjects.at(k->getID())->getState() != OBJECTSTATE::DEAD) {

						if (i->checkCollision(k->getBoundingSphere())) {
							// Call COLLISION-CLASS function
							this->collisionHandler.executeCollision(
								this->arenaObjects.at(i->getID()),
								this->arenaObjects.at(k->getID()),
								&i->getBoundingSphere(),
								&k->getBoundingSphere()
							);
						}
					}
				}
				
			}
			// LOOP 2.2: DYNAMIC <--> STATIC Collision
			for (auto&& k : this->physicsListStatic) {
				if (this->arenaObjects.at(k->getID())->getState() != OBJECTSTATE::DEAD) {

					if (i->checkCollision(k->getBoundingSphere())) {
						// Call COLLISION-CLASS function
						this->collisionHandler.executeCollision(
							this->arenaObjects.at(i->getID()),
							this->arenaObjects.at(k->getID()),
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
	for (auto &iterator : this->projectiles) {
		//iterator->cleanUp();
		//delete iterator;
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
	this->updatePhysicsComponents();
	this->checkCollisions();

	for (auto &iterator : playerInput) {
		iterator->generateCommands();
		iterator->execute();
	}

	for (auto &iterator : projectiles)
	{
		iterator->update();
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
	actor = new ActorObject(nextID, playerPos, this);
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

	actor->setType(OBJECTTYPE::PLAYER);

	//Create the new InputComponent (KeyboardComponent or ControllerComponent) and hand it to the ActorObject.
	//input = new ControllerComponent(*actor, 0);
	input = new KeyboardComponent(*actor);

	this->playerInput[0] = input;
	this->arenaObjects.push_back(actor);
	this->graphics.push_back(block);


	/*
	this->go = new GameObject(0);
	this->actorObject = new ActorObject(0);		// HAS TO BE 0 FOR THE ACTOR OBJECT!!!! ControllerComponent::generateCommands() --> XInputGetState()
	
	//this->playerInput[0] = new ControllerComponent(*this->actorObject, 0);
	this->blocks.push_back(new BlockComponent(*this->go, 0.0f, 1.0f, 0.0f, 1.0f));
	*/
}

void GamePlayState::initProjectile(XMFLOAT3 pos, XMFLOAT3 dir, ProjProp props)
{
	Projectile* proj;
	int nextID = this->newID();

	// Declare Components
	BlockComponent* block;
	PhysicsComponent* phyComp;
	AbilityComponent* abiliComp;

	proj = new Projectile(nextID, pos);
	proj->setDirection(dir);

	//input for blockComp
	XMFLOAT3 scale(props.size, props.size, props.size);
	XMFLOAT3 position = pos;
	block = new BlockComponent(*proj, props.color.x, props.color.y, props.color.z, 255.0f);
	
	// Create matrixes for world-matrix
	XMVECTOR translation = XMLoadFloat3(&position);
	XMMATRIX worldMatrix;
	XMMATRIX translationM = XMMatrixTranslationFromVector(translation);
	XMMATRIX rotationM = XMMatrixIdentity();
	XMMATRIX scaleM = XMMatrixScaling(scale.x, scale.y, scale.z);
	worldMatrix = scaleM * rotationM * translationM;

	// Apply matrixes
	proj->SETtranslationMatrix(translationM);
	proj->SETscaleMatrix(scaleM);
	proj->SETrotationMatrix(rotationM);
	proj->SETworldMatrix(worldMatrix);

	// Bind components
	proj->addComponent(block);

	//Add the block to the objects that will be rendered
	this->graphics.push_back(block);
	this->rio.addGraphics(block);

	//Template of components that are beeing worked on by other users
	abiliComp = new FireballComponent(*proj, 1);
	proj->setVelocity(dir * proj->getSpeed());
	proj->addComponent(abiliComp);

	//Template for Physics
	phyComp = new PhysicsComponent(/*pos, */*proj, props.size);
	this->physicsListDynamic.push_back(phyComp);
	proj->addComponent(phyComp);

	
	//Add proj to objectArrays
	this->arenaObjects.push_back(proj);
	this->projectiles.push_back(proj);

}
