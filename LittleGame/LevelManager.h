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
#include "ArenaPatterns.h"

using namespace DirectX::SimpleMath;
class GamePlayState;

//Defines what a specific space contains
namespace SQUARETYPE {
	enum TYPE { EMPTY, WALL, SPAWN, SIZE };
}

namespace TILESTATUS {
	enum STATUS {IDLE, HOLE, SIZE};
}

namespace TILESTATE {
	enum STATE {
		ACTIVE, TFALLING, FALLING, HOLE, RECOVERING, FLASH,
		GENERATOR, ELECTRIFIED, HEATED, COOLED, TELECTRIFIED,
		THEATED, TCOOLED, SIZE
	};
}

//Defines if a wall runs along the z-axis(VERTICAL) or along the x-axis(HORIZONTAL)
namespace WALLTYPE {
	enum TYPE { VERTICAL, HORIZONTAL, SIZE };
}

namespace EFFECTSTATUS {
	enum EFFECT{ IDLE, ELECTRIFIED, HEATED, COOLED, TELECTRIFIED, THEATED, TCOOLED, SIZE };
}

namespace GENERATOR {
	enum TYPE { OVERHEATED, COOLED, OVERCHARGED, SIZE};
}

struct tileData {
	SQUARETYPE::TYPE type;

	//Nya som Dew ska använda
	XMFLOAT3 baseColor;
	XMFLOAT3 color;
//	float basePosY;
//	float realPosY;
	float posY;
	TILESTATUS::STATUS status;
	double counter;
	double stateTime;
	double coolDownTime;
	double chargeTime;
//	double coolDownCounter;
//	double chargeCounter;
	TILESTATE::STATE state;
	

//	bool occupiedByGenerator;
	TILESTATE::STATE genEffect;
	EFFECTSTATUS::EFFECT currentEffect;
	std::vector<Index> genPattern;

	tileData() 
	{ 
		this->state = TILESTATE::STATE::ACTIVE;
		this->type = SQUARETYPE::TYPE::EMPTY;
		this->status = TILESTATUS::STATUS::IDLE;
		this->currentEffect = EFFECTSTATUS::EFFECT::IDLE;
//		this->occupiedByGenerator = false;
		this->coolDownTime = 6.0;
		this->chargeTime = 1.5;
		this->stateTime = 5.0;
		this->counter = 0.0;
//		this->coolDownCounter = 0.0;
//		this->chargeCounter = 0.0;
	};
	tileData(SQUARETYPE::TYPE type) {
		this->state = TILESTATE::STATE::ACTIVE;
		this->type = type;
		this->status = TILESTATUS::STATUS::IDLE;
		this->currentEffect = EFFECTSTATUS::EFFECT::IDLE;
//		this->occupiedByGenerator = false;
		this->coolDownTime = 6.0;
		this->chargeTime = 1.5;
		this->stateTime = 5.0;
		this->counter = 0.0;
//		this->coolDownCounter = 0.0;
//		this->chargeCounter = 0.0;
	}
};

struct enemySpawnPositions {
	std::vector<XMFLOAT2> north;
	std::vector<XMFLOAT2> west;
	std::vector<XMFLOAT2> south;
	std::vector<XMFLOAT2> east;

	void cleanUp() {
		this->north.clear();
		this->west.clear();
		this->south.clear();
		this->east.clear();
	}
};

class LevelManager
{
private:
	GamePlayState * pGPS = nullptr;
	ArenaPatterns arenaPatterns;

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
	void createARectLine(XMFLOAT3& pos, XMMATRIX& worldM, XMFLOAT4& color, std::list<GameObject*>& staticObjects, std::list<GraphicsComponent*>& graphics);
	/*
	1. Creates all the outer walls of the level by calling createAWall function for each wall.
	*/
	void createLevelWalls(int &staticPhysicsCount, std::vector<std::vector<tileData>>& grid, enemySpawnPositions& enemySpawnPos, std::list<GameObject*>& staticObjects, std::list<GraphicsComponent*>& graphics);
	void createAWall(XMFLOAT3 pos, XMMATRIX& worldM, XMFLOAT4 color, std::list<GameObject*>& staticObjects, std::list<GraphicsComponent*>& graphics);
	int nextID();

	
	/*--------<INFORMATION>--------
	1. Creates the fall pattern for the floor by calling the createPattern function in FloorFallPattern
	*/
	void setFallPattern(FloorFallData& pattern);

	void LevelManager::createFallPatterns(std::vector<FloorFallData>& easy, std::vector<FloorFallData>& medium, std::vector<FloorFallData>& hard);

public:
	void selectArena();
	/*--------<INFORMATION>--------
	1. Creates the arena by calling the following private functions
		createLevelWalls,
		createFloor,
		createNeonFloorGrid,
		setFallPattern.
	2. returns the latest used ID.
	*/
	int initArena(int ID, int &staticPhysicsCount, GamePlayState &pGPS, FloorFallData& pattern, std::vector<std::vector<tileData>>& grid, std::list<GameObject*>& staticObjects, std::list<GameObject*>& dynamicNoCollisionObjects, std::list<GameObject*>& dynamicObjects, std::list<GraphicsComponent*>& graphics, std::vector<FloorFallData>& easy, std::vector<FloorFallData>& medium, std::vector<FloorFallData>& hard, enemySpawnPositions& enemySpawnPos);
	/*--------<INFORMATION>--------
	1. Changes the state of a floor tile from a given position.
	*/
	void changeTileStateFromPos(XMFLOAT2 pos, OBJECTSTATE::TYPE state, std::vector<std::vector<tileData>>& grid, std::list<GameObject*>& staticObjects, std::list<GameObject*>& dynamicObjects);
	/*--------<INFORMATION>--------
	1. Changes the state of a floor tile from a given grid index.
	*/
	void changeTileStateFromIndex(int& x, int& y, OBJECTSTATE::TYPE& state, std::vector<std::vector<tileData>>& grid, std::list<GameObject*>& staticObjects, std::list<GameObject*>& dynamicObjects);
	/*--------<INFORMATION>--------
	1. Returns the state of a floor tile from a given position.
	*/
	void checkTileStatusFromPos(XMFLOAT3 pos, std::vector<std::vector<tileData>>& grid, TILESTATE::STATE& state);

	/*--------<INFORMATION>--------
	1. Returns the grid index pos for a given position.
	*/
	XMFLOAT2 findTileIndexFromPos(XMFLOAT2 pos);


	void createGenerator(int ID, std::vector<std::vector<tileData>>& grid, std::list<GameObject*>& dynamicObjects, std::list<GraphicsComponent*>& graphics, std::vector<Index>& genIndex);

	void clean();
};



#endif