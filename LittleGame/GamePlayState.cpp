#include "GamePlayState.h"
#include "StatisticsMenuState.h"
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
#include "RewardMenuState.h"



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
	XMFLOAT3 baseColor(0.2f, 0.2f, 0.45f);
	XMFLOAT3 holeColor(0.0f, 0.0f, 0.0f);
	XMFLOAT3 finalColor(0.0f, 0.0f, 0.0f);
	XMFLOAT3 flashColor(1.0f, 1.0f, 1.0f);
	XMFLOAT3 recoverColor(0.6f, 0.1f, 0.1f);
	XMFLOAT3 electrifiedColor = XMFLOAT3(0.5f, 0.5f, 0.05f);
	XMFLOAT3 heatedColor = XMFLOAT3(0.5f, 0.245f, 0.05f);
	XMFLOAT3 cooledColor = XMFLOAT3(0.05f, 0.4f, 0.5f);
	
	XMFLOAT3 bossTileColor = XMFLOAT3(0.001f, 0.75f, 0.001f);
	XMFLOAT3 teleportColor = XMFLOAT3(0.001f, 0.75f, 0.001f);
	XMFLOAT3 tempColor1;
	XMFLOAT3 tempColor2;
	float baseHeight = 0.5f - 0.01f;

	for (int i = 0; i < this->grid.size(); i++) {
		for (int j = 0; j < this->grid[i].size(); j++) {
			switch (this->grid[i][j].state)
			{
			case TILESTATE::ACTIVE:
				this->grid[i][j].color = baseColor;
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
					//this->grid[i][j].posY = baseHeight;
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
				this->grid[i][j].posY -= GRAVITY / 4.0f * this->counter;
				if (this->grid[i][j].posY < baseHeight) {
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
					this->grid[i][j].posY = baseHeight;
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
				this->grid[i][j].state = TILESTATE::ACTIVE;
				this->grid[i][j].color = baseColor;
				this->grid[i][j].counter = 0.0;
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
			case TILESTATE::BOSSTILE:
				this->grid[i][j].color = bossTileColor;
				break;
			case TILESTATE::TTELEPORT:
				this->grid[i][j].counter += this->dt;
				if (this->grid[i][j].counter < this->grid[i][j].chargeTime) {
					tempColor1.x = baseColor.x - (baseColor.x / (this->grid[i][j].stateTime)) * this->grid[i][j].counter;
					tempColor1.y = baseColor.y - (baseColor.y / (this->grid[i][j].stateTime)) * this->grid[i][j].counter;
					tempColor1.z = baseColor.z - (baseColor.z / (this->grid[i][j].stateTime)) * this->grid[i][j].counter;

					tempColor2.x = (teleportColor.x / (this->grid[i][j].chargeTime)) * this->grid[i][j].counter;
					tempColor2.y = (teleportColor.y / (this->grid[i][j].chargeTime)) * this->grid[i][j].counter;
					tempColor2.z = (teleportColor.z / (this->grid[i][j].chargeTime)) * this->grid[i][j].counter;

					this->grid[i][j].color = tempColor1 + tempColor2;
				}
				else {
					this->grid[i][j].color = teleportColor;
					this->grid[i][j].state = TILESTATE::TELEPORT;
					this->grid[i][j].counter = 0.0;
				}
				break;
			case TILESTATE::TELEPORT:
				this->grid[i][j].color = teleportColor;
				break;
			default:
				break;
			}
		}
	}

	float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());
	float pulseVelocity = 1000.0f * dt;

	for (int i = 0; i < this->gridPulsePoints[0].size(); i++)
	{
		pulseVelocity *= -1;
		this->gridPulsePoints[0][i].y += pulseVelocity;

		if (this->gridPulsePoints[0][i].y > ARENADATA::GETarenaHeight())
		{
			this->gridPulsePoints[0][i].y = this->gridPulsePoints[0][i].y - ARENADATA::GETarenaHeight();
		}
	}

	for (int i = 0; i < this->gridPulsePoints[1].size(); i++)
	{
		pulseVelocity *= -1;
		this->gridPulsePoints[1][i].x += pulseVelocity;

		if (this->gridPulsePoints[1][i].x > ARENADATA::GETarenaWidth())
		{
			this->gridPulsePoints[1][i].x = this->gridPulsePoints[1][i].x - ARENADATA::GETarenaWidth();
		}
	}
}

void GamePlayState::checkPlayerTileStatus() 
{
	TILESTATE::STATE state;
	XMFLOAT3 playerPos = this->player1->GETPosition();
	this->lm.checkTileStatusFromPos(playerPos, this->grid, state);

	//Check if the player is on a active floor tile or if he fell of the map.
	if (this->player1->getState() != OBJECTSTATE::TYPE::FALLING) {
		if (state == TILESTATE::STATE::FALLING ||
			state == TILESTATE::STATE::HOLE ||
			state == TILESTATE::STATE::RECOVERING) {
			this->player1->setState(OBJECTSTATE::TYPE::FALLING);
			this->player1->SETvelocityMagnitude(this->player1->GETvelocityMagnitude() * -1);
		} 
		else {
			switch (state) 
			{
			case TILESTATE::STATE::ACTIVE:
				break;
			case TILESTATE::STATE::HEATED:
				this->player1->applyStatusEffect(TILESTATE::STATE::HEATED);
				break;
			case TILESTATE::STATE::COOLED:
				this->player1->applyStatusEffect(TILESTATE::STATE::COOLED);
				break;
			case TILESTATE::STATE::ELECTRIFIED:
				this->player1->applyStatusEffect(TILESTATE::STATE::ELECTRIFIED);
				break;
			case TILESTATE::STATE::BOSSTILE:
				this->playerSteppedOnBossTile = true;
				this->player1->restoreFullHealth();
				break;
			case TILESTATE::STATE::TELEPORT:
				this->player1->setPosition(XMFLOAT3(ARENADATA::GETsquareSize() * 1.5f, playerPos.y, ARENADATA::GETarenaHeight() * 0.5f - ARENADATA::GETsquareSize() * 0.5f));
				this->player1->setState(OBJECTSTATE::TYPE::TELEPORTED);
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

void GamePlayState::init() 
{
	this->lights.reserve(MAX_NUM_POINTLIGHTS);
	this->lights.push(Light(XMFLOAT3(static_cast<float>(ARENADATA::GETarenaWidth() / 2), static_cast<float>(ARENADATA::GETsquareSize() * 10), static_cast<float>(ARENADATA::GETarenaHeight() / 2)), XMFLOAT3(0.0f, 0.0f, 0.0f), XMFLOAT3(0.3f, 0.3f, 0.3f), XMFLOAT3(0.5f, 0.0f, 0.0f), 50.0f));

	this->lm.selectArena();
	this->quadTree.initializeQuadTree(0, static_cast<float>(ARENADATA::GETarenaWidth()), static_cast<float>(ARENADATA::GETarenaHeight()), 0, 0);
	this->camera.init(static_cast<float>(ARENADATA::GETarenaWidth()), static_cast<float>(ARENADATA::GETarenaHeight()));
	this->rio.initialize(this->camera, this->lights);
	this->initPlayer();
	this->ID = this->GUI.initGUI(
		this->newID(),
		this->camera.GETcameraPos(),
		this->camera.GETfacingDir(),
		this->GUIObjects,
		this->graphics
	);
	this->ID = lm.initArena(this->newID(), this->staticPhysicsCount, *this, this->fallData, this->grid, this->staticObjects, this->noCollisionDynamicObjects, this->dynamicObjects, this->graphics, this->easyPatterns, this->mediumPatterns, this->hardPatterns, this->enemySpawnPos, this->gridPulsePoints);
	int i = 0;
	for (std::list<GameObject*>::iterator it = this->staticObjects.begin(); it != this->staticObjects.end() && i < this->staticPhysicsCount; it++) {
		this->quadTree.insertStaticObject(*it);
		i++;
	}

	std::vector<ActorObject*> allPlayers;
	allPlayers.push_back(player1);
	this->enemyManager.initialize(sGamePlayState, allPlayers);

	this->mousePicker = new MouseInput(this->camera.GETcameraPos(), this->camera.GETfacingDir());

	
	int randomLevel = Locator::getRandomGenerator()->GenerateInt(1, 3);
	// TESTING ------------------------ 
	//randomLevel = 1; 
	// TESTING ------------------------ 

	if (Locator::getStatsHeader()->getStats().level < 10) {
		switch (randomLevel)
		{
		case 1:
			this->enemyManager.startStandardLevel(this->enemySpawnPos, Locator::getStatsHeader()->getStats().difficulty);
			break;
		case 2:
			this->enemyManager.startRampLevel(this->enemySpawnPos, Locator::getStatsHeader()->getStats().difficulty);
			break;
		case 3:
			this->enemyManager.startPulseLevel(this->enemySpawnPos, Locator::getStatsHeader()->getStats().difficulty);
			break;
		}
	}
	else {
		this->enemyManager.startBossLevel();
	}
	
	this->mediumTime = 120.0;
	this->hardTime = 240.0;
	this->totalLevelTime = 0.0;
	this->counter = 0.0;
	this->genTimer = 10.0;
	this->gTimeLastFrame = static_cast<float>(Locator::getGameTime()->GetTime());
	this->fallPatternCoolDown = 25.0;
	this->playerSteppedOnBossTile = false;
	
	RewardMenuState::getInstance()->provide(this->player1);

	// Player will always get 2 rewards as a base
	this->nrOfPickedUpLoot = 2;

	// Adds to the level each time it starts a level
	Locator::getStatsHeader()->addLevel();
	Locator::getGameTime()->setMultiplier(1.0);

	//FOR TESTING
	this->player1->turnOnInvulnerability();
}

void GamePlayState::cleanUp()
{
	Locator::getAudioManager()->stopSound();
	// Direct internal objects
	this->rio.cleanUp();
	// this->camera.cleanUp();

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

	// Needs to be after dynamic objects:
	// No Playerobject-->no unique clean for enemy-->spells clean up swarmers from grid-->swarmers try using grid after it's deleted
	this->enemyManager.cleanUp();

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

	this->lights.clear();

	this->gridPulsePoints.clear();
	
	this->graphics.clear();

	this->GUI.cleanUp();

	//Clear the grid
	this->grid.clear();
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
			StateManager::changeState(StatisticsMenuState::getInstance());
			Locator::getD2D()->saveScreen();
		}
		else if (globalmsg == GLOBALMESSAGES::PLAYERWON) {
			//Sends the number of Lootboxes picked up druring the game
			RewardMenuState::getInstance()->provide(this->nrOfPickedUpLoot);


			// Change last so we've already done all of the changes.
			StateManager::changeState(RestartState::getInstance());
		}

		//else if (globalmsg == GLOBALMESSAGES::ENEMYDIED)
		//{
		//	int loopCount = Locator::getGlobalEvents()->getEnemyDeathCount();
		//	for (int i = 0; i < loopCount; i++)
		//		GUI.popEnemyElement(this->GUIObjects, this->graphics);
		//}
	}
}


void GamePlayState::update(GameManager * gm)
{	
	this->dt = Locator::getGameTime()->getDeltaTime();
	this->gTimeLastFrame = Locator::getGameTime()->GetTime();
	this->totalLevelTime += this->dt;
	if (dt < 0)
		dt = 0;
	this->counter += this->dt;
	this->genCounter += this->dt;
	this->GUI.updateGUI(this->player1);
	
	if (Locator::getStatsHeader()->getStats().level < 10) {
		if (this->counter > this->fallPatternCoolDown) {
			this->updateFloorPattern();
		}
		if (this->genCounter > this->genTimer) {
			this->lm.createGenerator(this->newID(), this->grid, this->dynamicObjects, this->graphics, this->genIndex);
			this->genCounter = 0.0;
		}
	}
	this->updateFloor();

	int ID;
	Index genIndex;
	XMFLOAT3 genPos;
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
			//TEST
			for (int i = 0; i < this->bossChargers.size(); i++) {
				if (ID == this->bossChargers[i]->getID()) {
					this->bossChargers.erase(this->bossChargers.begin() + i);
				}
			}
			int j = this->graphics.size();
			for (std::list<GraphicsComponent*>::reverse_iterator rit = this->graphics.rbegin(); rit != this->graphics.rend() && j > this->staticPhysicsCount; rit++) {
				if ((*rit)->getID() == ID) {
					this->graphics.erase(std::next(rit).base());
					j++;
				}
				j--;
			}
			if ((*it)->getType() == OBJECTTYPE::TYPE::ENEMY)
				this->GUI.popEnemyElement(this->GUIObjects, this->graphics);

			else if ((*it)->getType() == OBJECTTYPE::GENERATOR) {
				genPos = (*it)->GETPosition();
				genIndex = this->lm.findTileIndexFromPos(XMFLOAT2(genPos.x, genPos.z));
				for (int i = 0; i < this->genIndex.size(); i++) {
					if (genIndex.x == this->genIndex[i].x && genIndex.y == this->genIndex[i].y) {
						this->grid[this->genIndex[i].x][this->genIndex[i].y].state = TILESTATE::ACTIVE;
						this->genIndex.erase(this->genIndex.begin() + i);
						break;
					}
				}
			}
			(*it)->cleanUp();
			delete (*it);
			it = this->dynamicObjects.erase(it);
			it--;
		}
	}

	this->checkPlayerTileStatus();
	this->enemyManager.update(&this->GUI);
	this->checkCollisions();
}

void GamePlayState::render(GameManager * gm) 
{
	rio.render(this->graphics);
	gm->setupSecondRenderPass();
	rio.injectResourcesIntoSecondPass(this->grid, this->gridPulsePoints);
	gm->display(this);
}

GamePlayState* GamePlayState::getInstance() 
{
	return &sGamePlayState;
}

std::list<GameObject*>* GamePlayState::GETGUIObjects()
{
	return &this->GUIObjects;
}

std::list<GameObject*>* GamePlayState::getDynamicObjects()
{
	return &this->dynamicObjects;
}

std::list<GraphicsComponent*>* GamePlayState::getGraphicsComponents()
{
	return &this->graphics;
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
	float velocityMagnitude = 100.0f;
	XMFLOAT3 playerPos(static_cast<float>(ARENADATA::GETarenaWidth() * 0.5f), playerScales.y, static_cast<float>(ARENADATA::GETarenaHeight() * 0.5f));
	float actorAccelerationSpeed = 150.0f;
	float topSpeed = 11.0f;

	/// ACTOR OBJECT:
	actor = new ActorObject(nextID, velocityMagnitude, topSpeed, playerPos, this, OBJECTTYPE::PLAYER, 100.0f);

	/// PHYSICS COMPONENT:
	physics = new PhysicsComponent(*actor, 20.0f);

	/// BLOCK COMPONENT
	block = new BlockComponent(*this, *actor, playerColor, playerScales, playerRotation);

	/// INPUT COMPONENT:
	if (this->useController)
	{
		input = new ControllerComponent(*actor, 0);
	}
	else
	{
		input = new KeyboardComponent(*actor);
	}

	//Add the spell to the player, numbers are used to in different places
	// Slots:
	// 0:
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

bool GamePlayState::switchControllerInput()
{
	this->useController = !this->useController;
	return useController;
}


Projectile* GamePlayState::initProjectile(XMFLOAT3 pos, GameObject* shooter, ProjProp props, Light light)
{
	Projectile* proj = nullptr;
	int nextID = this->newID();

	XMFLOAT3 dir = shooter->getDirection();

	// Declare Components
	BlockComponent* block = nullptr;
	PhysicsComponent* phyComp = nullptr;

	XMFLOAT3 position = { pos.x /*+ dir.x * props.size*/,  40.0f /*pos.y*/ /*+ dir.y * props.size */, pos.z /*+ dir.z * props.size*/ };

	size_t lightID = this->lights.push(light);

	proj = new Projectile(nextID, props.speed, props.range, props.behavior, shooter, position, dir, OBJECTTYPE::PROJECTILE, lightID, &lights);

	//input for blockComp
	XMFLOAT3 scale(props.size, props.size, props.size);
	//XMFLOAT3 position = pos;
	XMFLOAT4 tempColor(props.color);
	XMFLOAT3 rotation(0.0f, 0.0f, 0.0f);
	block = new BlockComponent(*this, *proj, tempColor, scale, rotation);

	//Template for Physics
	phyComp = new PhysicsComponent(*proj, (props.size));

	
	//Add proj to objectArrays
	this->dynamicObjects.push_back(proj);

	return proj;
}

std::vector<std::vector<tileData>>& GamePlayState::GETgrid()
{
	return this->grid;
}

bool GamePlayState::GETplayerSteppedOnBossTile()
{
	return this->playerSteppedOnBossTile;
}

void GamePlayState::SETplayerSteppedOnBossTile(bool input)
{
	this->playerSteppedOnBossTile = input;
}

void GamePlayState::spawnBossGenerators()
{
	this->lm.createBossGenerators(this->grid, this->dynamicObjects, this->graphics, this->genIndex);
}

void GamePlayState::spawnBossChargers(float hp)
{
	this->enemyManager.createBossChargers(this->bossChargers, this->dynamicObjects, hp);
}

bool GamePlayState::checkGenerators()
{
	bool returnValue = false;
	if (this->genIndex.size() == 0) {
		returnValue = true;
	}
	return returnValue;
}

void GamePlayState::createABossWave()
{
	this->enemyManager.createBossWave(this->enemySpawnPos);
}

float GamePlayState::checkBossChargersHealth() {
	float totalBossHealth = 0.0f;
	for (int i = 0; i < this->bossChargers.size(); i++) {
			totalBossHealth += static_cast<EnemyObject*>(this->bossChargers[i])->GEThp();
	}
	for (int i = 0; i < this->bossChargers.size(); i++) {
		static_cast<EnemyObject*>(this->bossChargers[i])->setHp(totalBossHealth / this->bossChargers.size());
	}
	if (totalBossHealth < 0.0f) {
		int warning = 1;
	}
	return totalBossHealth;
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