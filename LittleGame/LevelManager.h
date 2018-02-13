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
	GameObject* ptr;

	tileData() {};

	tileData(SQUARETYPE::TYPE type) {
		this->type = type;
	}
};


class LevelManager
{
private:
	GamePlayState * pGPS;
	FFPattern ffp;

	int arenaWidth;
	int arenaDepth;
	int squareSize;
	int wallHeight;
	int tempID;
	int nrOfWalls;
	

	void createFloor(std::vector<std::vector<tileData>>& grid, std::vector<GameObject*>& staticObjects, std::vector<GraphicsComponent*>& graphics);
	void createNeonFloorGrid(std::vector<GameObject*>& staticObjects, std::vector<GraphicsComponent*>& graphics);
	void createARectLine(XMFLOAT3 pos, XMMATRIX worldM, XMFLOAT4 color, std::vector<GameObject*>& staticObjects, std::vector<GraphicsComponent*>& graphics);
	void createLevelWalls(int &staticPhysicsCount, std::vector<std::vector<tileData>>& grid, std::vector<GameObject*>& staticObjects, std::vector<GraphicsComponent*>& graphics);
	void createAWall(XMFLOAT3 pos, XMMATRIX worldM, XMFLOAT4 color, std::vector<GameObject*>& staticObjects, std::vector<GraphicsComponent*>& graphics);
	int nextID();
	XMFLOAT2 findTileIndexFromPos(XMFLOAT2 pos);
	void setFallPattern(FloorFallData& pattern);
	//void randomize();

public:
	int initArena(int ID, int &staticPhysicsCount, int width, int depth, GamePlayState &pGPS, FloorFallData& pattern, std::vector<std::vector<tileData>>& grid, std::vector<GameObject*>& staticObjects, std::vector<GameObject*>& dynamicObjects, std::vector<GraphicsComponent*>& graphics);
	void changeTileStateFromPos(XMFLOAT2 pos, OBJECTSTATE::TYPE state, std::vector<std::vector<tileData>>& grid, std::vector<GameObject*>& staticObjects, std::vector<GameObject*>& dynamicObjects);
	void changeTileStateFromIndex(XMFLOAT2 index, OBJECTSTATE::TYPE state, std::vector<std::vector<tileData>>& grid, std::vector<GameObject*>& staticObjects, std::vector<GameObject*>& dynamicObjects);
	OBJECTSTATE::TYPE checkTileStateFromPos(XMFLOAT3 pos, std::vector<std::vector<tileData>>& grid);
	void recoverFloor(int ID, Index index, std::vector<std::vector<tileData>>& grid, std::vector<GameObject*>& noCollisionDynamicObjects, std::vector<GraphicsComponent*>& graphics);
};



#endif