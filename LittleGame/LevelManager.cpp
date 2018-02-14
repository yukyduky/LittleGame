#include "LevelManager.h"
#include "RectangleComponent.h"
#include "LineComponent.h"
#include "BlockComponent.h"
#include "ActorObject.h"
#include "ArenaObject.h"

void LevelManager::createFloor(std::vector<std::vector<tileData>>& grid, std::vector<GameObject*>& staticObjects, std::vector<GraphicsComponent*>& graphics)
{
	//Prepare the matrices and variables
	GameObject* object;
	RectangleComponent* rect;
	int nextID;
	XMFLOAT3 pos;
	XMVECTOR vec;
	XMMATRIX worldM;
	XMMATRIX rotationM = XMMatrixIdentity();
	XMMATRIX scaleM = XMMatrixScaling(this->squareSize / 2, 0, this->squareSize / 2);
	XMMATRIX translationM;
	//Prepare the color of the rectangle
	vColor color(0.0f / 255.0f, 200.0f / 255.0f, 255.0f / 255.0f, 50.0f / 255.0f);
	//Create all the squares representing the floor
	for (int i = 0; i < grid.size(); i++)
	{
		for (int j = 0; j < grid[i].size(); j++)
		{
			//Calculate center position of the next grid space
			pos = XMFLOAT3(this->squareSize / 2.0f + i * this->squareSize, -0.5f, this->squareSize /2.0f + j * this->squareSize);
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
			grid[i][j].ptr = object;
			staticObjects.push_back(object);
			graphics.push_back(rect);
		}
	}
}

void LevelManager::createNeonFloorGrid(std::vector<GameObject*>& staticObjects, std::vector<GraphicsComponent*>& graphics)
{
	//Calculate the number of vertical and horizontal lines needed
	int nrOfVerticalLines = this->arenaWidth / this->squareSize + 1;
	int nrOfHorizontalLines = this->arenaDepth / this->squareSize + 1;

	XMFLOAT4 color(0.0f / 255.0f, 150.0f / 255.0f, 255.0f / 255.0f, 255.0f / 255.0f);
	//Prepare matrices and variables
	float rectWidth = 1.5f;
	XMMATRIX worldM;
	XMMATRIX translationM;
	XMMATRIX scaleMV = XMMatrixScaling(rectWidth, 0.0f, this->arenaDepth * 0.5);
	XMMATRIX scaleMH = XMMatrixScaling(this->arenaWidth / 2.0f, 0.0f, rectWidth);
	XMMATRIX rotationM = XMMatrixIdentity();
	
	XMFLOAT3 currentPos;
	XMVECTOR vec;
	//Create the vertical lines
	for (int i = 0; i < nrOfVerticalLines; i++)
	{
		currentPos = XMFLOAT3(i * this->squareSize, 0.0f, this->arenaDepth * 0.5);
		vec = XMLoadFloat3(&currentPos);
		translationM = XMMatrixTranslationFromVector(vec);
		worldM = scaleMV * rotationM * translationM;
		this->createARectLine(currentPos, worldM, color, staticObjects, graphics);
	}
	//Create the horizontal lines
	for (int i = 0; i < nrOfHorizontalLines; i++)
	{
		currentPos = XMFLOAT3(this->arenaWidth * 0.5, 0.0f, i * this->squareSize);
		vec = XMLoadFloat3(&currentPos);
		translationM = XMMatrixTranslationFromVector(vec);
		worldM = scaleMH * rotationM * translationM;
		this->createARectLine(currentPos, worldM, color, staticObjects, graphics);
	}
}

void LevelManager::createARectLine(XMFLOAT3 pos, XMMATRIX worldM, XMFLOAT4 color, std::vector<GameObject*>& staticObjects, std::vector<GraphicsComponent*>& graphics)
{
	GameObject* object;
	RectangleComponent* rect;
	int nextID = this->nextID();
	//Create the ArenaObject and the RectangleComponent
	object = new ArenaObject(nextID, pos);
	rect = new RectangleComponent(*object, color.x, color.y, color.z, color.w);
	//Add the RectangleComponent to the ArenaObject and store them in the vector arrays
	object->SETworldMatrix(worldM);
	object->addComponent(rect);
	staticObjects.push_back(object);
	graphics.push_back(rect);
}

void LevelManager::createLevelWalls(int &staticPhysicsCount, std::vector<std::vector<tileData>>& grid, std::vector<GameObject*>& staticObjects, std::vector<GraphicsComponent*>& graphics)
{
	//Prepare variables that we will need
//	int nextID = this->nextID();
	XMMATRIX rotLR = XMMatrixRotationY(XM_PI * 0.5);
	XMMATRIX rotTB = XMMatrixIdentity();
	XMMATRIX scaleM = XMMatrixScaling(this->squareSize * 0.5, this->wallHeight, this->squareSize * 0.5);
	XMMATRIX translationM;
	XMMATRIX worldM;
	XMFLOAT4 color(155.0f / 255.0f, 48.0f / 255.0f, 255.0f / 255.0f, 0.0f / 255.0f);
	XMFLOAT3 currPos;
	XMVECTOR vec;
	XMFLOAT2 posIndex;
	XMFLOAT3 temp;
	int nrOfVerticalSquares = grid[0].size();
	int nrOfHorizontalSquares = grid.size();
	
	//Create pillars in the corners
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < 2; j++)
		{
			currPos = XMFLOAT3((j * (this->arenaWidth - this->squareSize)) + this->squareSize * 0.5, this->wallHeight * 0.5, (i * (this->arenaDepth - this->squareSize)) + this->squareSize * 0.5);
			vec = XMLoadFloat3(&currPos);
			translationM = XMMatrixTranslationFromVector(vec);
			worldM = scaleM * rotTB*  translationM;
			this->createAWall(currPos, worldM, color, staticObjects, graphics);
			grid[j * (grid.size() - 1)][i * (grid[0].size() - 1)].type = SQUARETYPE::TYPE::WALL;
			staticPhysicsCount++;
		}
	}
	
	int* rowLR = new int[nrOfVerticalSquares];
	/*randomize numbers between 0 and 1 for every square in leftRow*/
	// this is just for test
	for (int i = 0; i < nrOfVerticalSquares; i++)
	{
		rowLR[i] = SQUARETYPE::WALL;
	}
	rowLR[nrOfVerticalSquares / 2] = SQUARETYPE::SPAWN;
	rowLR[nrOfVerticalSquares / 2 - 1] = SQUARETYPE::SPAWN;


	int* rowTB = new int[nrOfHorizontalSquares];
	for (int i = 0; i < nrOfHorizontalSquares; i++)
	{
		rowTB[i] = SQUARETYPE::WALL;
	}
	rowTB[nrOfHorizontalSquares / 2] = SQUARETYPE::SPAWN;
	rowTB[nrOfHorizontalSquares / 2 - 1] = SQUARETYPE::SPAWN;
	
	//Create left row of walls
	for (int i = 1; i < nrOfVerticalSquares - 1; i++)
	{
		if (rowLR[i] == SQUARETYPE::WALL)
		{
			currPos = XMFLOAT3(this->squareSize * 0.5, this->wallHeight * 0.5, this->squareSize * 0.5 + i * this->squareSize);
			vec = XMLoadFloat3(&currPos);
			translationM = XMMatrixTranslationFromVector(vec);
			worldM = scaleM * rotTB * translationM;
			this->createAWall(currPos, worldM, color, staticObjects, graphics);
			grid[0][i].type = SQUARETYPE::WALL;
			staticPhysicsCount++;
		}
		else 
		{
			grid[0][i].type = SQUARETYPE::SPAWN;
		}
	}
	//Create right row of walls
	for (int i = 1; i < nrOfVerticalSquares - 1; i++)
	{
		if (rowLR[i] == SQUARETYPE::WALL)
		{
			currPos = XMFLOAT3(this->arenaWidth - this->squareSize * 0.5, this->wallHeight * 0.5, this->squareSize * 0.5 + i * this->squareSize);
			vec = XMLoadFloat3(&currPos);
			translationM = XMMatrixTranslationFromVector(vec);
			worldM = scaleM * rotTB * translationM;
			this->createAWall(currPos, worldM, color, staticObjects, graphics);
			grid[nrOfHorizontalSquares - 1][i].type = SQUARETYPE::WALL;
			staticPhysicsCount++;
		}
		else
		{
			grid[nrOfHorizontalSquares - 1][i].type = SQUARETYPE::SPAWN;
		}
	}
	//Create top row of walls
	for (int i = 1; i < nrOfHorizontalSquares - 1; i++)
	{
		if (rowTB[i] == SQUARETYPE::WALL)
		{
			currPos = XMFLOAT3(this->squareSize * 0.5 + i * this->squareSize, this->wallHeight * 0.5, this->arenaDepth - this->squareSize * 0.5);
			vec = XMLoadFloat3(&currPos);
			translationM = XMMatrixTranslationFromVector(vec);
			worldM = scaleM * rotTB * translationM;
			this->createAWall(currPos, worldM, color, staticObjects, graphics);
			grid[i][nrOfVerticalSquares - 1].type = SQUARETYPE::WALL;
			staticPhysicsCount++;
		}
		else
		{
			grid[i][nrOfVerticalSquares - 1].type = SQUARETYPE::SPAWN;
		}
	}
	//Create bottom row of walls
	for (int i = 1; i < nrOfHorizontalSquares - 1; i++)
	{
		if (rowTB[i] == SQUARETYPE::WALL)
		{
			currPos = XMFLOAT3(this->squareSize * 0.5 + i * this->squareSize, this->wallHeight * 0.5, this->squareSize * 0.5);
			vec = XMLoadFloat3(&currPos);
			translationM = XMMatrixTranslationFromVector(vec);
			worldM = scaleM * rotTB * translationM;
			this->createAWall(currPos, worldM, color, staticObjects, graphics);
			grid[i][0].type = SQUARETYPE::WALL;
			staticPhysicsCount++;
		}
		else
		{
			grid[i][0].type = SQUARETYPE::SPAWN;
		}
	}
	delete rowTB;
	delete rowLR;
}

void LevelManager::createAWall(XMFLOAT3 pos, XMMATRIX worldM, XMFLOAT4 color, std::vector<GameObject*>& staticObjects, std::vector<GraphicsComponent*>& graphics)
{
	GameObject* object;
	BlockComponent* block;
	PhysicsComponent* bSphere;
	int nextID = this->nextID();
	//Create the new ArenaObject and the new BlockComponent
	object = new ArenaObject(nextID, pos);
	object->setType(OBJECTTYPE::INDESTRUCTIBLE);
	XMFLOAT3 tempScale(1, 1, 1);						// TOBE DELETED
	XMFLOAT3 tempRotation(0, 0, 0);
	block = new BlockComponent(*this->pGPS, *object, color, tempScale, tempRotation);
	bSphere = new PhysicsComponent(*object, this->squareSize * 0.5);
	XMFLOAT3 bSpherePos = pos;
	bSpherePos.y = this->squareSize * 0.5;
	bSphere->updateBoundingArea(bSpherePos);
	//Give the world matrix to the new object and store the object and the block in the vector arrays
	object->SETworldMatrix(worldM);
	staticObjects.push_back(object);
	graphics.push_back(block);
	this->nrOfWalls++;
}

int LevelManager::nextID()
{
	return this->tempID++;
}

XMFLOAT2 LevelManager::findTileIndexFromPos(XMFLOAT2 pos)
{
	XMFLOAT2 index = XMFLOAT2(0.0f, 0.0f);
	index.x = pos.x / this->squareSize;
	index.y = pos.y / this->squareSize;

	return index;
}

void LevelManager::setFallPattern(FloorFallData& pattern) {
	int patternNr = Locator::getRandomGenerator()->GenerateInt(0, this->ffp.GETmaxNum());
	this->ffp.createPattern(patternNr, pattern);
}

int LevelManager::initArena(int ID, int &staticPhysicsCount, int width, int depth, GamePlayState &pGPS, FloorFallData& pattern, std::vector<std::vector<tileData>>& grid, std::vector<GameObject*>& staticObjects, std::vector<GameObject*>& dynamicObjects, std::vector<GraphicsComponent*>& graphics)
{
	this->pGPS = &pGPS;
	this->squareSize = 50;
	this->arenaWidth = width;
	this->arenaDepth = depth;
	this->wallHeight = 100;
	this->nrOfWalls = 0;
	this->tempID = ID;
	
	//Create the grid for the level
	grid.resize(width / this->squareSize);
	for (int i = 0; i < width / this->squareSize; i++)
	{
		grid[i].resize(depth / this->squareSize);
		for (int k = 0; k < grid[i].size(); k++) {
			grid[i][k].type = SQUARETYPE::EMPTY;
		}
	}
	
	// createLevelWalls needs to come first
	this->createLevelWalls(staticPhysicsCount, grid, staticObjects, graphics);
	this->createFloor(grid, staticObjects, graphics);
	this->createNeonFloorGrid(staticObjects, graphics);
	this->setFallPattern(pattern);

	return this->tempID;
}

void LevelManager::changeTileStateFromPos(XMFLOAT2 pos, OBJECTSTATE::TYPE state, std::vector<std::vector<tileData>>& grid, std::vector<GameObject*>& staticObjects, std::vector<GameObject*>& dynamicObjects)
{
	XMFLOAT2 index = this->findTileIndexFromPos(pos);
	grid[(int)index.x][(int)index.y].ptr->setState(state);


	int ID = grid[(int)index.x][(int)index.y].ptr->getID();
	switch (state)
	{
	case OBJECTSTATE::TYPE::TFALLING : 
		for (int i = this->nrOfWalls; i < staticObjects.size(); i++) {
			if (staticObjects[i]->getID() == ID) {
				dynamicObjects.push_back(staticObjects[i]);
				staticObjects.erase(staticObjects.begin() + i);
			}
		}
		break;
	default:
		break;
	}
}

void LevelManager::changeTileStateFromIndex(XMFLOAT2 index, OBJECTSTATE::TYPE state, std::vector<std::vector<tileData>>& grid, std::vector<GameObject*>& staticObjects, std::vector<GameObject*>& dynamicObjects)
{

	//grid[(int)index.x][(int)index.y].ptr->setState(state);


	int ID = grid[(int)index.x][(int)index.y].ptr->getID();
	switch (state)
	{
	case OBJECTSTATE::TYPE::TFALLING:
		for (int i = this->nrOfWalls; i < staticObjects.size(); i++) {
			if (staticObjects[i]->getID() == ID) {
				staticObjects[i]->setState(state);
				dynamicObjects.push_back(staticObjects[i]);
				staticObjects.erase(staticObjects.begin() + i);
			}
		}
		break;

	case OBJECTSTATE::TYPE::RECOVER:
		for (int i = 0; i < dynamicObjects.size(); i++) {
			if (dynamicObjects[i]->getID() == ID) {
				dynamicObjects[i]->setState(state);
			}
		}
		break;
	default:
		break;
	}
}

OBJECTSTATE::TYPE LevelManager::checkTileStateFromPos(XMFLOAT3 pos, std::vector<std::vector<tileData>>& grid)
{
	return grid[pos.x / ARENASQUARESIZE][pos.z / ARENASQUARESIZE].ptr->getState();
}
 

  //////////////////////////////////////////////////////////////
 ////         OLD CODE FOR MAKING LINES ON WALLS          /////
//////////////////////////////////////////////////////////////
//DO NOT REMOVE!!!!! CAN'T DRAW LINES YET SO WE COMMENT THIS SECTION OUT UNTIL WE ACCTUALLY CAN DRAW THEM.
/*
//Create lines for the walls.
LineComponent* currentLine;
XMFLOAT3 startPos;
XMFLOAT3 stepH(0.0f, ARENASQUARESIZE, 0.0f);
XMFLOAT3 stepL;
XMFLOAT3 parallelStep;
XMMATRIX rotMH;
XMMATRIX translationM;
//Define some variables we need to create the lines. Different values if the wall is
//running along the x-axis or the z-axis. A VERTICAL wall type means it runs along the z-axis.
if (wType == WALLTYPE::VERTICAL) {
startPos = pos - XMFLOAT3(ARENASQUARESIZE / 2, (HEIGHTOFWALLS * ARENASQUARESIZE) / 2, (LENGTHOFWALLS * ARENASQUARESIZE) / 2);
stepL = XMFLOAT3(0.0f, 0.0f, ARENASQUARESIZE);
rotMH = DirectX::XMMatrixRotationY((float)(PI / 2));
parallelStep = XMFLOAT3(ARENASQUARESIZE, 0.0f, 0.0f);
}
else {
startPos = pos - XMFLOAT3((LENGTHOFWALLS * ARENASQUARESIZE) / 2, (HEIGHTOFWALLS * ARENASQUARESIZE) / 2, ARENASQUARESIZE / 2);
stepL = XMFLOAT3(ARENASQUARESIZE, 0.0f, 0.0f);
rotMH = DirectX::XMMatrixIdentity();
parallelStep = XMFLOAT3(0.0f, 0.0f, ARENASQUARESIZE);
}


//Prepare Matrixes and other variables we need for the LineComponent.
XMMATRIX worldMatrix = DirectX::XMMatrixIdentity();
XMMATRIX scaleMH = DirectX::XMMatrixScaling(LENGTHOFWALLS * ARENASQUARESIZE, 0.0f, 0.0f);
XMMATRIX scaleMV = DirectX::XMMatrixScaling(HEIGHTOFWALLS * ARENASQUARESIZE, 0.0f, 0.0f);
XMMATRIX rotMV = DirectX::XMMatrixRotationZ((float)(PI / 2));

XMFLOAT3 currPos = startPos;
XMFLOAT3 parallelPos;
XMVECTOR vec;
vColor startColor(155.0f, 48.0f, 255.0f, 255.0f);
vColor endColor(50.0f, 205.0f, 50.0f, 255.0f);
//Create horizontal lines for the wall section.
for (int i = 0; i < HEIGHTOFWALLS + 1; i++) {
//Get the ID for the next object.
nextID = this->arenaObjects.size();
object = new ArenaObject(nextID, currPos);
vec = DirectX::XMLoadFloat3(&currPos);
//Prepare the new lines world matrix.
translationM = DirectX::XMMatrixTranslationFromVector(vec);
worldMatrix = scaleMH * rotMH * translationM;
//Create the new LineComponent and hand it it's world matrix.
currentLine = new LineComponent(*object, startColor, endColor);
object->SETworldMatrix(worldMatrix);
//Give the new GameObject the LineComponent and push them into their vectors for storage.
object->addComponent(currentLine);
this->arenaObjects.push_back(object);
this->graphics.push_back(currentLine);

//Calculate the parallel line and do the same steps as above.
parallelPos = currPos + parallelStep;
nextID = this->arenaObjects.size();
object = new ArenaObject(nextID, parallelPos);
vec = DirectX::XMLoadFloat3(&parallelPos);
translationM = DirectX::XMMatrixTranslationFromVector(vec);
worldMatrix = scaleMH * rotMH * translationM;
currentLine = new LineComponent(*object, startColor, endColor);
object->SETworldMatrix(worldMatrix);
object->addComponent(currentLine);
this->arenaObjects.push_back(object);
this->graphics.push_back(currentLine);

//Prepare currPos for next iteration.
currPos = currPos + stepH;
}
//Reset currPos to the startPos for the vertical lines.
currPos = startPos;
//Create the vertical lines for the wall section.
for (int i = 0; i < LENGTHOFWALLS + 1; i++) {
//Get the ID for the next object.
nextID = this->arenaObjects.size();
object = new ArenaObject(nextID, currPos);
vec = DirectX::XMLoadFloat3(&currPos);
//Prepare the lines world Matrix.
translationM = DirectX::XMMatrixTranslationFromVector(vec);
worldMatrix = scaleMV * rotMV * translationM;
//Create the new LineComponent and hand it it's world matrix.
currentLine = new LineComponent(*object, startColor, endColor);
object->SETworldMatrix(worldMatrix);
//Give the GameObject the LineComponent and push them into their vectors for storage.
object->addComponent(currentLine);
this->arenaObjects.push_back(object);
this->graphics.push_back(currentLine);

//Calculate the parallel line and do the same steps as above.
parallelPos = currPos + parallelStep;
nextID = this->arenaObjects.size();
object = new ArenaObject(nextID, parallelPos);
vec = DirectX::XMLoadFloat3(&parallelPos);
translationM = DirectX::XMMatrixTranslationFromVector(vec);
worldMatrix = scaleMV * rotMV * translationM;
currentLine = new LineComponent(*object, startColor, endColor);
object->SETworldMatrix(worldMatrix);
object->addComponent(currentLine);
this->arenaObjects.push_back(object);
this->graphics.push_back(currentLine);

//Prepare currPos for next iteration.
currPos = currPos + stepL;
}
*/




