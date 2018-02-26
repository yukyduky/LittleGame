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
#include <iterator>
#include "Crosshair.h"
#include "StateManager.h"

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
	this->initPlayer();
	this->ID = lm.initArena(this->newID(), this->staticPhysicsCount, ARENAWIDTH, ARENAHEIGHT, *this, this->fallData, this->grid, this->staticObjects, this->dynamicObjects, this->graphics);
	this->quadTree.initializeQuadTree(0, ARENAWIDTH, ARENAHEIGHT, 0, 0);
	this->camera.init(ARENAWIDTH, ARENAHEIGHT);
	this->rio.initialize(this->camera, this->pointLights);
	int i = 0;
	for (std::list<GameObject*>::iterator it = this->staticObjects.begin(); it != this->staticObjects.end() && i < this->staticPhysicsCount; it++) {
		this->quadTree.insertStaticObject(*it);
		i++;
	}
	

	std::vector<ActorObject*> allPlayers;
	allPlayers.push_back(player1);
	this->enemyManager.initialize(sGamePlayState, allPlayers);

	this->pointLights.reserve(MAX_NUM_POINTLIGHTS);
	this->pointLights.push_back(Light(XMFLOAT3(ARENAWIDTH * 0.5, ARENASQUARESIZE * 10, ARENAHEIGHT * 0.5), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.3f, 0.3f, 0.3f), XMFLOAT3(0.8f, 0.0001f, 0.00001f), 50.0f));
	this->pointLights.push_back(Light(XMFLOAT3(ARENAWIDTH - 200.0f, ARENASQUARESIZE * 3, ARENAHEIGHT - 200.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), 50.0f));
	this->pointLights.push_back(Light(XMFLOAT3(200.0f, 150.0f, 200.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), 50.0f));

	// To be changed when Ollie has done the rework on camera
	XMFLOAT3 tempcDir;
	XMStoreFloat3(&tempcDir, this->camera.GETfacingDir());
	this->mousePicker = new MouseInput(this->camera.GETcameraPos(), this->camera.GETfacingDirFloat3());
	this->enemyManager.startLevel1();
}

void GamePlayState::cleanUp()
{
	Locator::getAudioManager()->stopSound();
	// Direct internal objects
	this->rio.cleanUp();
	// this->camera.cleanUp();
	this->enemyManager.cleanUp();

	// GameObjects which will on their own clean up all of their connected components
	for (auto &iterator : this->staticObjects) {
		iterator->cleanUp();
		delete iterator;
	}
	this->staticObjects.clear();

	for (auto &iterator : this->dynamicObjects) {
		iterator->cleanUp();
		delete iterator;
	}
	this->dynamicObjects.clear();

	for (auto &iterator : this->noCollisionDynamicObjects) {
		iterator->cleanUp();
		delete iterator;
	}
	this->noCollisionDynamicObjects.clear();

	for (int i = 0; i < this->playerInput.size(); i++) {
		this->playerInput[i] = nullptr;
	}

	this->quadTree.cleanup();

	//for (auto && iterator2 : this->pointLights) {
	//	delete &iterator2;
	//}

	this->pointLights.clear();
	
	this->graphics.clear();

	InputComponent::cleanup();

	this->staticPhysicsCount = 0;
	this->counter = 0;
	this->ID = 0;
}

void GamePlayState::pause()
{

}

void GamePlayState::resume()
{
}

void GamePlayState::handleEvents(GameManager * gm) {
	MSG msg;
	GLOBALMESSAGES globalmsg;

	while (gm->pollEvent(msg)) {
		// Exit the application when 'X' is pressed
		if (msg.message == WM_QUIT) {
			gm->quit();
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	while (Locator::getGlobalEvents()->pollEvent(globalmsg)) {
		if (globalmsg == GLOBALMESSAGES::PLAYERDIED) {
			StateManager::changeState(RestartState::getInstance());
		}
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
	//Check if the player is on a active floor tile or if he fell of the map.
	/*if (this->player1 != nullptr && this->player1->getState() != OBJECTSTATE::TYPE::FALLING) {
		if (this->lm.checkTileStateFromPos(this->player1->GETPosition(), this->grid) == OBJECTSTATE::TYPE::FALLING || this->lm.checkTileStateFromPos(this->player1->GETPosition(), this->grid) == OBJECTSTATE::TYPE::INVISIBLE) {
			this->player1->setState(OBJECTSTATE::TYPE::FALLING);
		}
	}*/

	int ID;
	//Update the noCollisionDynamicObjects if the object isn't dead. Else remove the object.
	for (std::list<GameObject*>::iterator it = this->noCollisionDynamicObjects.begin(); it != this->noCollisionDynamicObjects.end(); it++) {
		(*it)->update();
	}
	/*
	MIGHT WANT THIS CODE LATER! LET IT BE COMMENTED OUT FOR THE TIME BEING.
	for (int i = 0; i < this->noCollisionDynamicObjects.size(); i++) {
		if (this->noCollisionDynamicObjects[i]->getState() != OBJECTSTATE::TYPE::DEAD) {
			//noCollisionDynamicObjects[i]->update();
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
	*/

	this->enemyManager.update();

	for (std::list<GameObject*>::iterator it = this->dynamicObjects.begin(); it != this->dynamicObjects.end(); it++) {
		if ((*it)->getState() != OBJECTSTATE::TYPE::DEAD) {
			(*it)->update();
		}
		else {
			ID = (*it)->getID();
			int j = this->graphics.size();
			for (std::list<GraphicsComponent*>::reverse_iterator rit = this->graphics.rbegin(); rit != this->graphics.rend() && j > this->staticPhysicsCount; rit++) {
				if ((*rit)->getID() == ID) {
					this->graphics.erase(std::next(rit).base());
					j++;
				}
				j--;
			}
			(*it)->cleanUp();
			delete (*it);
			it = this->dynamicObjects.erase(it);
			it--;
		}
	}
	this->checkCollisions();
}

void GamePlayState::render(GameManager * gm) 
{
	rio.render(this->graphics);
	gm->setupSecondRenderPass();
	rio.injectResourcesIntoSecondPass();
	gm->display(this);
}

GamePlayState* GamePlayState::getInstance() 
{
	return &sGamePlayState;
}

std::list<GameObject*>* GamePlayState::getDynamicObjects()
{
	return &this->dynamicObjects;
}

void GamePlayState::addGraphics(GraphicsComponent * graphicsComponent)
{
	this->graphics.push_back(graphicsComponent);
}

void GamePlayState::initPlayer()
{
	ActorObject* actor = nullptr;
	BlockComponent* block = nullptr;
	InputComponent* input = nullptr;
	PhysicsComponent* physics = nullptr;
	int nextID = this->newID();

	XMFLOAT4 playerColor(0.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f);
	XMFLOAT3 playerRotation(0, 0, 0);
	XMFLOAT3 playerScales(10.0f, 40.0f, 10.0f);
	XMFLOAT3 playerPos(static_cast<float>(ARENAWIDTH * 0.5), playerScales.y, static_cast<float>(ARENAHEIGHT * 0.5));
	float playerVelocity = 300.0f;
	float actorSpeed = 1;

	/// ACTOR OBJECT:
	actor = new ActorObject(nextID, actorSpeed, playerPos, playerVelocity, this, OBJECTTYPE::PLAYER);

	/// PHYSICS COMPONENT:
	physics = new PhysicsComponent(*actor, 20.0f);

	/// BLOCK COMPONENT
	block = new BlockComponent(*this, *actor, playerColor, playerScales, playerRotation);

	/// INPUT COMPONENT:
	//input = new ControllerComponent(*actor, 0);
	input = new KeyboardComponent(*actor);

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

	/// CROSSHAIR	
	Crosshair* crossHair = nullptr;
	BlockComponent* cross = nullptr;

	crossHair = new Crosshair(actor, this->newID());

	cross = new BlockComponent(*this, *crossHair, XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f), XMFLOAT3(10.0f, 5.0f, 5.0f), playerRotation);

	this->noCollisionDynamicObjects.push_back(crossHair);
	/// END OF CROSSHAIR

	this->player1 = actor;
	// We add this component to the Dynamic list because this actor = dynamic.
	this->dynamicObjects.push_back(actor);

	actor = nullptr;
	physics = nullptr;
	block = nullptr;
	input = nullptr;
}


Projectile* GamePlayState::initProjectile(XMFLOAT3 pos, ActorObject* shooter, ProjProp props)
{
	Projectile* proj = nullptr;
	int nextID = this->newID();

	XMFLOAT3 dir = shooter->getDirection();

	// Declare Components
	BlockComponent* block = nullptr;
	PhysicsComponent* phyComp = nullptr;

	XMFLOAT3 position = {pos.x /*+ dir.x * props.size*/, pos.y /*+ dir.y * props.size */, pos.z /*+ dir.z * props.size*/};
	proj = new Projectile(nextID, props.speed, props.range, props.spinn, shooter, position, dir, OBJECTTYPE::PROJECTILE);

	//input for blockComp
	XMFLOAT3 scale(props.size, props.size, props.size);
	//XMFLOAT3 position = pos;
	XMFLOAT4 tempColor(props.color);
	XMFLOAT3 rotation(0, 0, 0);
	block = new BlockComponent(*this, *proj, tempColor, scale, rotation);

	//Template for Physics
	phyComp = new PhysicsComponent(/*pos, */*proj, (props.size + 5));

	
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