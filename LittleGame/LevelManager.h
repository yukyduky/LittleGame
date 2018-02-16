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


class LevelManager
{
private:
	GamePlayState * pGPS;

	int arenaWidth;
	int arenaDepth;
	int squareSize;
	int wallHeight;
	int tempID;
	

	void createFloor(std::vector<std::vector<SQUARETYPE::TYPE>>& grid, std::list<GameObject*>& staticObjects, std::list<GraphicsComponent*>& graphics);
	void createNeonFloorGrid(std::list<GameObject*>& staticObjects, std::list<GraphicsComponent*>& graphics);
	void createARectLine(XMFLOAT3 pos, XMMATRIX worldM, XMFLOAT4 color, std::list<GameObject*>& staticObjects, std::list<GraphicsComponent*>& graphics);
	void createLevelWalls(int &staticPhysicsCount, std::vector<std::vector<SQUARETYPE::TYPE>>& grid, std::list<GameObject*>& staticObjects, std::list<GraphicsComponent*>& graphics);
	void createAWall(XMFLOAT3 pos, XMMATRIX worldM, XMFLOAT4 color, std::list<GameObject*>& staticObjects, std::list<GraphicsComponent*>& graphics);
	int nextID();


	//void randomize();

public:
	int initArena(int ID, int &staticPhysicsCount, int width, int depth, GamePlayState &pGPS, std::vector<std::vector<SQUARETYPE::TYPE>>& grid, std::list<GameObject*>& staticObjects, std::list<GraphicsComponent*>& graphics);


};



#endif