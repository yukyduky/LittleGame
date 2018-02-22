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

void GamePlayState::updateFloorPattern() {
	double dt = Locator::getGameTime()->GetTime() - this->gTimeLastFrame;
	this->gTimeLastFrame = Locator::getGameTime()->GetTime();
	this->totalLevelTime += dt;
	this->counter += dt;
	Index index(0, 0);
	XMFLOAT3 currVel(0, 0, 0);
	XMFLOAT4 fallColor(1.0f, 0.0f, 0.0f, 1.0f);
	XMFLOAT4 baseColor(0.0f, 0.0f, 0.0f, 0.0f);
	XMFLOAT4 finalColor(0.0f, 0.0f, 0.0f, 1.0f);

	switch (this->floorState)	
	{
	case FLOORSTATE::STATE::ACTIVE:
		if (this->counter > this->stateTime) {
			if (totalLevelTime < this->mediumTime) {
				this->currData = easyPatterns[Locator::getRandomGenerator()->GenerateInt(0, this->easyPatterns.size() - 1)];
			}
			else if (totalLevelTime < this->hardTime) {
				this->currData = mediumPatterns[Locator::getRandomGenerator()->GenerateInt(0, this->mediumPatterns.size() - 1)];
			}
			else {
				this->currData = hardPatterns[Locator::getRandomGenerator()->GenerateInt(0, this->hardPatterns.size() - 1)];
			}
			for (int i = 0; i < this->currData.pattern.size(); i++) {
				index.x = this->currData.pattern[i].x;
				index.y = this->currData.pattern[i].y;
				this->grid[index.x][index.y].ptr->setState(OBJECTSTATE::TYPE::TFALLING);
				//this->lm.changeTileStateFromIndex(XMFLOAT2(index.x, index.y), OBJECTSTATE::TYPE::TFALLING, this->grid, this->staticObjects, this->noCollisionDynamicObjects);
			}
			this->floorState = FLOORSTATE::STATE::TFALLING;
			this->counter = 0.0f;
		}
		break;
		
	case FLOORSTATE::STATE::TFALLING:
		if (this->counter < this->stateTime) {
			for (int i = 0; i < this->currData.pattern.size(); i++) {
				index.x = currData.pattern[i].x;
				index.y = currData.pattern[i].y;
				baseColor = this->grid[index.x][index.y].baseColor;

				baseColor.x = baseColor.x - (baseColor.x / (this->stateTime - 0.5f)) * counter;
				baseColor.y = baseColor.y - (baseColor.y / (this->stateTime - 0.5f)) * counter;
				baseColor.z = baseColor.z - (baseColor.z / (this->stateTime - 0.5f)) * counter;
				fallColor.x = (fallColor.x / (this->stateTime - 0.5f)) * counter;
				fallColor.y = (fallColor.y / (this->stateTime - 0.5f)) * counter;
				fallColor.z = (fallColor.z / (this->stateTime - 0.5f)) * counter;
				
				finalColor.x = baseColor.x + fallColor.x;
				finalColor.y = baseColor.y + fallColor.y;
				finalColor.z = baseColor.z + fallColor.z;
				finalColor.w = baseColor.w;

				this->grid[index.x][index.y].color = finalColor;
			}
		}
		else {
			this->floorState = FLOORSTATE::STATE::FALLING;
			this->counter = 0.0f;
		}
		break;

	case FLOORSTATE::STATE::FALLING:
		if (this->counter < stateTime) {
			for (int i = 0; i < this->currData.pattern.size(); i++) {
				index.x = this->currData.pattern[i].x;
				index.y = this->currData.pattern[i].y;
				this->grid[index.x][index.y].posY += GRAVITY * this->counter * 4.0f;
			}
		}
		else {
			for (int i = 0; i < this->currData.pattern.size(); i++) {
				index.x = this->currData.pattern[i].x;
				index.y = this->currData.pattern[i].y;
				this->grid[index.x][index.y].posY = 10000.0f;
			}
			this->floorState = FLOORSTATE::STATE::DEACTIVATED;
			this->counter = 0.0f;
		}
		break;

	case FLOORSTATE::STATE::DEACTIVATED:
		if (this->counter > this->stateTime) {
			for (int i = 0; i < this->currData.pattern.size(); i++) {
				index.x = this->currData.pattern[i].x;
				index.y = this->currData.pattern[i].y;
				this->grid[index.x][index.y].posY = -50.0f;
			}
			this->floorState = FLOORSTATE::STATE::RECOVERING;
			this->counter = 0.0f;
		}
		break;

	case FLOORSTATE::STATE::RECOVERING:
		if (this->counter < this->stateTime) {
			for (int i = 0; i < this->currData.pattern.size(); i++) {
				index.x = this->currData.pattern[i].x;
				index.y = this->currData.pattern[i].y;
				this->grid[index.x][index.y].posY -= GRAVITY * this->counter * 4.0f;
			}
		}
		else {
			for (int i = 0; i < this->currData.pattern.size(); i++) {
				index.x = this->currData.pattern[i].x;
				index.y = this->currData.pattern[i].y;
				this->grid[index.x][index.y].posY = -0.5f;
			}
			this->floorState = FLOORSTATE::STATE::ACTIVE;
			this->counter = 0.0f;
		}
		break;

	default:
		break;
	}
	
	

	/*
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
	*/

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
	this->lm.selectArena();
	this->quadTree.initializeQuadTree(0, ARENADATA::GETarenaWidth(), ARENADATA::GETarenaHeight(), 0, 0);
	this->camera.init(ARENADATA::GETarenaWidth(), ARENADATA::GETarenaHeight());
	this->rio.initialize(this->camera, this->pointLights);
	this->initPlayer();
	this->ID = lm.initArena(this->newID(), this->staticPhysicsCount, *this, this->fallData, this->grid, this->staticObjects, this->noCollisionDynamicObjects, this->dynamicObjects, this->graphics, this->easyPatterns, this->mediumPatterns, this->hardPatterns);
	int i = 0;
	for (std::list<GameObject*>::iterator it = this->staticObjects.begin(); it != this->staticObjects.end() && i < this->staticPhysicsCount; it++) {
		this->quadTree.insertStaticObject(*it);
		i++;
	}

	std::vector<ActorObject*> allPlayers;
	allPlayers.push_back(player1);
	this->enemyManager.initialize(sGamePlayState, allPlayers);

	this->pointLights.reserve(MAX_NUM_POINTLIGHTS);
	this->pointLights.push_back(Light(XMFLOAT3(ARENADATA::GETarenaWidth() / 2.0f, ARENADATA::GETsquareSize() * 10, ARENADATA::GETarenaHeight() / 2.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.3f, 0.3f, 0.3f), XMFLOAT3(0.8f, 0.0001f, 0.00001f), 50.0f));
	this->pointLights.push_back(Light(XMFLOAT3(ARENADATA::GETarenaWidth() - 200.0f, ARENADATA::GETsquareSize() * 3, ARENADATA::GETarenaHeight() - 200.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), 50.0f));
	this->pointLights.push_back(Light(XMFLOAT3(200.0f, 150.0f, 200.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), 50.0f));

	// To be changed when Ollie has done the rework on camera
	XMFLOAT3 tempcDir;
	XMStoreFloat3(&tempcDir, this->camera.GETfacingDir());
	this->mousePicker = new MouseInput(this->camera.GETcameraPosFloat3(), tempcDir);
	this->enemyManager.startLevel1();

	this->mediumTime = 120.0;
	this->hardTime = 240.0;
	this->totalLevelTime = 0.0;
	this->timeBetweenPatterns = 20.0;
	this->stateTime = 5.0;
	this->recoveryMode = false;
	this->gTimeLastFrame = Locator::getGameTime()->GetTime();
	
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
	for (auto &iterator : this->dynamicObjects) {
		iterator->cleanUp();
		delete iterator;
	}
	for (auto &iterator : this->noCollisionDynamicObjects) {
		iterator->cleanUp();
		delete iterator;
	}
	for (int i = 0; i < this->playerInput.size(); i++) {
		this->playerInput[i] = nullptr;
	}
	this->quadTree.cleanup();
	this->staticObjects.clear();
	this->dynamicObjects.clear();
	this->noCollisionDynamicObjects.clear();
	this->graphics.clear();

	//Clear FloorFallPattern arrays.
	this->easyPatterns.clear();
	this->mediumPatterns.clear();
	this->hardPatterns.clear();

	InputComponent::cleanup();
}

void GamePlayState::pause()
{

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
	this->updateFloorPattern();

	int ID;
	//Update the noCollisionDynamicObjects if the object isn't dead. Else remove the object.
	for (std::list<GameObject*>::iterator it = this->noCollisionDynamicObjects.begin(); it != this->noCollisionDynamicObjects.end(); it++) {
		(*it)->update();
	}

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

	//Check if the player is on a active floor tile or if he fell of the map.
	if (this->player1->getState() != OBJECTSTATE::TYPE::FALLING) {
		if (this->lm.checkTileStateFromPos(this->player1->GETPosition(), this->grid) == OBJECTSTATE::TYPE::FALLING || this->lm.checkTileStateFromPos(this->player1->GETPosition(), this->grid) == OBJECTSTATE::TYPE::INVISIBLE) {
			this->player1->setState(OBJECTSTATE::TYPE::FALLING);
		}
	}

//	this->enemyManager.update();
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
	XMFLOAT3 playerPos((float)(ARENADATA::GETarenaWidth() / 2), playerScales.y, (float)(ARENADATA::GETarenaHeight() / 2));
	XMFLOAT3 playerVelocity(300.0f, -300.0f, 300.0f);
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
		Crosshair* crossHair;
		BlockComponent* cross;

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


Projectile* GamePlayState::initProjectile(XMFLOAT3 pos, XMFLOAT3 dir, ProjProp props)
{
	Projectile* proj;
	int nextID = this->newID();

	// Declare Components
	BlockComponent* block;
	PhysicsComponent* phyComp;

	XMFLOAT3 position = {pos.x /*+ dir.x * props.size*/, pos.y /*+ dir.y * props.size */, pos.z /*+ dir.z * props.size*/};
	proj = new Projectile(nextID, props.speed, props.spinn, position, dir, OBJECTTYPE::PROJECTILE);

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