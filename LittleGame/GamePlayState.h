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
#include "Camera.h"
#include "PhysicsComponent.h"
#include "CollisionHandler.h"
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

class GamePlayState : public State
{
private:
	static GamePlayState sGamePlayState;
	
	CollisionHandler collisionHandler;
	LevelManager lm;
	Camera camera;
	RenderInputOrganizer rio;
	std::vector<std::vector<SQUARETYPE::TYPE>> grid;
	std::vector<GameObject*> arenaObjects;

	std::vector<GraphicsComponent*> graphics;
	std::vector<GraphicsComponent*> blocks;
	std::array<InputComponent*, 1> playerInput;	// '1' for testing purposes, should be '5'

	Command* selectCommand;

	std::vector<GameObject*> gameObjectsArray;

	std::list<PhysicsComponent*> physicsListStatic;
	std::list<PhysicsComponent*> physicsListDynamic;

	void updatePhysicsComponents();
	
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
};

#endif // !GAMEPLAYSTATE_H
