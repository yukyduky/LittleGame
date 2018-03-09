#include "LevelManager.h"
#include "RectangleComponent.h"
#include "LineComponent.h"
#include "BlockComponent.h"
#include "ActorObject.h"
#include "ArenaObject.h"
#include "ArenaGlobals.h"
#include <string>
#include <sstream>

void LevelManager::createFloor(std::vector<std::vector<tileData>>& grid, std::list<GameObject*>& staticObjects, std::list<GraphicsComponent*>& graphics)
{
	//Prepare the matrices and variables
	GameObject* object = nullptr;
	RectangleComponent* rect = nullptr;
	int nextID;
	XMFLOAT3 pos;
	XMVECTOR vec;
	XMMATRIX worldM;
	XMMATRIX rotationM = XMMatrixIdentity();
	XMMATRIX scaleM = XMMatrixScaling(this->arenaWidth * 0.5f, 1.0f, this->arenaDepth * 0.5f);
	XMMATRIX translationM;
	//Prepare the color of the rectangle
	vColor color(1.0f, 1.0f, 1.0f, 0.0f);
	vColor actualColor(0.2f, 0.2f, 0.45f, 0.0f);
	//Create all the squares representing the floor
	
	//Calculate center position of the next grid space
	pos = XMFLOAT3(this->arenaWidth * 0.5f, -0.5f, this->arenaDepth * 0.5f);
	nextID = this->nextID();
	//Create the GameObject and calculate the world matrix
	object = new ArenaObject(nextID, pos);
	vec = XMLoadFloat3(&pos);
	translationM = XMMatrixTranslationFromVector(vec);
	worldM = scaleM * rotationM * translationM;
	//Create the RectangleComponent
	rect = new RectangleComponent(*object, color.r, color.g, color.b, color.a);
	//Give the RectangleComponent to the ArenaObject and set it's world matrix
	object->addComponent(rect);
	object->SETworldMatrix(worldM);
	object->SETrotationMatrix(rotationM);
	object->SETscaleMatrix(scaleM);
	//Push the new ArenaObject and GraphicsComponent into the vector arrays
	
	for (size_t i = 0; i < grid.size(); i++)
	{
		for (size_t j = 0; j < grid[i].size(); j++)
		{
			grid[i][j].baseColor = XMFLOAT3(color.r, color.g, color.b);
			grid[i][j].color = XMFLOAT3(actualColor.r, actualColor.g, actualColor.b);
			grid[i][j].posY = pos.y;
		}
	}
	staticObjects.push_back(object);
	graphics.push_back(rect);
}

void LevelManager::createNeonFloorGrid(std::list<GameObject*>& staticObjects, std::list<GraphicsComponent*>& graphics)
{
	//Calculate the number of vertical and horizontal lines needed
	int nrOfVerticalLines = this->arenaWidth / this->squareSize + 1;
	int nrOfHorizontalLines = this->arenaDepth / this->squareSize + 1;

	XMFLOAT4 color(0.0f / 255.0f, 150.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f);
	//Prepare matrices and variables
	float rectWidth = 1.5f;
	XMMATRIX worldM;
	XMMATRIX translationM;
	XMMATRIX scaleMV = XMMatrixScaling(rectWidth, 0.0f, this->arenaDepth * 0.5f);
	XMMATRIX scaleMH = XMMatrixScaling(this->arenaWidth * 0.5f, 0.0f, rectWidth);
	XMMATRIX rotationM = XMMatrixIdentity();
	
	XMFLOAT3 currentPos;
	XMVECTOR vec;

	//Create the vertical lines
	for (int i = 0; i < nrOfVerticalLines; i++)
	{
		currentPos = XMFLOAT3(static_cast<float>(i * this->squareSize), 0.0f, static_cast<float>(this->arenaDepth) * 0.5f);
		vec = XMLoadFloat3(&currentPos);
		translationM = XMMatrixTranslationFromVector(vec);
		worldM = scaleMV * rotationM * translationM;
		void* test = &graphics;
		this->createARectLine(currentPos, worldM, color, staticObjects, graphics);
	}
	//Create the horizontal lines
	for (int i = 0; i < nrOfHorizontalLines; i++)
	{
		currentPos = XMFLOAT3(static_cast<float>(this->arenaWidth) * 0.5f, 0.0f, i * static_cast<float>(this->squareSize));
		vec = XMLoadFloat3(&currentPos);
		translationM = XMMatrixTranslationFromVector(vec);
		worldM = scaleMH * rotationM * translationM;
		this->createARectLine(currentPos, worldM, color, staticObjects, graphics);
	}
}

void LevelManager::createARectLine(XMFLOAT3& pos, XMMATRIX& worldM, XMFLOAT4& color, std::list<GameObject*>& staticObjects, std::list<GraphicsComponent*>& graphics)
{
	GameObject* object = nullptr;
	RectangleComponent* rect = nullptr;
	int nextID = this->nextID();
	// Create the ArenaObject and the RectangleComponent
	object = new ArenaObject(nextID, pos);
	rect = new RectangleComponent(*object, color.x, color.y, color.z, color.w);
	// Add the RectangleComponent to the ArenaObject and store them in the vector arrays
	object->SETworldMatrix(worldM);
	object->addComponent(rect);
	staticObjects.push_back(object);
	graphics.push_back(rect);
}

void LevelManager::createLevelWalls(int &staticPhysicsCount, std::vector<std::vector<tileData>>& grid, enemySpawnPositions& enemySpawnPos, std::list<GameObject*>& staticObjects, std::list<GraphicsComponent*>& graphics)
{
	//Prepare variables that we will need
	XMMATRIX rotLR = XMMatrixRotationY(XM_PI * 0.5f);
	XMMATRIX rotTB = XMMatrixIdentity();
	XMMATRIX scaleM = XMMatrixScaling(static_cast<float>(this->squareSize) * 0.5f, static_cast<float>(this->wallHeight), static_cast<float>(this->squareSize) * 0.5f);
	XMMATRIX translationM;
	XMMATRIX worldM;
	XMFLOAT4 color(75.0f / 255.0f, 24.0f / 255.0f, 0.5f , 0.0f / 255.0f);
	XMFLOAT3 currPos;
	XMVECTOR vec;
	XMFLOAT2 spawnPos;

	int nrOfVerticalSquares = grid[0].size();
	int nrOfHorizontalSquares = grid.size();
	WallData wData(nrOfVerticalSquares, nrOfHorizontalSquares);
	int caseNr = Locator::getRandomGenerator()->GenerateInt(0, arenaPatterns.GETmaxWallNum());
	// USE THIS if you want to try a SPECIFIC wall pattern
	caseNr = 2;
	this->arenaPatterns.createWallPattern(caseNr, wData);
	
	//Create pillars in the corners
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			currPos = XMFLOAT3((j * (this->arenaWidth - this->squareSize)) + this->squareSize * 0.5f, this->wallHeight * 0.5f, (i * (this->arenaDepth - this->squareSize)) + this->squareSize * 0.5f);
			vec = XMLoadFloat3(&currPos);
			translationM = XMMatrixTranslationFromVector(vec);
			worldM = scaleM * rotTB*  translationM;
			this->createAWall(currPos, worldM, color, staticObjects, graphics);
			grid[j * (grid.size() - 1)][i * (grid[0].size() - 1)].type = SQUARETYPE::TYPE::WALL;
			staticPhysicsCount++;
		}
	}
	//Create left row of walls
	for (int i = 1; i < wData.nrVertical - 1; i++)
	{
		currPos = XMFLOAT3(this->squareSize * 0.5f, this->wallHeight * 0.5f, this->squareSize * 0.5f + i * this->squareSize);
		if (wData.rowL[i] == SQUARETYPE::WALL)
		{
			vec = XMLoadFloat3(&currPos);
			translationM = XMMatrixTranslationFromVector(vec);
			worldM = scaleM * rotTB * translationM;
			this->createAWall(currPos, worldM, color, staticObjects, graphics);
			grid[0][i].type = SQUARETYPE::WALL;
			staticPhysicsCount++;
		}
		else 
		{
			spawnPos.x = currPos.x;
			spawnPos.y = currPos.z;
			enemySpawnPos.west.push_back(spawnPos);
			grid[0][i].type = SQUARETYPE::SPAWN;
		}
	}
	//Create right row of walls
	for (int i = 1; i < wData.nrVertical - 1; i++)
	{
		currPos = XMFLOAT3(this->arenaWidth - this->squareSize * 0.5f, this->wallHeight * 0.5f, this->squareSize * 0.5f + i * this->squareSize);
		if (wData.rowR[i] == SQUARETYPE::WALL)
		{
			vec = XMLoadFloat3(&currPos);
			translationM = XMMatrixTranslationFromVector(vec);
			worldM = scaleM * rotTB * translationM;
			this->createAWall(currPos, worldM, color, staticObjects, graphics);
			grid[nrOfHorizontalSquares - 1][i].type = SQUARETYPE::WALL;
			staticPhysicsCount++;
		}
		else
		{
			spawnPos.x = currPos.x;
			spawnPos.y = currPos.z;
			enemySpawnPos.east.push_back(spawnPos);
			grid[nrOfHorizontalSquares - 1][i].type = SQUARETYPE::SPAWN;
		}
	}
	//Create top row of walls
	for (int i = 1; i < wData.nrHorizontal - 1; i++)
	{
		currPos = XMFLOAT3(this->squareSize * 0.5f + i * this->squareSize, this->wallHeight * 0.5f, this->arenaDepth - this->squareSize * 0.5f);
		if (wData.rowT[i] == SQUARETYPE::WALL)
		{
			vec = XMLoadFloat3(&currPos);
			translationM = XMMatrixTranslationFromVector(vec);
			worldM = scaleM * rotTB * translationM;
			this->createAWall(currPos, worldM, color, staticObjects, graphics);
			grid[i][nrOfVerticalSquares - 1].type = SQUARETYPE::WALL;
			staticPhysicsCount++;
		}
		else
		{
			spawnPos.x = currPos.x;
			spawnPos.y = currPos.z;
			enemySpawnPos.north.push_back(spawnPos);
			grid[i][nrOfVerticalSquares - 1].type = SQUARETYPE::SPAWN;
		}
	}
	//Create bottom row of walls
	for (int i = 1; i < wData.nrHorizontal - 1; i++)
	{
		currPos = XMFLOAT3(this->squareSize * 0.5f + i * this->squareSize, this->wallHeight * 0.5f, this->squareSize * 0.5f);
		if (wData.rowB[i] == SQUARETYPE::WALL)
		{
			vec = XMLoadFloat3(&currPos);
			translationM = XMMatrixTranslationFromVector(vec);
			worldM = scaleM * rotTB * translationM;
			this->createAWall(currPos, worldM, color, staticObjects, graphics);
			grid[i][0].type = SQUARETYPE::WALL;
			staticPhysicsCount++;
		}
		else
		{
			spawnPos.x = currPos.x;
			spawnPos.y = currPos.z;
			enemySpawnPos.south.push_back(spawnPos);
			grid[i][0].type = SQUARETYPE::SPAWN;
		}
	}
}

void LevelManager::createAWall(XMFLOAT3 pos, XMMATRIX& worldM, XMFLOAT4 color, std::list<GameObject*>& staticObjects, std::list<GraphicsComponent*>& graphics)
{
	GameObject* object = nullptr;
	BlockComponent* block = nullptr;
	PhysicsComponent* bSphere = nullptr;
	int nextID = this->nextID();	//Create the new ArenaObject and the new BlockComponent
	object = new ArenaObject(nextID, pos);
	object->setType(OBJECTTYPE::INDESTRUCTIBLE);
	XMFLOAT3 tempScale(1, 1, 1);						// TOBE DELETED
	XMFLOAT3 tempRotation(0, 0, 0);
	block = new BlockComponent(*this->pGPS, *object, color, tempScale, tempRotation);
	bSphere = new PhysicsComponent(*object, static_cast<float>(this->squareSize) * 0.75f);
	XMFLOAT3 bSpherePos = pos;
	bSpherePos.y = this->squareSize * 0.5f;
	bSphere->updateBoundingArea(bSpherePos);
	//Give the world matrix to the new object and store the object and the block in the vector arrays
	object->SETworldMatrix(worldM);
	staticObjects.push_back(object);

	this->nrOfWalls++;
}

int LevelManager::nextID()
{
	return this->tempID++;
}

void LevelManager::setFallPattern(FloorFallData& pattern) {
	int patternNr = Locator::getRandomGenerator()->GenerateInt(0, this->arenaPatterns.GETmaxFloorNum());
	this->arenaPatterns.createFloorPattern(3, pattern);
}

void LevelManager::createFallPatterns(std::vector<FloorFallData>& easy, std::vector<FloorFallData>& medium, std::vector<FloorFallData>& hard) {
	this->arenaPatterns.createEasyFloorPatterns(easy);
	this->arenaPatterns.createMediumFloorPatterns(medium);
	this->arenaPatterns.createHardFloorPatterns(hard);
}

void LevelManager::selectArena() {
	this->arenaPatterns.createArenaData();
}

int LevelManager::initArena(int ID, int &staticPhysicsCount, GamePlayState &pGPS, 
			FloorFallData& pattern, std::vector<std::vector<tileData>>& grid, 
			std::list<GameObject*>& staticObjects, std::list<GameObject*>& dynamicNoCollisionObjects,
			std::list<GameObject*>& dynamicObjects, std::list<GraphicsComponent*>& graphics, 
			std::vector<FloorFallData>& easy, std::vector<FloorFallData>& medium, 
			std::vector<FloorFallData>& hard, enemySpawnPositions& enemySpawnPos)
{
	this->pGPS = &pGPS;
	this->squareSize = ARENADATA::GETsquareSize();
	this->arenaWidth = ARENADATA::GETarenaWidth();
	this->arenaDepth = ARENADATA::GETarenaHeight();
	this->wallHeight = ARENADATA::GETheightOfWall() * ARENADATA::GETsquareSize();
	this->nrOfWalls = 0;
	this->tempID = ID;

	//Create the grid for the level
	grid.resize(this->arenaWidth / this->squareSize);
	for (auto &i : grid) {
		i.resize(this->arenaDepth / this->squareSize);
		for (auto &k : i) {
			k.type = SQUARETYPE::EMPTY;
		}
	}
	
	// createLevelWalls needs to come first
	this->createLevelWalls(staticPhysicsCount, grid, enemySpawnPos, staticObjects, graphics);
	this->createFloor(grid, dynamicNoCollisionObjects, graphics);
	this->createNeonFloorGrid(staticObjects, graphics);
	this->setFallPattern(pattern);
	this->createFallPatterns(easy, medium, hard);

	return this->tempID;
}

void LevelManager::changeTileStateFromPos(XMFLOAT2 pos, OBJECTSTATE::TYPE state, std::vector<std::vector<tileData>>& grid, std::list<GameObject*>& staticObjects, std::list<GameObject*>& dynamicObjects)
{
	Index index = this->findTileIndexFromPos(pos);
//	grid[(int)index.x][(int)index.y].ptr->setState(state);


//	int ID = grid[(int)index.x][(int)index.y].ptr->getID();
	switch (state)
	{
	case OBJECTSTATE::TYPE::TFALLING : 
		for (std::list<GameObject*>::iterator it = staticObjects.begin(); it != staticObjects.end(); it++) {
//			if ((*it)->getID() == ID) {
//				dynamicObjects.push_back((*it));
//				staticObjects.erase(it);
				it--;
//			}
		}
		break;
	default:
		break;
	}
}

void LevelManager::changeTileStateFromIndex(int& x, int& y, OBJECTSTATE::TYPE& state, std::vector<std::vector<tileData>>& grid, std::list<GameObject*>& staticObjects, std::list<GameObject*>& dynamicObjects)
{
//	int ID = grid[x][y].ptr->getID();
	int ID = -1;
	std::list<GameObject*>::iterator it = staticObjects.begin();
	int test = 0;

	if (state == OBJECTSTATE::TYPE::TFALLING) {
		test++;
	}

	switch (state)
	{
	case OBJECTSTATE::TYPE::TFALLING:
		while (it != staticObjects.end()) {
			if ((*it)->getID() == ID) {
				(*it)->setState(state);
				dynamicObjects.splice(dynamicObjects.end(), staticObjects, it);
				break;
			}
			it++;
		}
		break;
	case OBJECTSTATE::TYPE::RECOVER:
		while (it != staticObjects.end()) {
			if ((*it)->getID() == ID) {
				(*it)->setState(state);
				dynamicObjects.push_back((*it));
				break;
			}
			it++;
		}
		break;
	default:
		break;
	}
}

void LevelManager::checkTileStatusFromPos(XMFLOAT3 pos, std::vector<std::vector<tileData>>& grid, TILESTATE::STATE& state)
{
	state = grid[static_cast<size_t>(pos.x / ARENADATA::GETsquareSize())][static_cast<size_t>(pos.z / ARENADATA::GETsquareSize())].state;
}

Index LevelManager::findTileIndexFromPos(XMFLOAT2 pos)
{
	Index index;
	index.x = pos.x / this->squareSize;
	index.y = pos.y / this->squareSize;

	return index;
}

void LevelManager::createGenerator(int ID, std::vector<std::vector<tileData>>& grid, std::list<GameObject*>& dynamicObjects, std::list<GraphicsComponent*>& graphics, std::vector<Index>& genIndex)
{
	Index index;
	do {
		index.x = Locator::getRandomGenerator()->GenerateInt(1, grid.size() - 2);
		index.y = Locator::getRandomGenerator()->GenerateInt(1, grid[0].size() - 2);
	} while (grid[index.x][index.y].state == TILESTATE::GENERATOR);
	
	float squareSize = ARENADATA::GETsquareSize();
	XMFLOAT3 genPos = XMFLOAT3(squareSize * 0.5f + index.x * squareSize, -squareSize * 0.5f, squareSize * 0.5f + index.y * squareSize);
	int genType = Locator::getRandomGenerator()->GenerateInt(0, GENERATOR::TYPE::OVERCHARGED);
	grid[index.x][index.y].state = TILESTATE::GENERATOR;
	XMFLOAT4 genColor;

	switch (genType)
	{
	case GENERATOR::TYPE::OVERHEATED:
		genColor = XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f);
		grid[index.x][index.y].genEffect = TILESTATE::THEATED;
		break;
	case GENERATOR::TYPE::COOLED:
		genColor = XMFLOAT4(0.0f, 0.0f, 1.0f, 1.0f);
		grid[index.x][index.y].genEffect = TILESTATE::TCOOLED;
		break;
	case GENERATOR::TYPE::OVERCHARGED:
		genColor = XMFLOAT4(1.0f, 1.0f, 0.0f, 1.0f);
		grid[index.x][index.y].genEffect = TILESTATE::TELECTRIFIED;
		break;
	default:
		break;
	}
	genIndex.push_back(index);
	
	GameObject* object = nullptr;
	BlockComponent* block = nullptr;
	PhysicsComponent* bSphere = nullptr;
	object = new ActorObject(ID, 0.0f, 0.0f, genPos, this->pGPS, OBJECTTYPE::ENEMY, 500.0f);
	object->setType(OBJECTTYPE::GENERATOR);
	object->setState(OBJECTSTATE::TYPE::GENERATORRISING);
	XMFLOAT3 scale(this->squareSize * 0.5f, this->squareSize * 0.5f, this->squareSize * 0.5f);						// TOBE DELETED
	XMFLOAT3 rotation(0, 0, 0);
	block = new BlockComponent(*this->pGPS, *object, genColor, scale, rotation);
	bSphere = new PhysicsComponent(*object, static_cast<float>(this->squareSize) * 0.75f);
	XMFLOAT3 bSpherePos = genPos;
	bSpherePos.y = this->squareSize * 0.5f;
	bSphere->updateBoundingArea(bSpherePos);
	//Give the world matrix to the new object and store the object and the block in the vector arrays
	dynamicObjects.push_back(object);
}

void LevelManager::clean() {

}
