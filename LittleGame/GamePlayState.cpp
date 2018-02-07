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

#include "DamageSpell.h"
#include "MobilitySpell.h"

using namespace DirectX::SimpleMath;

GamePlayState GamePlayState::sGamePlayState;

//void GamePlayState::updatePhysicsComponents()
//{
//	for (auto&& i : physicsListDynamic) {
//		if (i->GETEntityPointer()->getState() != OBJECTSTATE::DEAD) {
//			i->updateBoundingArea(i->GETEntityPointer()->GETPosition());
//		}
//	}
//}

void GamePlayState::checkCollisions() {
	//--------//
	// LOOP 1 //   : Looping through each DYNAMIC physicsComponent
	//--------//
	for (auto&& i : this->dynamicObjects) {
		// Comparing to all other DYNAMIC & STATIC physComponents.
		// NOTE: Skipping if object state = DEAD.
		int iID = i->getID();
		
		if (i->getState() != OBJECTSTATE::TYPE::DEAD) {
			//----------//
			// LOOP 2.1 //   :  DYNAMIC <--> DYNAMIC Collision
			//----------//
			for (auto&& k : this->dynamicObjects) {
				int kID = k->getID();
				if (iID != kID)
				{
					if (k->getState() != OBJECTSTATE::TYPE::DEAD) {

						if (i->GETphysicsComponent()->checkCollision(k->GETphysicsComponent()->GETBoundingSphere())) {
							// Call COLLISION-CLASS function
							this->collisionHandler.executeCollision(
								i,
								k,
								&i->GETphysicsComponent()->GETBoundingSphere(),
								&k->GETphysicsComponent()->GETBoundingSphere()
							);
						}
					}
				}
				
			}
			//----------//
			// LOOP 2.2 //   :  DYNAMIC <--> STATIC Collision
			//----------//
			for (int k = 0; k < this->staticPhysicsCount; k++) {
				if (this->staticObjects[k]->getState() != OBJECTSTATE::TYPE::DEAD) {

					if (i->GETphysicsComponent()->checkCollision(this->staticObjects[k]->GETphysicsComponent()->GETBoundingSphere())) {
						// Call COLLISION-CLASS function
						this->collisionHandler.executeCollision(
							i,
							this->staticObjects[k],
							&i->GETphysicsComponent()->GETBoundingSphere(),
							&this->staticObjects[k]->GETphysicsComponent()->GETBoundingSphere()
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
	this->ID = lm.initArena(this->newID(), this->staticPhysicsCount, ARENAWIDTH, ARENAHEIGHT, this->grid, this->staticObjects, this->graphics);

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
	for (auto &iterator : this->staticObjects) {
		iterator->cleanUp();
		delete iterator;
	}
	for (auto &iterator : this->dynamicObjects) {
		iterator->cleanUp();
		delete iterator;
	}
/*
	for (auto &iterator : this->projectiles) {
		//iterator->cleanUp();
		//delete iterator;
	}
*/
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
	int ID;
	for (int i = 0; i < this->dynamicObjects.size(); i++) {
		if (dynamicObjects[i]->getState() != OBJECTSTATE::TYPE::DEAD) {
			this->dynamicObjects[i]->update();
		}
		else {
		/*
			ID = this->dynamicObjects[i]->getID();
			for (int j = 0; j < this->graphics.size(); j++) {
				if (this->graphics[j]->getID() == ID) {
					this->graphics.erase(this->graphics.begin() + j - 1, this->graphics.begin() + j - 1);
				}
			}
			this->dynamicObjects[i]->cleanUp();
			this->dynamicObjects.erase(this->dynamicObjects.begin() + i, this->dynamicObjects.begin() + i);
		*/
		}
	}
	this->checkCollisions();
}

void GamePlayState::render(GameManager * gm) {
	rio.render(this->graphics);
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
	int nextID = this->newID();
	
	//Create the new ActorObject
	XMFLOAT3 playerScales(10.0f, 40.0f, 10.0f);
	XMFLOAT3 playerPos((float)(ARENAWIDTH / 2), playerScales.y, (float)(ARENAHEIGHT / 2));
	actor = new ActorObject(nextID, playerPos, this);
	/// PHYSICS COMPONENT:
	// 1: We new a PhysicsComponent, using the actor-POINTER'S address as a parameter.
	physics = new PhysicsComponent(*actor, 20.0f);

	XMFLOAT3 playerVelocity(300.0f, 300.0f, 300.0f);
	actor->setVelocity(playerVelocity);
	actor->setSpeed(1);

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
	//actor->SETinputComponent(input);

	this->playerInput[0] = input;
	this->graphics.push_back(block);

	//Add the spell to the player, numbers are used to in different places
	// Slots:
	// 0 (Autoattack):
	actor->addSpell(new DamageSpell(actor, NAME::AUTOATTACK));
	// 1:
	actor->addSpell(new DamageSpell(actor, NAME::EXPLOSION));
	// 2: 
	actor->addSpell(new DamageSpell(actor, NAME::BOMB));
	// 3:
	actor->addSpell(new MobilitySpell(actor, NAME::DASH));
	// 4:
	actor->addSpell(new MobilitySpell(actor, NAME::SPEEDBUFF));

	actor->selectAbility1();

	player1 = actor;

	/*
	this->go = new GameObject(0);
	this->actorObject = new ActorObject(0);		// HAS TO BE 0 FOR THE ACTOR OBJECT!!!! ControllerComponent::generateCommands() --> XInputGetState()
	
	//this->playerInput[0] = new ControllerComponent(*this->actorObject, 0);
	this->blocks.push_back(new BlockComponent(*this->go, 0.0f, 1.0f, 0.0f, 1.0f));
	*/
	this->dynamicObjects.push_back(actor);
}

Projectile* GamePlayState::initProjectile(XMFLOAT3 pos, XMFLOAT3 dir, ProjProp props)
{
	Projectile* proj;
	int nextID = this->newID();

	// Declare Components
	BlockComponent* block;
	PhysicsComponent* phyComp;

	XMFLOAT3 position = {pos.x + dir.x * props.size, pos.y + dir.y * props.size , pos.z + dir.z * props.size};
	proj = new Projectile(nextID, position);
	proj->setDirection(dir);
	proj->setType(OBJECTTYPE::PROJECTILE);

	//input for blockComp
	XMFLOAT3 scale(props.size, props.size, props.size);
	//XMFLOAT3 position = pos;
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
	//abiliComp = new FireballComponent(*proj, 1);
	//proj->addComponent(abiliComp);
	proj->setSpeed(props.speed);
	proj->setVelocity(dir * props.speed);

	//Template for Physics
	phyComp = new PhysicsComponent(/*pos, */*proj, 20.0f);

	
	//Add proj to objectArrays
	this->dynamicObjects.push_back(proj);
//	this->projectiles.push_back(proj);

	return proj;
}
