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

#include "DamageSpell.h"
#include "MobilitySpell.h"

using namespace DirectX::SimpleMath;

GamePlayState GamePlayState::sGamePlayState;

void GamePlayState::updatePhysicsComponents()
{
	for (auto&& i : physicsListDynamic) {
		if (i->GETEntityPointer()->getState() != OBJECTSTATE::DEAD) {
			i->updateBoundingArea(i->GETEntityPointer()->getPosition());
		}
	}
}

void GamePlayState::checkCollisions() {
	//--------//
	// LOOP 1 //   : Looping through each DYNAMIC physicsComponent
	//--------//
	for (auto&& i : this->physicsListDynamic) {
		// Comparing to all other DYNAMIC & STATIC physComponents.
		// NOTE: Skipping if object state = DEAD.
		int iID = i->getID();
		if (i->GETEntityPointer()->getState() != OBJECTSTATE::DEAD) {
			//----------//
			// LOOP 2.1 //   :  DYNAMIC <--> DYNAMIC Collision
			//----------//
			for (auto&& k : this->physicsListDynamic) {
				int kID = k->getID();
				if (iID != kID)
				{
					if (k->GETEntityPointer()->getState() != OBJECTSTATE::DEAD) {

						if (i->checkCollision(k->GETBoundingSphere())) {
							// Call COLLISION-CLASS function
							this->collisionHandler.executeCollision(
								i->GETEntityPointer(),
								k->GETEntityPointer(),
								&i->GETBoundingSphere(),
								&k->GETBoundingSphere()
							);
						}
					}
				}
				
			}
			//----------//
			// LOOP 2.2 //   :  DYNAMIC <--> STATIC Collision
			//----------//
			for (auto&& k : this->physicsListStatic) {
				if (k->GETEntityPointer()->getState() != OBJECTSTATE::DEAD) {

					if (i->checkCollision(k->GETBoundingSphere())) {
						// Call COLLISION-CLASS function
						this->collisionHandler.executeCollision(
							i->GETEntityPointer(),
							k->GETEntityPointer(),
							&i->GETBoundingSphere(),
							&k->GETBoundingSphere()
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
	this->enemyManager.initialize(sGamePlayState);
	this->initPlayer();
	this->ID = lm.initArena(this->newID(), ARENAWIDTH, ARENAHEIGHT, *this, this->grid, this->staticObjects, this->graphics, this->physicsListStatic);

	for (auto &i : this->graphics) {
		this->rio.addGraphics(i);
	}

	this->enemyManager.startLevel1();
}

void GamePlayState::cleanUp()
{
	// Direct internal objects
	// this->rio.cleanUp();
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

	this->enemyManager.update();

	player1->decCD();

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

std::vector<GameObject*>* GamePlayState::getDynamicObjects()
{
	return &this->dynamicObjects;
}

void GamePlayState::addGraphicsToRio(GraphicsComponent * graphicsComponent)
{
	this->rio.addGraphics(graphicsComponent);
}

void GamePlayState::initPlayer()
{
	ActorObject* actor;
	BlockComponent* block;
	InputComponent* input;
	PhysicsComponent* physics;
	int nextID = this->newID();
	
	/// ACTOR OBJECT:
	XMFLOAT3 playerScales(10.0f, 40.0f, 10.0f);
	XMFLOAT3 playerPos((float)(ARENAWIDTH / 2), playerScales.y, (float)(ARENAHEIGHT / 2));
	XMFLOAT3 playerVelocity(300.0f, 300.0f, 300.0f);
	actor = new ActorObject(nextID, playerPos, playerVelocity, this, OBJECTTYPE::PLAYER);

	/// PHYSICS COMPONENT:
	// 1: We new a PhysicsComponent, using the actor-POINTER'S address as a parameter.
	physics = new PhysicsComponent(*actor, 20.0f);
	// 2: We add this component to the Dynamic list because this actor = dynamic.
	this->physicsListDynamic.push_back(physics);
	
	/// BLOCK COMPONENT:
	//Create the playerColor and the new BlockComponent that will represent the players body.
	XMFLOAT4 playerColor(50.0f, 205.0f, 50.0f, 255.0f);
	XMFLOAT3 playerRotation(0, 0, 0);
	block = new BlockComponent(*this, *actor, playerColor, playerScales, playerRotation);

	/// KEYBOARD COMPONENT:
	//input = new ControllerComponent(*actor, 0);
	input = new KeyboardComponent(*actor);

	// Add to relevant vector
	this->dynamicObjects.push_back(actor);
	this->graphics.push_back(block);



	//Create the spell
	DamageSpell* autoAttackSpell = new DamageSpell(actor, NAME::AUTOATTACK);
	DamageSpell* explosionSpell = new DamageSpell(actor, NAME::EXPLOSION);
	MobilitySpell* dashSpell = new MobilitySpell(actor, NAME::DASH);

	//Add the spell to the player
	actor->addSpell(autoAttackSpell);
	actor->addSpell(explosionSpell);
	actor->addSpell(dashSpell);

	this->playerInput[0] = input;
	player1 = actor;
}

Projectile* GamePlayState::initProjectile(XMFLOAT3 pos, XMFLOAT3 dir, ProjProp props)
{
	Projectile* proj;
	int nextID = this->newID();

	// Declare Components
	BlockComponent* block;
	PhysicsComponent* phyComp;
	AbilityComponent* abiliComp;

	XMFLOAT3 position = {pos.x + dir.x * props.size, pos.y + dir.y * props.size , pos.z + dir.z * props.size};
	proj = new Projectile(nextID, props.speed, position, dir, OBJECTTYPE::PROJECTILE);

	//input for blockComp
	XMFLOAT3 scale(props.size, props.size, props.size);
	//XMFLOAT3 position = pos;
	XMFLOAT4 tempColor(props.color.x, props.color.y, props.color.z, 255.0f);
	XMFLOAT3 rotation(0, 0, 0);
	block = new BlockComponent(*this, *proj, tempColor, scale, rotation);


	//Add the block to the objects that will be rendered
	this->graphics.push_back(block);
//	this->rio.addGraphics(block);

	//Template of components that are beeing worked on by other users
	//abiliComp = new FireballComponent(*proj, 1);
	//proj->addComponent(abiliComp);

	//Template for Physics
	phyComp = new PhysicsComponent(/*pos, */*proj, 20.0f);
	this->physicsListDynamic.push_back(phyComp);
	
	//Add proj to objectArrays
	this->dynamicObjects.push_back(proj);
	this->projectiles.push_back(proj);

	return proj;
}
