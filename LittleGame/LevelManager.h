#pragma once
#ifndef LEVELMANAGER_H_
#define LEVELMANAGER_H_

#include <vector>
#include <d3d11.h>
#include <DirectXMath.h>
#include <SimpleMath.h>
#include "GameObject.h"
#include "GraphicsComponent.h"
#include "PhysicsComponent.h"
#include "FloorFallPatterns.h"

using namespace DirectX::SimpleMath;
class GamePlayState;

//Defines what a specific space contains
namespace SQUARETYPE {
	enum TYPE { EMPTY, WALL, SPAWN, SIZE };
}

//Defines if a wall runs along the z-axis(VERTICAL) or along the x-axis(HORIZONTAL)
namespace WALLTYPE {
	enum TYPE { VERTICAL, HORIZONTAL, SIZE };
}

struct tileData {
	SQUARETYPE::TYPE type;
	GameObject* ptr = nullptr;

	tileData() {};

	tileData(SQUARETYPE::TYPE type) {
		this->type = type;
	}
};


class LevelManager
{
private:
	GamePlayState * pGPS = nullptr;
	FFPattern ffp;

	int arenaWidth = 0;
	int arenaDepth = 0;
	int squareSize = 0;
	int wallHeight = 0;
	int tempID = 0;
	int nrOfWalls = 0;
	
	/*--------<INFORMATION>--------
	1. Creates all the RectangleComponents representing the arena floor.
	*/
	void createFloor(std::vector<std::vector<tileData>>& grid, std::list<GameObject*>& staticObjects, std::list<GraphicsComponent*>& graphics);
	/*--------<INFORMATION>--------
	1. Creates all the RectangleComponents representing the neon grid on the arena floor 
		by calling createARectLine function for each line.
	*/
	void createNeonFloorGrid(std::list<GameObject*>& staticObjects, std::list<GraphicsComponent*>& graphics);
	void createARectLine(XMFLOAT3 pos, XMMATRIX worldM, XMFLOAT4 color, std::list<GameObject*>& staticObjects, std::list<GraphicsComponent*>& graphics);
	/*
	1. Creates all the outer walls of the level by calling createAWall function for each wall.
	*/
	void createLevelWalls(int &staticPhysicsCount, std::vector<std::vector<tileData>>& grid, std::list<GameObject*>& staticObjects, std::list<GraphicsComponent*>& graphics);
	void createAWall(XMFLOAT3 pos, XMMATRIX worldM, XMFLOAT4 color, std::list<GameObject*>& staticObjects, std::list<GraphicsComponent*>& graphics);
	int nextID();

	/*--------<INFORMATION>--------
	1. Returns the grid index pos for a given position.
	*/
	XMFLOAT2 findTileIndexFromPos(XMFLOAT2 pos);
	/*--------<INFORMATION>--------
	1. Creates the fall pattern for the floor by calling the createPattern function in FloorFallPattern
	*/
	void setFallPattern(FloorFallData& pattern);

public:
	/*--------<INFORMATION>--------
	1. Creates the arena by calling the following private functions
		createLevelWalls,
		createFloor,
		createNeonFloorGrid,
		setFallPattern.
	2. returns the latest used ID.
	*/
	int initArena(int ID, int &staticPhysicsCount, int width, int depth, GamePlayState &pGPS, FloorFallData& pattern, std::vector<std::vector<tileData>>& grid, std::list<GameObject*>& staticObjects, std::list<GameObject*>& dynamicObjects, std::list<GraphicsComponent*>& graphics);
	/*--------<INFORMATION>--------
	1. Changes the state of a floor tile from a given position.
	*/
	void changeTileStateFromPos(XMFLOAT2 pos, OBJECTSTATE::TYPE state, std::vector<std::vector<tileData>>& grid, std::list<GameObject*>& staticObjects, std::list<GameObject*>& dynamicObjects);
	/*--------<INFORMATION>--------
	1. Changes the state of a floor tile from a given grid index.
	*/
	void changeTileStateFromIndex(XMFLOAT2 index, OBJECTSTATE::TYPE state, std::vector<std::vector<tileData>>& grid, std::list<GameObject*>& staticObjects, std::list<GameObject*>& dynamicObjects);
	/*--------<INFORMATION>--------
	1. Returns the state of a floor tile from a given position.
	*/
	OBJECTSTATE::TYPE checkTileStateFromPos(XMFLOAT3 pos, std::vector<std::vector<tileData>>& grid);

	void clean();
};



#endif