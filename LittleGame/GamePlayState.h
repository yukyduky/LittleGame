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




//Defines what a specific space contains
namespace SQUARETYPE {
	enum TYPE { EMPTY, WALL, SPAWN, SIZE };
}

//Defines if a wall runs along the z-axis(VERTICAL) or along the x-axis(HORIZONTAL)
namespace WALLTYPE {
	enum TYPE {VERTICAL, HORIZONTAL, SIZE};
}

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
	std::array<int*, 0> grid;
	int arenaGrid[ARENAWIDTH/ARENASQUARESIZE][ARENAHEIGHT/ARENASQUARESIZE];
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

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Calls createArenaFloor
	2. Calls createArenaWalls
	3.
	*/
	void initArena();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Creates a new GameObject with a new RectangleComponent.
	2. Pushes the new GameObject into the arenaObject vector.
	*/
	void createArenaFloor(); 

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Calculates the amount of vertical lines and horizontal lines the arena need.
	2. Prepares the worldMatrix for the next line.
	3. Creates all the veritcal lines by calling createLine function.
	4. Creates all the horizontal lines by calling createLine function.
	*/
	void createArenaNeonGrid();

	void createRectLine(XMFLOAT3 pos, XMMATRIX wMatrix, XMFLOAT4 color);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Creates the new GameObject and the new LineComponent
	2. Gives the world matrix to the LineComponent.
	3. Gives the LineComponent to the new GameObject.
	4. Pushes the new GameObject into the arenaObjects vector.
	5. Pushes the new LineComponent into the graphics vector.
	*/
	void createLine(XMFLOAT3 pos, XMMATRIX wMatrix, XMFLOAT4 startColor, XMFLOAT4 endColor);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Calculates number of walls in Left, Right, Top and Bottom row.
	2. Calculates the position of the wall we want to create.
	3. Checks if the new positions should be a wall or a spawn location.
	4. Creates the worldMatrix for the new wall.
	5. Calls createAWall() function.
	6. Sets the correct type of the squares in the arenaGrid.
	7. TODO: Implement a randomize function for the spawn locations and make corner static corner pillars.
	*/
	void createArenaWalls();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Creates a GameObject and a BlockComponent.
	2. The ID for the new object is fetched from the arenaGrid vector.
	3. Gives the worldMatrix to the BlockComponent.
	4. Gives the BlockComponent to the GameObject.
	5. Pushes the new GameObject into the arenaObjects vector.
	6. PS: REMEMBER to set the grid area of the new wall to the right type.
	*/
	void createAWall(XMFLOAT3 pos, XMMATRIX wMatrix, XMFLOAT4 color, WALLTYPE::TYPE wType);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Sets the square at the given index to the given type.
	*/
	void SETsquareType(XMFLOAT2 index, SQUARETYPE::TYPE type);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Find the index of a square at a given position.
	2. The function does not care about the height of the position you send in.
	3. Returns XMFLOAT2 where the x-value is the x-index and y-value is the z-index.
	4. We call it z-index because the depth in the grid is along the z-axis.
	*/
	XMFLOAT2 findGridIndexFromPosition(XMFLOAT3 pos);

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Creates the ActorObject and all it's matrices that will represent the player.
	2. Creates a BlockComponent that will represent the players body.
	*/
	void initPlayer();
};

#endif // !GAMEPLAYSTATE_H
