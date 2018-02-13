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
#include "GameObject.h"

#include "IncludeSpells.h"


//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//                                 GAMEPLAY STATE          /
///////////////////////////////////////////////////////////
//////////////////////////////
///////////////
///////
//

/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                             |
  |           PRIVATE           |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-*/

using namespace DirectX::SimpleMath;

GamePlayState GamePlayState::sGamePlayState;

void GamePlayState::checkCollisions() {
	//--------//
	// LOOP 1 //   :	Looping through each DYNAMIC physicsComponent
	//--------//
	for (auto&& i : this->dynamicObjects) {
		// Comparing to all other DYNAMIC & STATIC physComponents.
		// NOTE: Skipping if object state = DEAD.
		int iID = i->getID();
		
		if (i->getState() != OBJECTSTATE::TYPE::DEAD) {
			//----------//
			// LOOP 2.1 //   :	DYNAMIC <--> DYNAMIC Collision
			//----------//
			for (auto&& k : this->dynamicObjects) {
				int kID = k->getID();
				if (iID != kID)
				{
					if (k->getState() != OBJECTSTATE::TYPE::DEAD) {

						// Dynamic Object must be within the same part of the quad tree
						// AND
						// Collision between the objects must return true.
						if (
							this->quadTree.checkDynamicObject(i, k) &&
							i->GETphysicsComponent()->checkCollision(k->GETphysicsComponent()->GETBoundingSphere())
							) {
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
			// LOOP 2.2 //   :	DYNAMIC <--> STATIC Collision
			//----------//
			for (auto && k : this->quadTree.retrieveStaticList(i)) {
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
	}
}

//_________________________________________//
//                                         //
//             END OF PRIVATE              //
//_________________________________________//
/////////////////////////////////////////////





/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                             |
  |           PUBLIC            |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-*/

void GamePlayState::init() {
	this->quadTree.initializeQuadTree(0, ARENAWIDTH, ARENAHEIGHT, 0, 0);
	this->camera.init(ARENAWIDTH, ARENAHEIGHT);
	this->rio.initialize(this->camera, this->pointLights);
	this->initPlayer();
	this->ID = lm.initArena(this->newID(), this->staticPhysicsCount, ARENAWIDTH, ARENAHEIGHT, *this, this->fallData, this->grid, this->staticObjects, this->dynamicObjects, this->graphics);
	for (int i = 0; i < this->staticPhysicsCount; i++) {
		this->quadTree.insertStaticObject(this->staticObjects[i]);
	}
	

	std::vector<ActorObject*> allPlayers;
	allPlayers.push_back(player1);
	this->enemyManager.initialize(sGamePlayState, allPlayers);

	this->pointLights.reserve(MAX_NUM_POINTLIGHTS);
	this->pointLights.push_back(Light(XMFLOAT3(ARENAWIDTH / 2.0f, ARENASQUARESIZE * 10, ARENAHEIGHT / 2.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.3f, 0.3f, 0.3f), XMFLOAT3(0.8f, 0.0001f, 0.00001f), 50.0f));
	this->pointLights.push_back(Light(XMFLOAT3(ARENAWIDTH - 200.0f, ARENASQUARESIZE * 3, ARENAHEIGHT - 200.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), 50.0f));
	this->pointLights.push_back(Light(XMFLOAT3(200.0f, 150.0f, 200.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), 50.0f));

	//this->enemyManager.startLevel1();

	this->mousePicker = new MouseInput(this->camera.GETcameraPosFloat3(), this->camera.GETfacingDir());
	this->enemyManager.startLevel1();
}

void GamePlayState::cleanUp()
{
	// Direct internal objects
	 this->rio.cleanUp();
	// this->camera.cleanUp();
	this->enemyManager.cleanUp();

	// GameObjects which will on their own clean up all of their connected components
	for (auto &iterator : this->staticObjects) {
		iterator->cleanUp();
		delete iterator;
	}
	for (auto &iterator : this->dynamicObjects) {
		iterator->cleanUp();
		delete iterator;
	}
	for (auto &iterator : this->noCollisionDynamicObjects) {
		iterator->cleanUp();
		delete iterator;
	}
	this->quadTree.cleanup();
	this->staticObjects.clear();
	this->dynamicObjects.clear();
	this->noCollisionDynamicObjects.clear();
	this->graphics.clear();
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
	this->counter += Locator::getGameTime()->getDeltaTime();
	Index index;
	//Make the next floor tile fall if the time is right.	
	if (this->counter > this->fallData.time) {
		if (!this->fallData.recoverMode) {
			for (int i = 0; i < this->fallData.popsPerIteration; i++) {
				if (this->fallData.pattern.size() == 0) { //Will be replaced by a check if all enemies are dead.
					this->fallData.recoverMode = true;
				}
				else {
					index.x = this->fallData.pattern[0].x;
					index.y = this->fallData.pattern[0].y;
					this->fallData.recoverPattern.push_back(this->fallData.pattern[0]);
					this->fallData.pattern.erase(this->fallData.pattern.begin());
					this->lm.changeTileStateFromIndex(XMFLOAT2(index.x, index.y), OBJECTSTATE::TYPE::TFALLING, this->grid, this->staticObjects, this->noCollisionDynamicObjects);

				}
			}
			this->counter = 0;
		}
		else {
			//Recover a floor tile if the time is right
			for (int i = 0; i < this->fallData.popsPerIteration; i++) {
				if (this->fallData.recoverPattern.size() != 0) {
					index.x = this->fallData.recoverPattern[0].x;
					index.y = this->fallData.recoverPattern[0].y;
					this->fallData.recoverPattern.erase(this->fallData.recoverPattern.begin());
					this->lm.changeTileStateFromIndex(XMFLOAT2(index.x, index.y), OBJECTSTATE::TYPE::RECOVER, this->grid, this->staticObjects, this->noCollisionDynamicObjects);
				}
			}
			this->counter = 0;
		}
	}
	if (this->player1->getState() != OBJECTSTATE::TYPE::FALLING) {
		if (this->lm.checkTileStateFromPos(this->player1->GETPosition(), this->grid) == OBJECTSTATE::TYPE::FALLING || this->lm.checkTileStateFromPos(this->player1->GETPosition(), this->grid) == OBJECTSTATE::TYPE::INVISIBLE) {
			this->player1->setState(OBJECTSTATE::TYPE::FALLING);
		}
	}
	

	int ID;
	//Update the noCollisionDynamicObjects if the object isn't dead. Else remove the object.
	for (int i = 0; i < this->noCollisionDynamicObjects.size(); i++) {
		if (this->noCollisionDynamicObjects[i]->getState() != OBJECTSTATE::TYPE::DEAD) {
			noCollisionDynamicObjects[i]->update();
		}
		else {
			ID = this->noCollisionDynamicObjects[i]->getID();
			for (int j = 0; j < this->graphics.size(); j++) {
				if (this->graphics[j]->getID() == ID) {
					this->graphics.erase(this->graphics.begin() + j);
					break;
				}
			}
			this->noCollisionDynamicObjects[i]->cleanUp();
			delete this->noCollisionDynamicObjects[i];
			this->noCollisionDynamicObjects.erase(this->noCollisionDynamicObjects.begin() + i);
		}
	}
	this->enemyManager.update();

	//Update the dynamic objects if the object isn't dead. Else remove the object.
	for (int i = 0; i < this->dynamicObjects.size(); i++) {
		if (dynamicObjects[i]->getState() != OBJECTSTATE::TYPE::DEAD) {
			this->dynamicObjects[i]->update();
		}
		else {
		
			ID = this->dynamicObjects[i]->getID();
			for (int j = this->staticPhysicsCount; j < this->graphics.size(); j++) {
				if (this->graphics[j]->getID() == ID) {
					this->graphics.erase(this->graphics.begin() + j);
					break;
				}
			}
			this->dynamicObjects[i]->cleanUp();
			delete this->dynamicObjects[i];
			this->dynamicObjects.erase(this->dynamicObjects.begin() + i);
		
		}
	}
	this->checkCollisions();
}

void GamePlayState::render(GameManager * gm) {
	rio.render(this->graphics);
	gm->setupSecondRenderPass();
	rio.injectResourcesIntoSecondPass();
	gm->display(this);
}

GamePlayState* GamePlayState::getInstance() {
	return &sGamePlayState;
}

std::vector<GameObject*>* GamePlayState::getDynamicObjects()
{
	return &this->dynamicObjects;
}

void GamePlayState::addGraphics(GraphicsComponent * graphicsComponent)
{
	this->graphics.push_back(graphicsComponent);
}

void GamePlayState::initPlayer()
{
	ActorObject* actor;
	BlockComponent* block;
	InputComponent* input;
	PhysicsComponent* physics;
	int nextID = this->newID();

	XMFLOAT4 playerColor(50.0f / 255.0f, 205.0f / 255.0f, 50.0f / 255.0f, 0.0f / 255.0f);
	XMFLOAT3 playerRotation(0, 0, 0);
	XMFLOAT3 playerScales(10.0f, 40.0f, 10.0f);
	XMFLOAT3 playerPos((float)(ARENAWIDTH / 2), playerScales.y, (float)(ARENAHEIGHT / 2));
	XMFLOAT3 playerVelocity(300.0f, 0.0f, 300.0f);
	float actorSpeed = 1;

	/// ACTOR OBJECT:
	actor = new ActorObject(nextID, actorSpeed, playerPos, playerVelocity, this, OBJECTTYPE::PLAYER);

	/// PHYSICS COMPONENT:
	physics = new PhysicsComponent(*actor, 20.0f);

	/// BLOCK COMPONENT
	block = new BlockComponent(*this, *actor, playerColor, playerScales, playerRotation);

	/// INPUT COMPONENT:
	//input = new ControllerComponent(*actor, 0);
	//actor->setKeyBoardInput(false);
	input = new KeyboardComponent(*actor);
	actor->setKeyBoardInput(true);

	//Add the spell to the player, numbers are used to in different places
	// Slots:
	// 0 (Autoattack):
	actor->addSpell(new SpAutoAttack(actor));
	// 1:
	actor->addSpell(new SpFire(actor));
	// 2: 
	actor->addSpell(new SpBomb(actor));
	// 3:
	actor->addSpell(new SpDash(actor));
	// 4:
	actor->addSpell(new SpBuff(actor));

	actor->selectAbility1();

	this->playerInput[0] = input;
	this->player1 = actor;

	// We add this component to the Dynamic list because this actor = dynamic.
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
	proj = new Projectile(nextID, props.speed, position, dir, OBJECTTYPE::PROJECTILE);

	//input for blockComp
	XMFLOAT3 scale(props.size, props.size, props.size);
	//XMFLOAT3 position = pos;
	XMFLOAT4 tempColor(props.color.x, props.color.y, props.color.z, 0.0f);
	XMFLOAT3 rotation(0, 0, 0);
	block = new BlockComponent(*this, *proj, tempColor, scale, rotation);

	//Template for Physics
	phyComp = new PhysicsComponent(/*pos, */*proj, props.size);

	
	//Add proj to objectArrays
	this->dynamicObjects.push_back(proj);
//	this->projectiles.push_back(proj);

	return proj;
}
//_________________________________________//
//                                         //
//              END OF PUBLIC              //
//_________________________________________//
/////////////////////////////////////////////

//
//\\\\\
//\\\\\\\\\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//                                 GAMEPLAY STATE          \
////////////////////////////////////////////////////////////