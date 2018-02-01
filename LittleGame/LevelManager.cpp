#include "LevelManager.h"
#include "RectangleComponent.h"
#include "LineComponent.h"
#include "BlockComponent.h"
#include "ActorObject.h"
#include "ArenaObject.h"

void LevelManager::createFloor(std::vector<GameObject*>& objects, std::vector<GraphicsComponent*>& graphics)
{
	GameObject* object;
	RectangleComponent* rect;
	int nextID = objects.size();
	//Calculate center position of the arena
	XMFLOAT3 pos(this->arenaWidth / 2, -0.5f, this->arenaDepth / 2);
	XMVECTOR vec = XMLoadFloat3(&pos);
	//Create the GameObject
	object = new ArenaObject(nextID, pos);
	//Prepare the worldMatrix for the RectangleComponent
	XMMATRIX worldM;
	XMMATRIX rotationM = XMMatrixIdentity();
	XMMATRIX scaleM = XMMatrixScaling(this->arenaWidth / 2, 0, this->arenaDepth / 2);
	XMMATRIX translationM = XMMatrixTranslationFromVector(vec);
	worldM = scaleM * rotationM * translationM;
	//Prepare the color of the rectangle
	vColor color(72.0f, 118.0f, 255.0f, 255.0f);
	//Create the RectangleComponent and set the world matrix
	rect = new RectangleComponent(*object, color.r, color.g, color.b, color.a);
	//Give the RectangleComponent to the ArenaObject and set it's world matrix
	object->addComponent(rect);
	object->SETworldMatrix(worldM);
	//Push the new ArenaObject and GraphicsComponent into the vector arrays
	objects.push_back(object);
	graphics.push_back(rect);
}

void LevelManager::createNeonFloorGrid(std::vector<GameObject*>& objects, std::vector<GraphicsComponent*>& graphics)
{
	//Calculate the number of vertical and horizontal lines needed
	int nrOfVerticalLines = this->arenaWidth / this->squareSize + 1;
	int nrOfHorizontalLines = this->arenaDepth / this->squareSize + 1;

	XMFLOAT4 color(255.0f, 0.0f, 0.0f, 255.0f);
	//Prepare matrices and variables
	float rectWidth = 1.5f;
	XMMATRIX worldM;
	XMMATRIX translationM;
	XMMATRIX scaleMV = XMMatrixScaling(rectWidth, 0.0f, this->arenaDepth / 2.0f);
	XMMATRIX scaleMH = XMMatrixScaling(this->arenaWidth / 2.0f, 0.0f, rectWidth);
	XMMATRIX rotationM = XMMatrixIdentity();
	
	XMFLOAT3 currentPos;
	XMVECTOR vec;
	//Create the vertical lines
	for (int i = 0; i < nrOfVerticalLines; i++)
	{
		currentPos = XMFLOAT3(i * this->squareSize, 0.0f, this->arenaDepth / 2.0f);
		vec = XMLoadFloat3(&currentPos);
		translationM = XMMatrixTranslationFromVector(vec);
		worldM = scaleMV * rotationM * translationM;
		this->createARectLine(currentPos, worldM, color, objects, graphics);
	}
	//Create the horizontal lines
	for (int i = 0; i < nrOfHorizontalLines; i++)
	{
		currentPos = XMFLOAT3(this->arenaWidth / 2.0f, 0.0f, i * this->squareSize);
		vec = XMLoadFloat3(&currentPos);
		translationM = XMMatrixTranslationFromVector(vec);
		worldM = scaleMH * rotationM * translationM;
		this->createARectLine(currentPos, worldM, color, objects, graphics);
	}
}

void LevelManager::createARectLine(XMFLOAT3 pos, XMMATRIX worldM, XMFLOAT4 color, std::vector<GameObject*>& objects, std::vector<GraphicsComponent*>& graphics)
{
	GameObject* object;
	RectangleComponent* rect;
	int nextID = objects.size();
	//Create the ArenaObject and the RectangleComponent
	object = new ArenaObject(nextID, pos);
	rect = new RectangleComponent(*object, color.x, color.y, color.z, color.w);
	//Add the RectangleComponent to the ArenaObject and store them in the vector arrays
	object->SETworldMatrix(worldM);
	object->addComponent(rect);
	objects.push_back(object);
	graphics.push_back(rect);
}

void LevelManager::createLevelWalls(std::vector<GameObject*>& objects, std::vector<GraphicsComponent*>& graphics, std::vector<PhysicsComponent*>& physics)
{

}

void LevelManager::createAWall(XMFLOAT3 pos, XMFLOAT3 scale, XMMATRIX worldM, XMFLOAT4 color, std::vector<GameObject*>& objects, std::vector<GraphicsComponent*>& graphics, std::vector<PhysicsComponent*>& physics)
{
	GameObject* object;
	BlockComponent* block;
	int nextID = objects.size();
	//Create the new ArenaObject and the new BlockComponent
	object = new ArenaObject(nextID, pos);
	block = new BlockComponent(*object, color.x, color.y, color.z, color.w);
	//Give the world matrix to the new object and store the object and the block in the vector arrays
	object->SETworldMatrix(worldM);
	objects.push_back(object);
	graphics.push_back(block);
}

void LevelManager::initArena(int width, int depth, std::vector<GameObject*>& objects, std::vector<GraphicsComponent*>& graphics, std::vector<PhysicsComponent*>& physics)
{
	this->squareSize = 50;
	this->arenaWidth = width;
	this->arenaDepth = depth;
	this->wallHeight = 150;
	
	

	this->createFloor(objects, graphics);
	this->createNeonFloorGrid(objects, graphics);
	this->createLevelWalls(objects, graphics, physics);

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




