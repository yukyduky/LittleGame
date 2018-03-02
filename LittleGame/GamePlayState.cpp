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

void GamePlayState::updateFloorPattern() {

	Index index;

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
		if (this->grid[index.x][index.y].state != TILESTATE::STATE::GENERATOR) {
			this->grid[index.x][index.y].state = TILESTATE::TFALLING;
			this->grid[index.x][index.y].counter = 0.0f;
		}
	}
	this->counter = 0.0;
}

void GamePlayState::updateFloor()
{
	Index index(0, 0);
	XMFLOAT3 currVel(0, 0, 0);
	XMFLOAT3 fallColor(0.6f, 0.1f, 0.1f);
	XMFLOAT3 baseColor(0.0f, 0.784f, 1.0f);
	XMFLOAT3 holeColor(0.0f, 0.0f, 0.0f);
	XMFLOAT3 finalColor(0.0f, 0.0f, 0.0f);
	XMFLOAT3 flashColor(1.0f, 1.0f, 1.0f);
	XMFLOAT3 recoverColor(0.6f, 0.1f, 0.1f);
	XMFLOAT3 electrifiedColor = XMFLOAT3(1.0f, 1.0f, 0.0f);
	XMFLOAT3 heatedColor = XMFLOAT3(1.0f, 0.55f, 0.0f);
	XMFLOAT3 cooledColor = XMFLOAT3(0.0f, 0.75f, 1.0f);
	XMFLOAT3 tempColor1;
	XMFLOAT3 tempColor2;
	float baseHeight = 0.5f - 0.01f;

	for (int i = 0; i < this->grid.size(); i++) {
		for (int j = 0; j < this->grid[i].size(); j++) {
			switch (this->grid[i][j].state)
			{
			case TILESTATE::ACTIVE:
				break;
			case TILESTATE::TFALLING:
				this->grid[i][j].counter += this->dt;
				if (this->grid[i][j].counter < this->grid[i][j].stateTime) {
					tempColor1.x = baseColor.x - (baseColor.x / (this->grid[i][j].stateTime)) * this->grid[i][j].counter;
					tempColor1.y = baseColor.y - (baseColor.y / (this->grid[i][j].stateTime)) * this->grid[i][j].counter;
					tempColor1.z = baseColor.z - (baseColor.z / (this->grid[i][j].stateTime)) * this->grid[i][j].counter;
					
					tempColor2.x = (fallColor.x / (this->grid[i][j].stateTime)) * counter;
					tempColor2.y = (fallColor.y / (this->grid[i][j].stateTime)) * counter;
					tempColor2.z = (fallColor.z / (this->grid[i][j].stateTime)) * counter;

					finalColor.x = tempColor1.x + tempColor2.x;
					finalColor.y = tempColor1.y + tempColor2.y;
					finalColor.z = tempColor1.z + tempColor2.z;

					this->grid[i][j].color = finalColor;
				}
				else {
					this->grid[i][j].color = fallColor;
					this->grid[i][j].state = TILESTATE::FALLING;
					this->grid[i][j].counter = 0.0;
				}
				break;
			case TILESTATE::FALLING:
				this->grid[i][j].counter += this->dt;
				if (this->grid[i][j].counter < this->grid[i][j].stateTime) {
					this->grid[i][j].posY += GRAVITY / 4.0f * this->counter;
				}
				else {
					this->grid[i][j].posY = baseHeight;
					this->grid[i][j].color = holeColor;
					this->grid[i][j].state = TILESTATE::HOLE;
					this->grid[i][j].counter = 0.0;
				}
				break;
			case TILESTATE::HOLE:
				this->grid[i][j].counter += this->dt;
				if (this->grid[i][j].counter > this->grid[i][j].stateTime) {
					this->grid[i][j].state = TILESTATE::RECOVERING;
					this->grid[i][j].counter = 0.0;
				}
				break;
			case TILESTATE::RECOVERING:
				this->grid[i][j].counter += this->dt;
				if (this->grid[i][j].counter < this->grid[i][j].stateTime) {
					tempColor1.x = (recoverColor.x / (this->grid[i][j].stateTime)) * this->grid[i][j].counter;
					tempColor1.y = (recoverColor.y / (this->grid[i][j].stateTime)) * this->grid[i][j].counter;
					tempColor1.z = (recoverColor.z / (this->grid[i][j].stateTime)) * this->grid[i][j].counter;

					finalColor.x = tempColor1.x + holeColor.x;
					finalColor.y = tempColor1.y + holeColor.y;
					finalColor.z = tempColor1.z + holeColor.z;

					this->grid[i][j].color = finalColor;
				}
				else {
					this->grid[i][j].color = XMFLOAT3(0.0f, 1.0f, 0.0f);
					this->grid[i][j].state = TILESTATE::FLASH;
					this->grid[i][j].counter = 0.0;
				}
				break;
			case TILESTATE::FLASH:
				this->grid[i][j].counter += this->dt;
				if (this->grid[i][j].counter > 0.2) {
					this->grid[i][j].color = baseColor;
					this->grid[i][j].state = TILESTATE::ACTIVE;
					this->grid[i][j].counter = 0.0;
				}
				break;
			case TILESTATE::GENERATOR:
				this->grid[i][j].counter += this->dt;
				if (this->grid[i][j].counter > this->grid[i][j].coolDownTime) {
					index.x = i;
					index.y = j;
					this->generatorDischarge(index);
					this->grid[i][j].counter = 0.0;
				}
				break;
			case TILESTATE::TELECTRIFIED:
				this->grid[i][j].counter += this->dt;
				if (this->grid[i][j].counter < this->grid[i][j].chargeTime) {
					tempColor1.x = baseColor.x - (baseColor.x / (this->grid[i][j].stateTime)) * this->grid[i][j].counter;
					tempColor1.y = baseColor.y - (baseColor.y / (this->grid[i][j].stateTime)) * this->grid[i][j].counter;
					tempColor1.z = baseColor.z - (baseColor.z / (this->grid[i][j].stateTime)) * this->grid[i][j].counter;

					tempColor2.x = (electrifiedColor.x / (this->grid[i][j].chargeTime)) * this->grid[i][j].counter;
					tempColor2.y = (electrifiedColor.y / (this->grid[i][j].chargeTime)) * this->grid[i][j].counter;
					tempColor2.z = (electrifiedColor.z / (this->grid[i][j].chargeTime)) * this->grid[i][j].counter;

					this->grid[i][j].color = tempColor1 + tempColor2;
				}
				else {
					this->grid[i][j].color = electrifiedColor;
					this->grid[i][j].state = TILESTATE::ELECTRIFIED;
					this->grid[i][j].counter = 0.0;
				}
				break;
			case TILESTATE::ELECTRIFIED:
				this->grid[i][j].counter += this->dt;
				if (this->grid[i][j].counter > 0.2) {
					this->grid[i][j].state = TILESTATE::ACTIVE;
					this->grid[i][j].color = baseColor;
					this->grid[i][j].counter = 0.0;
				}
				break;
			case TILESTATE::THEATED:
				this->grid[i][j].counter += this->dt;
				if (this->grid[i][j].counter < this->grid[i][j].chargeTime) {
					tempColor1.x = baseColor.x - (baseColor.x / (this->grid[i][j].stateTime)) * this->grid[i][j].counter;
					tempColor1.y = baseColor.y - (baseColor.y / (this->grid[i][j].stateTime)) * this->grid[i][j].counter;
					tempColor1.z = baseColor.z - (baseColor.z / (this->grid[i][j].stateTime)) * this->grid[i][j].counter;

					tempColor2.x = (heatedColor.x / (this->grid[i][j].chargeTime)) * this->grid[i][j].counter;
					tempColor2.y = (heatedColor.y / (this->grid[i][j].chargeTime)) * this->grid[i][j].counter;
					tempColor2.z = (heatedColor.z / (this->grid[i][j].chargeTime)) * this->grid[i][j].counter;

					this->grid[i][j].color = tempColor1 + tempColor2;
				}
				else {
					this->grid[i][j].color = heatedColor;
					this->grid[i][j].state = TILESTATE::HEATED;
					this->grid[i][j].counter = 0.0;
				}
				break;
			case TILESTATE::HEATED:
				this->grid[i][j].counter += this->dt;
				if (this->grid[i][j].counter > 0.2) {
					this->grid[i][j].state = TILESTATE::ACTIVE;
					this->grid[i][j].color = baseColor;
					this->grid[i][j].counter = 0.0;
				}
				break;
			case TILESTATE::TCOOLED:
				this->grid[i][j].counter += this->dt;
				if (this->grid[i][j].counter < this->grid[i][j].chargeTime) {
					tempColor1.x = baseColor.x - (baseColor.x / (this->grid[i][j].stateTime)) * this->grid[i][j].counter;
					tempColor1.y = baseColor.y - (baseColor.y / (this->grid[i][j].stateTime)) * this->grid[i][j].counter;
					tempColor1.z = baseColor.z - (baseColor.z / (this->grid[i][j].stateTime)) * this->grid[i][j].counter;

					tempColor2.x = (cooledColor.x / (this->grid[i][j].chargeTime)) * this->grid[i][j].counter;
					tempColor2.y = (cooledColor.y / (this->grid[i][j].chargeTime)) * this->grid[i][j].counter;
					tempColor2.z = (cooledColor.z / (this->grid[i][j].chargeTime)) * this->grid[i][j].counter;

					this->grid[i][j].color =  tempColor1 + tempColor2;
				}
				else {
					this->grid[i][j].color = cooledColor;
					this->grid[i][j].state = TILESTATE::COOLED;
					this->grid[i][j].counter = 0.0;
				}
				break;
			case TILESTATE::COOLED:
				this->grid[i][j].counter += this->dt;
				if (this->grid[i][j].counter > 0.2) {
					this->grid[i][j].state = TILESTATE::ACTIVE;
					this->grid[i][j].color = baseColor;
					this->grid[i][j].counter = 0.0;
				}
				break;
			default:
				break;
			}
		}
	}
}

void GamePlayState::checkPlayerTileStatus() 
{
	TILESTATE::STATE state;
	this->lm.checkTileStatusFromPos(this->player1->GETPosition(), this->grid, state);

	//Check if the player is on a active floor tile or if he fell of the map.
	if (this->player1->getState() != OBJECTSTATE::TYPE::FALLING) {
		if (state == TILESTATE::STATE::FALLING ||
			state == TILESTATE::STATE::HOLE ||
			state == TILESTATE::STATE::RECOVERING) {
			this->player1->setState(OBJECTSTATE::TYPE::FALLING);
		} 
		else {
			switch (state) 
			{
			case EFFECTSTATUS::EFFECT::IDLE:
				break;
			case EFFECTSTATUS::EFFECT::HEATED:
				//To be filled out
				break;
			case EFFECTSTATUS::EFFECT::COOLED:
				//To be filled out
				break;
			case EFFECTSTATUS::EFFECT::ELECTRIFIED:
				//To be filled out
				break;
			default:
				break;
			}
		}
	}

}

void GamePlayState::generatorDischarge(Index index) 
{
	Index currIndex = index;
	for (int i = index.y + 1; i < this->grid[index.x].size(); i++) {
		if (this->grid[index.x][i].state == TILESTATE::ACTIVE) {
			this->grid[index.x][i].state = this->grid[index.x][index.y].genEffect;
		}
	}
	for (int i = index.y - 1; i >= 0; i--) {
		if (this->grid[index.x][i].state == TILESTATE::ACTIVE) {
			this->grid[index.x][i].state = this->grid[index.x][index.y].genEffect;
		}
	}
	for (int i = index.x + 1; i < this->grid.size(); i++) {
		if (this->grid[i][index.y].state == TILESTATE::ACTIVE) {
			this->grid[i][index.y].state = this->grid[index.x][index.y].genEffect;
		}
	}
	for (int i = index.x - 1; i >= 0; i--) {
		if (this->grid[i][index.y].state == TILESTATE::ACTIVE) {
			this->grid[i][index.y].state = this->grid[index.x][index.y].genEffect;
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
	this->lm.selectArena();
	this->quadTree.initializeQuadTree(0, ARENADATA::GETarenaWidth(), ARENADATA::GETarenaHeight(), 0, 0);
	this->camera.init(ARENADATA::GETarenaWidth(), ARENADATA::GETarenaHeight());
	this->rio.initialize(this->camera, this->pointLights);
	this->initPlayer();
	this->ID = this->GUI.initGUI(
		this->newID(),
		this->camera.GETcameraPos(),
		this->camera.GETfacingDirFloat3(),
		this->GUIObjects,
		this->graphics
	);
	this->ID = lm.initArena(this->newID(), this->staticPhysicsCount, *this, this->fallData, this->grid, this->staticObjects, this->noCollisionDynamicObjects, this->dynamicObjects, this->graphics, this->easyPatterns, this->mediumPatterns, this->hardPatterns, this->enemySpawnPos);
	int i = 0;
	for (std::list<GameObject*>::iterator it = this->staticObjects.begin(); it != this->staticObjects.end() && i < this->staticPhysicsCount; it++) {
		this->quadTree.insertStaticObject(*it);
		i++;
	}

	std::vector<ActorObject*> allPlayers;
	allPlayers.push_back(player1);
	this->enemyManager.initialize(sGamePlayState, allPlayers);

	this->pointLights.reserve(MAX_NUM_POINTLIGHTS);
	this->pointLights.push_back(Light(XMFLOAT3(ARENADATA::GETarenaWidth() * 0.5, ARENADATA::GETsquareSize() * 10, ARENADATA::GETarenaHeight() * 0.5), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.3f, 0.3f, 0.3f), XMFLOAT3(0.8f, 0.0001f, 0.00001f), 50.0f));
	this->pointLights.push_back(Light(XMFLOAT3(ARENADATA::GETarenaWidth() - 200.0f, ARENADATA::GETsquareSize() * 3, ARENADATA::GETarenaHeight() - 200.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), 50.0f));
	this->pointLights.push_back(Light(XMFLOAT3(200.0f, 150.0f, 200.0f), XMFLOAT3(0.0f, 0.0f, 1.0f), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(1.0f, 0.0f, 0.0f), 50.0f));

	this->mousePicker = new MouseInput(this->camera.GETcameraPos(), this->camera.GETfacingDirFloat3());
	this->enemyManager.startLevel1();

	this->mediumTime = 120.0;
	this->hardTime = 240.0;
	this->totalLevelTime = 0.0;
	this->timeBetweenPatterns = 20.0;
	this->stateTime = 5.0;
	this->recoveryMode = false;
	this->counter = 0.0;
	this->genTimer = 10.0;
	this->gTimeLastFrame = Locator::getGameTime()->GetTime();
	this->floorState = FLOORSTATE::STATE::ACTIVE;
	this->fallPatternCoolDown = 25.0;
	
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

	for (auto &iterator : this->GUIObjects) {
		iterator->cleanUp();
		delete iterator;
	}
	this->GUIObjects.clear();

	for (auto &i : this->playerInput) {
		i = nullptr;
	}

	this->quadTree.cleanup();

	//for (auto && iterator2 : this->pointLights) {
	//	delete &iterator2;
	//}

	this->pointLights.clear();
	
	this->graphics.clear();

	//Clear the grid
	this->grid.clear();
	this->floorState = FLOORSTATE::STATE::ACTIVE;
	//Clear FloorFallPattern arrays.
	this->easyPatterns.clear();
	this->mediumPatterns.clear();
	this->hardPatterns.clear();
	this->currData.pattern.clear();
	//Clear enemySpawnPos
	this->enemySpawnPos.cleanUp();

	InputComponent::cleanup();

	this->staticPhysicsCount = 0;
	this->counter = 0;
	this->ID = 0;
	this->counter = 0;
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
	this->dt = Locator::getGameTime()->GetTime() - this->gTimeLastFrame;
	this->gTimeLastFrame = Locator::getGameTime()->GetTime();
	this->totalLevelTime += this->dt;
	this->counter += this->dt;
	this->genCounter += this->dt;
	this->GUI.updateGUI(this->player1);
	
	if (this->counter > this->fallPatternCoolDown) {
		this->updateFloorPattern();
	}
	if (this->genCounter > this->genTimer) {
		this->lm.createGenerator(this->newID(), this->grid, this->dynamicObjects, this->graphics, this->genIndex);
		this->genCounter = 0.0;
	}
	this->updateFloor();

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

	this->checkPlayerTileStatus();
//	this->enemyManager.update();
	this->checkCollisions();
}

void GamePlayState::render(GameManager * gm) 
{
	rio.render(this->graphics);
	gm->setupSecondRenderPass();
	rio.injectResourcesIntoSecondPass(this->grid);
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
	XMFLOAT3 playerPos(static_cast<float>(ARENADATA::GETarenaWidth() / 2), playerScales.y, static_cast<float>(ARENADATA::GETarenaHeight() / 2));
	XMFLOAT3 playerVelocity(300.0f, -300.0f, 300.0f);
	float actorSpeed = 1;

	/// ACTOR OBJECT:
	actor = new ActorObject(nextID, actorSpeed, playerPos, playerVelocity, this, OBJECTTYPE::PLAYER, 100.0f);

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


Projectile* GamePlayState::initProjectile(XMFLOAT3 pos, XMFLOAT3 dir, ProjProp props)
{
	Projectile* proj = nullptr;
	int nextID = this->newID();

	// Declare Components
	BlockComponent* block = nullptr;
	PhysicsComponent* phyComp = nullptr;

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