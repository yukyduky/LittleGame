#pragma once
#ifndef GAMEPLAYSTATE_H
#define GAMEPLAYSTATE_H

#include "State.h"
#include <vector>
#include <array>
#include "Commands.h"
#include "RenderInputOrganizer.h"
#include "GraphicsComponent.h"
#include "GameObject.h"
#include "ActorObject.h"
#include "Projectile.h"
#include "Camera.h"
#include "PhysicsComponent.h"
#include "CollisionHandler.h"
#include "FireballComponent.h"
#include <list>
#include "ArenaGlobals.h"
#include "LevelManager.h"



/*
//Defines what a specific space contains
namespace SQUARETYPE {
	enum TYPE { EMPTY, WALL, SPAWN, SIZE };
}

//Defines if a wall runs along the z-axis(VERTICAL) or along the x-axis(HORIZONTAL)
namespace WALLTYPE {
	enum TYPE {VERTICAL, HORIZONTAL, SIZE};
}
*/
class Command;
class InputComponent;

//(Size of cube, color in XMFLOAT3, travelSpeed)
struct ProjProp {
	float size;
	XMFLOAT3 color;
	float speed;

	ProjProp(float s, XMFLOAT3 c, float spd) : size(s), color(c), speed(spd){}
	ProjProp() {}
};


class GamePlayState : public State
{
private:
	static GamePlayState sGamePlayState;
	
	int ID = 0;
	int arenaWidth;
	int arenaDepth;
	CollisionHandler collisionHandler;
	LevelManager lm;
	Camera camera;
	RenderInputOrganizer rio;
	std::vector<std::vector<SQUARETYPE::TYPE>> grid;
	//everything that will exist in this level
	std::vector<GameObject*> staticObjects;
	std::vector<GameObject*> dynamicObjects;
	int staticPhysicsCount = 0;
	std::vector<int> deadObjectsID;

	//All objects that wants to be renederd
	std::vector<GraphicsComponent*> graphics;
	std::array<InputComponent*, 1> playerInput;	// '1' for testing purposes, should be '5'

	//Template to be able to update player1, changed to vector when multiplayer is implemented
	ActorObject* player1;

	Command* selectCommand;

	//std::vector<GameObject*> gameObjectsArray;

	///std::list<PhysicsComponent*> physicsListStatic;
	///std::list<PhysicsComponent*> physicsListDynamic;
	//Array with all active projectiles
	//std::vector<Projectile*> projectiles;
	std::vector<int> deadProjectileID;

	//void updatePhysicsComponents();
	
	void checkCollisions();

public:
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Initialize the 'GamePlayState'.
	*/
	virtual void init();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Cleanup the 'GamePlayState'; freeing memory, default settings, etc.
	*/
	virtual void cleanUp();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Pause the 'GamePlayState'.
	*/
	virtual void pause();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Resume the 'GamePlayState'.
	*/
	virtual void resume();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Handle the events generated in the GamePlayState.
	*/
	virtual void handleEvents(GameManager* gm);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Update the GamePlayState.
	*/
	virtual void update(GameManager* gm);
	
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Render the 'GamePlayState'
	*/
	virtual void render(GameManager* gm);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Get the static instance of the 'GamePlayState'.
	*/
	static GamePlayState* getInstance();


	void initPlayer();

	/*RETURNS THE NEW ID*/
	int newID() { return this->ID++; }

	/*call to shoot projectile*/
	Projectile* initProjectile(XMFLOAT3 pos, XMFLOAT3 dir, ProjProp props);
};

#endif // !GAMEPLAYSTATE_H
