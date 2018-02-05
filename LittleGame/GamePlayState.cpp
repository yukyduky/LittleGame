#include "GamePlayState.h"
#include "GameManager.h"
#include "Locator.h"
#include "RectangleComponent.h"
#include "LineComponent.h"
#include "BlockComponent.h"
#include "KeyboardComponent.h"
#include "ControllerComponent.h"
#include <SimpleMath.h>
#include <DirectXMath.h>
#include "ActorObject.h"
#include "ArenaObject.h"

using namespace DirectX::SimpleMath;

GamePlayState GamePlayState::sGamePlayState;

void GamePlayState::updatePhysicsComponents()
{
	for (auto&& i : physicsListDynamic) {
		if (this->arenaObjects.at(i->getID())->getState() != OBJECTSTATE::DEAD) {
			i->updateBoundingArea(this->arenaObjects.at(i->getID())->getPosition());
		}
	}
}

void GamePlayState::checkCollisions() {
	// LOOP 1: Looping through each DYNAMIC physicsComponent
	for (auto&& i : this->physicsListDynamic) {
		// Comparing to all other DYNAMIC & STATIC physComponents.
		// NOTE: Skipping if object state = DEAD.
		int iID = i->getID();
		if (this->arenaObjects.at(iID)->getState() != OBJECTSTATE::DEAD) {
			// LOOP 2.1: DYNAMIC <--> DYNAMIC Collision
			for (auto&& k : this->physicsListDynamic) {
				int kID = k->getID();
				if (iID != kID)
				{
					if (this->arenaObjects.at(k->getID())->getState() != OBJECTSTATE::DEAD) {

						if (i->checkCollision(k->getBoundingSphere())) {
							// Call COLLISION-CLASS function
							this->collisionHandler.executeCollision(
								this->arenaObjects.at(i->getID()),
								this->arenaObjects.at(k->getID()),
								&i->getBoundingSphere(),
								&k->getBoundingSphere()
							);
						}
					}
				}
				
			}
			// LOOP 2.2: DYNAMIC <--> STATIC Collision
			for (auto&& k : this->physicsListStatic) {
				if (this->arenaObjects.at(k->getID())->getState() != OBJECTSTATE::DEAD) {

					if (i->checkCollision(k->getBoundingSphere())) {
						// Call COLLISION-CLASS function
						this->collisionHandler.executeCollision(
							this->arenaObjects.at(i->getID()),
							this->arenaObjects.at(k->getID()),
							&i->getBoundingSphere(),
							&k->getBoundingSphere()
						);
					}
				}
			}
		}
	}
}


void GamePlayState::init() {
	this->camera.init(ARENAWIDTH, ARENAHEIGHT);
	this->rio.initialize(this->camera);
	this->initPlayer();
	this->initArena();

	for (auto &i : this->graphics) {
		this->rio.addGraphics(i);
	}
}

void GamePlayState::cleanUp()
{
	// Direct internal objects
	// this->rio.cleanUp();
	// this->camera.cleanUp();


	// GameObjects which will on their own clean up all of their connected components
	for (auto &iterator : this->arenaObjects) {
		iterator->cleanUp();
		delete iterator;
	}
	for (auto &iterator : this->projectiles) {
		//iterator->cleanUp();
		//delete iterator;
	}
}

void GamePlayState::pause() {

}

void GamePlayState::resume()
{
	
}

void GamePlayState::handleEvents(GameManager * gm) {
	MSG msg;

	while (gm->pollEvent(msg)) {
		// Exit the application when 'X' is pressed
		if (msg.message == WM_QUIT) {
			gm->quit();
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
}


void GamePlayState::update(GameManager * gm)
{
	this->updatePhysicsComponents();
	this->checkCollisions();

	for (auto &iterator : playerInput) {
		iterator->generateCommands();
		iterator->execute();
	}

	for (auto &iterator : projectiles)
	{
		iterator->update();
	}
}

void GamePlayState::render(GameManager * gm) {
	this->rio.render();
	gm->display(this);
}

GamePlayState* GamePlayState::getInstance() {
	return &sGamePlayState;
	
}

void GamePlayState::initArena()
{
	this->createArenaFloor();
	this->createArenaNeonGrid();
	this->createArenaWalls();

	int test23 = 1;
}

void GamePlayState::createArenaFloor()
{
	GameObject* object;
	RectangleComponent* rect;
	int nextID = this->arenaObjects.size();
	//Calculate center position of the arena
	XMFLOAT3 pos(ARENAWIDTH / 2, -0.5f, ARENAHEIGHT / 2);
	XMVECTOR vec = DirectX::XMLoadFloat3(&pos);
	//Create the GameObject
	object = new ArenaObject(nextID, pos);
	//Prepare the worldMatrix for the RectangleComponent.
	XMMATRIX worldM = DirectX::XMMatrixIdentity();
	XMMATRIX rotationM = DirectX::XMMatrixIdentity();
	XMMATRIX scaleM = DirectX::XMMatrixScaling(ARENAWIDTH / 2, 0, ARENAHEIGHT / 2);
	XMMATRIX translationM = DirectX::XMMatrixTranslationFromVector(vec);
	worldM = scaleM * rotationM * translationM;
	//Prepare the color of the rectangle.
	vColor color(72.0f, 118.0f, 255.0f, 255.0f);
	//Create the RectangleComponent and give it the finished world matrix.
	rect = new RectangleComponent(*object, color.r, color.g, color.b, color.a);
	object->SETworldMatrix(worldM);
	//Give the RectangleComponent to the new GameObject.
	object->addComponent(rect);
	//Push the new GameObject into the GameObject vector and graphics vector.
	this->arenaObjects.push_back(object);
	this->graphics.push_back(rect);

	int test = 2;
}

void GamePlayState::createArenaNeonGrid()
{
	//Calculate the number of vertical and horizontal lines.
	int nrOfVerticalLines = (ARENAWIDTH / ARENASQUARESIZE) + 1; //+1 to get a start line at 0
	int nrOfHorizontalLines = (ARENAHEIGHT / ARENASQUARESIZE) + 1;//+1 to get a start line at 0
																  //Create startColor and endColor
	XMFLOAT4 color(255.0f, 0.0f, 0.0f, 255.0f);
	//Prepare matrixes
	float rectWidth = 1.5f;
	XMMATRIX worldMatrix = DirectX::XMMatrixIdentity();
	XMMATRIX translationM = DirectX::XMMatrixIdentity();
	XMMATRIX scaleMV = XMMatrixScaling(rectWidth, 0.0f, ARENAHEIGHT / 2.0f);
	XMMATRIX scaleMH = XMMatrixScaling(ARENAWIDTH / 2.0f, 0.0f, rectWidth);
	XMMATRIX rotationM = DirectX::XMMatrixIdentity();


	//Prepare current position variable and vec variable.
	XMFLOAT3 currentPos;
	XMVECTOR vec;
	//Create the vertical lines.
	for (int i = 0; i < nrOfVerticalLines; i++)
	{
		currentPos = XMFLOAT3(i * ARENASQUARESIZE, 0.0f, ARENAHEIGHT / 2.0f);
		vec = DirectX::XMLoadFloat3(&currentPos);
		translationM = DirectX::XMMatrixTranslationFromVector(vec);
		//scaleMV = DirectX::XMMatrixScaling(ARENAHEIGHT, 0.0f, 0.0f);
		worldMatrix = scaleMV * rotationM * translationM;
		this->createRectLine(currentPos, worldMatrix, color);
	}
	for (int i = 0; i < nrOfHorizontalLines; i++)
	{
		currentPos = XMFLOAT3(ARENAWIDTH / 2.0f , 0.0f, i * ARENASQUARESIZE);
		vec = DirectX::XMLoadFloat3(&currentPos);
		translationM = DirectX::XMMatrixTranslationFromVector(vec);
		//scaleMH = DirectX::XMMatrixScaling(ARENAWIDTH, 0.0f, 0.0f);
		worldMatrix = scaleMH * rotationM * translationM;
		this->createRectLine(currentPos, worldMatrix, color);
	}


	/*
	//Calculate the number of vertical and horizontal lines.
	int nrOfVerticalLines = (ARENAWIDTH / ARENASQUARESIZE) + 1; //+1 to get a start line at 0
	int nrOfHorizontalLines = (ARENAHEIGHT / ARENASQUARESIZE) + 1;//+1 to get a start line at 0
	//Create startColor and endColor
	XMFLOAT4 startColor(155.0f, 48.0f, 255.0f, 255.0f);
	XMFLOAT4 endColor(155.0f, 48.0f, 255.0f, 255.0f);
	//Prepare matrixes
	XMMATRIX worldMatrix = DirectX::XMMatrixIdentity();
	XMMATRIX translationM = DirectX::XMMatrixIdentity();
	XMMATRIX scaleM = DirectX::XMMatrixIdentity();
	XMMATRIX rotVertical = DirectX::XMMatrixRotationY((float)(PI / 2));
	XMMATRIX rotHorizontal = DirectX::XMMatrixIdentity();

	//Prepare current position variable and vec variable.
	XMFLOAT3 currentPos;
	XMVECTOR vec;
	//Create the vertical lines.
	for (int i = 0; i < nrOfVerticalLines; i++)
	{
		currentPos = XMFLOAT3(i * ARENASQUARESIZE, 0.0f, 0.0f);
		vec = DirectX::XMLoadFloat3(&currentPos);
		translationM = DirectX::XMMatrixTranslationFromVector(vec);
		scaleM = DirectX::XMMatrixScaling(ARENAHEIGHT, 0.0f, 0.0f);
		worldMatrix = scaleM * rotVertical * translationM;
		this->createLine(currentPos, worldMatrix, startColor, endColor);
	}
	for (int i = 0; i < nrOfHorizontalLines; i++)
	{
		currentPos = XMFLOAT3(0.0f, i * ARENASQUARESIZE, 0.0f);
		vec = DirectX::XMLoadFloat3(&currentPos);
		translationM = DirectX::XMMatrixTranslationFromVector(vec);
		scaleM = DirectX::XMMatrixScaling(ARENAWIDTH, 0.0f, 0.0f);
		worldMatrix = scaleM * rotHorizontal * translationM;
		this->createLine(currentPos, worldMatrix, startColor, endColor);
	}
	*/
	int test3 = 4;
}

void GamePlayState::createLine(XMFLOAT3 pos, XMMATRIX wMatrix, XMFLOAT4 startColor, XMFLOAT4 endColor)
{
	GameObject* object = nullptr;
	LineComponent* line = nullptr;
	//Get ID for next object.
	int nextID = this->arenaObjects.size();
	//Create the GameObject
	object = new ArenaObject(nextID, pos);
	//Create the LineComponent and give it it's world matrix.
	vColor startC(startColor.x, startColor.w, startColor.z, startColor.w);
	vColor endC(startColor.x, startColor.w, startColor.z, startColor.w);
	line = new LineComponent(*object, startC, endC);
	object->SETworldMatrix(wMatrix);
	//Add the LineComponent to the GameObject and push the GameObject into the vectors.
	object->addComponent(line);
	this->graphics.push_back(line);
	this->arenaObjects.push_back(object);
}

void GamePlayState::createRectLine(XMFLOAT3 pos, XMMATRIX wMatrix, XMFLOAT4 color)
{
	GameObject* object = nullptr;
	RectangleComponent* rect;
	//Get the next id
	int nextID = this->arenaObjects.size();
	//Create the ArenaObject and the RectangleComponent
	object = new ArenaObject(nextID, pos);
	rect = new RectangleComponent(*object, color.x, color.y, color.z, color.w);
	//Add the RectangleComponent to the GameObject and push the GameObject into the vectors.
	object->SETworldMatrix(wMatrix);
	object->addComponent(rect);
	this->graphics.push_back(rect);
	this->arenaObjects.push_back(object);
}

void GamePlayState::createArenaWalls()
{
	//Calculate the number of walls in each row based on the arenas width, height,
	//grid size and the length of each piece of wall
	int nrOfWallsLR = ARENAHEIGHT / (ARENASQUARESIZE * LENGTHOFWALLS); //Should be 8 during testing
	int nrOfWallsTB = ARENAWIDTH / (ARENASQUARESIZE * LENGTHOFWALLS); //Should be 12 during testing
	//Prepare the ID for the first GameObject we will create.
	int nextID = this->arenaObjects.size();

	//Create rotation matrix for Left and right row of walls. Rotates 90 degres around Y-axis.
	XMMATRIX rotLR = DirectX::XMMatrixRotationY((float)(PI / 2));
	//Create rotation matrix for Top and Bottom row of walls. No rotation so it will be identity matrix.
	XMMATRIX rotTB = DirectX::XMMatrixIdentity();
	//Create scale matrix for all of the walls.
	//XMMATRIX scaleM = DirectX::XMMatrixIdentity();
	XMMATRIX scaleM = DirectX::XMMatrixScaling(LENGTHOFWALLS * ARENASQUARESIZE / 2, HEIGHTOFWALLS * ARENASQUARESIZE / 2, ARENASQUARESIZE / 2);
	//Initialize a translation matrix for future use.
	XMMATRIX translationM = DirectX::XMMatrixIdentity();
	//Inititalize worldMatrix that will be passed to the BlockComponent.
	XMMATRIX worldMatrix = DirectX::XMMatrixIdentity();
	//Create a color to be used in the BlockComponent.
	XMFLOAT4 wallColor(155.0f, 48.0f, 255.0f, 255.0f);

	
	XMFLOAT3 currPos;
	XMVECTOR vec;
	XMFLOAT2 posIndex; // used to find all the indexes of a wall section.
	XMFLOAT3 temp;
	//Creates left row of arena walls
	for (int i = 0; i < nrOfWallsLR; i++) {
		//Calculate new pos
		currPos = XMFLOAT3(ARENASQUARESIZE / 2.0f, (ARENASQUARESIZE * HEIGHTOFWALLS) / 2.0f, ((ARENASQUARESIZE * LENGTHOFWALLS) / 2.0f) + i * LENGTHOFWALLS * ARENASQUARESIZE);
		
		//Check if the new position is a spawn location.
		if (i == nrOfWallsLR / 2 || i == nrOfWallsLR / 2 - 1) {
			//Find the index of the spawn locations first square
			currPos = currPos - XMFLOAT3(0.0f, 0.0f, ARENASQUARESIZE * LENGTHOFWALLS / 2);
			
			//Set the all of the spawnlocation areas squares to SPAWN.
			for (int j = 0; j < LENGTHOFWALLS; j++)
			{
				posIndex = this->findGridIndexFromPosition(currPos);
				this->SETsquareType(posIndex, SQUARETYPE::SPAWN);
				currPos.z += ARENASQUARESIZE;
			}
		}
		else {
			//Prepare the worldMatrix for the new wall and create the wall.
			vec = DirectX::XMLoadFloat3(&currPos);
			translationM = DirectX::XMMatrixTranslationFromVector(vec);
			worldMatrix = scaleM * rotLR * translationM;
			this->createAWall(currPos, worldMatrix, wallColor, WALLTYPE::VERTICAL);

			//Find the index of the wall locations first square.
			currPos = currPos - XMFLOAT3(0.0f, 0.0f, ARENASQUARESIZE * LENGTHOFWALLS / 2);
			
			//Set all of the wall locations areas squares to WALL.
			for (int j = 0; j < LENGTHOFWALLS; j++)
			{
				posIndex = this->findGridIndexFromPosition(currPos);
				this->SETsquareType(posIndex, SQUARETYPE::WALL);
				currPos.z += ARENASQUARESIZE;
			}
		}
	}
	//Creates right row of arena walls
	for (int i = 0; i < nrOfWallsLR; i++) {
		//Calculate new pos
		currPos = XMFLOAT3(ARENAWIDTH - ARENASQUARESIZE / 2.0f, (ARENASQUARESIZE * HEIGHTOFWALLS) / 2.0f, ((ARENASQUARESIZE * LENGTHOFWALLS) / 2.0f) + i * LENGTHOFWALLS * ARENASQUARESIZE);
		
		//Check if the new position is a spawn location.
		if (i == nrOfWallsLR / 2 || i == nrOfWallsLR / 2 - 1) {
			//Find the index of the spawn locations first square
			currPos = currPos - XMFLOAT3(0.0f, 0.0f, ARENASQUARESIZE * LENGTHOFWALLS / 2);
			
			//Set the all of the spawnlocation areas squares to SPAWN.
			for (int j = 0; j < LENGTHOFWALLS; j++)
			{
				posIndex = this->findGridIndexFromPosition(currPos);
				this->SETsquareType(posIndex, SQUARETYPE::SPAWN);
				currPos.z += ARENASQUARESIZE;
			}
		}
		else {
			//Prepare the worldMatrix for the new wall and create the wall.
			vec = DirectX::XMLoadFloat3(&currPos);
			translationM = DirectX::XMMatrixTranslationFromVector(vec);
			worldMatrix = scaleM * rotLR * translationM;
			this->createAWall(currPos, worldMatrix, wallColor, WALLTYPE::VERTICAL);

			//Find the index of the wall locations first square.
			currPos = currPos - XMFLOAT3(0.0f, 0.0f, ARENASQUARESIZE * LENGTHOFWALLS / 2);

			//Set all of the wall locations areas squares to WALL.
			for (int j = 0; j < LENGTHOFWALLS; j++)
			{
				posIndex = this->findGridIndexFromPosition(currPos);
				this->SETsquareType(posIndex, SQUARETYPE::WALL);
				currPos.z += ARENASQUARESIZE;
			}
		}
	}
	//Creates bottom row of arena walls
	for (int i = 0; i < nrOfWallsTB; i++) {
		//Calculate new pos
		currPos = XMFLOAT3(((ARENASQUARESIZE * LENGTHOFWALLS) / 2.0f) + i * LENGTHOFWALLS * ARENASQUARESIZE, (ARENASQUARESIZE * HEIGHTOFWALLS) / 2.0f, ARENASQUARESIZE / 2.0f);

		//Check if the new position is a spawn location.
		if (i == nrOfWallsTB / 2 || i == nrOfWallsTB / 2 - 1) {
			//Find the index of the spawn locations first square
			currPos = currPos - XMFLOAT3(ARENASQUARESIZE * LENGTHOFWALLS / 2, 0.0f, 0.0f);

			//Set the all of the spawnlocation areas squares to SPAWN.
			for (int j = 0; j < LENGTHOFWALLS; j++)
			{
				posIndex = this->findGridIndexFromPosition(currPos);
				this->SETsquareType(posIndex, SQUARETYPE::SPAWN);
				currPos.x += ARENASQUARESIZE;
			}
		}
		else {
			//Prepare the worldMatrix for the new wall and create the wall.
			vec = DirectX::XMLoadFloat3(&currPos);
			translationM = DirectX::XMMatrixTranslationFromVector(vec);
			worldMatrix = scaleM * rotTB * translationM;
			this->createAWall(currPos, worldMatrix, wallColor, WALLTYPE::HORIZONTAL);
		
			//Find the index of the wall locations first square.
			currPos = currPos - XMFLOAT3(ARENASQUARESIZE * LENGTHOFWALLS / 2, 0.0f, 0.0f);
			
			//Set all of the wall locations areas squares to WALL.
			for (int j = 0; j < LENGTHOFWALLS; j++)
			{
				posIndex = this->findGridIndexFromPosition(currPos);
				this->SETsquareType(posIndex, SQUARETYPE::WALL);
				currPos.x += ARENASQUARESIZE;
			}
		}
	}
	
	
	//Creates top row of arena walls
	for (int i = 0; i < nrOfWallsTB; i++) {
		//Calculate new pos
		currPos = XMFLOAT3(((ARENASQUARESIZE * LENGTHOFWALLS) / 2.0f) + i * LENGTHOFWALLS * ARENASQUARESIZE, (ARENASQUARESIZE * HEIGHTOFWALLS) / 2.0f, ARENAHEIGHT - ARENASQUARESIZE / 2.0f);
	
		//Check if the new position is a spawn location.
		if (i == nrOfWallsTB / 2 || i == nrOfWallsTB / 2 - 1) {
			//Find the index of the spawn locations first square
			currPos = currPos - XMFLOAT3(ARENASQUARESIZE * LENGTHOFWALLS / 2, 0.0f, 0.0f);

			//Set the all of the spawnlocation areas squares to SPAWN.
			for (int j = 0; j < LENGTHOFWALLS; j++)
			{
				posIndex = this->findGridIndexFromPosition(currPos);
				this->SETsquareType(posIndex, SQUARETYPE::SPAWN);
				currPos.x += ARENASQUARESIZE;
			}
		}
		else { 
			//Prepare the worldMatrix for the new wall and create the wall.
			vec = DirectX::XMLoadFloat3(&currPos);
			translationM = DirectX::XMMatrixTranslationFromVector(vec);
			worldMatrix = scaleM * rotTB * translationM;
			this->createAWall(currPos, worldMatrix, wallColor, WALLTYPE::HORIZONTAL);
		
			//Find the index of the wall locations first square.
			currPos = currPos - XMFLOAT3(ARENASQUARESIZE * LENGTHOFWALLS / 2, 0.0f, 0.0f);

			//Set all of the wall locations areas squares to WALL.
			for (int j = 0; j < LENGTHOFWALLS; j++)
			{
				posIndex = this->findGridIndexFromPosition(currPos);
				this->SETsquareType(posIndex, SQUARETYPE::WALL);
				currPos.x += ARENASQUARESIZE;
			}
		}
	}
	
	int test2 = 2;
}

void GamePlayState::createAWall(XMFLOAT3 pos, XMMATRIX wMatrix, XMFLOAT4 color, WALLTYPE::TYPE wType)
{
	GameObject* object;
	BlockComponent* block;
	//Get ID for next object.
	int nextID = this->arenaObjects.size();
	//Create the GameObject.
	object = new ArenaObject(nextID, pos);
	//Create the BlockComponent and give it it's world matrix.
	block = new BlockComponent(*object, color.x, color.y, color.z, color.w);
	object->SETworldMatrix(wMatrix);
	//Add the BlockComponent to the GameObject and push the GameObject into the vectors.
	object->addComponent(block);
	this->graphics.push_back(block);
	this->arenaObjects.push_back(object);

	
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
}

void GamePlayState::SETsquareType(XMFLOAT2 index, SQUARETYPE::TYPE type)
{

	this->arenaGrid[(int)index.x][(int)index.y] = type;
}

XMFLOAT2 GamePlayState::findGridIndexFromPosition(XMFLOAT3 pos)
{
	XMFLOAT2 index = XMFLOAT2(0.0f, 0.0f);
	index.x = pos.x / ARENASQUARESIZE;
	index.y = pos.z / ARENASQUARESIZE;

	return index;
}

void GamePlayState::initPlayer()
{
	ActorObject* actor;
	BlockComponent* block;
	InputComponent* input;		// THIS IS CORRECT!
	PhysicsComponent* physics;
	int nextID = this->arenaObjects.size();
	
	//Create the new ActorObject
	XMFLOAT3 playerScales(10.0f, 40.0f, 10.0f);
	XMFLOAT3 playerPos((float)(ARENAWIDTH / 2), playerScales.y, (float)(ARENAHEIGHT / 2));
	actor = new ActorObject(nextID, playerPos, this);
	/// PHYSICS COMPONENT:
	// 1: We new a PhysicsComponent, using the actor's address as a parameter.
	physics = new PhysicsComponent(*actor);
	// 2: We add this component to the Dynamic list because actor = dynamic.
	this->physicsListDynamic.push_back(physics);
	// 3: We add this component to actor's list of components.
	actor->addComponent(this->physicsListDynamic.back());
	XMFLOAT3 playerVelocity(300.0f, 300.0f, 300.0f);
	actor->setVelocity(playerVelocity);

	//Create the playerColor and the new BlockComponent that will represent the players body.
	vColor playerColor(50.0f, 205.0f, 50.0f, 255.0f);
	block = new BlockComponent(*actor, playerColor.r, playerColor.g, playerColor.b, playerColor.a);
	
	//Create the world-, scale-, translation- and rotationmatrix and hand them to the ActorObject.
	XMVECTOR playerTranslation = XMLoadFloat3(&playerPos);
	XMMATRIX worldMatrix;
	XMMATRIX translationM = XMMatrixTranslationFromVector(playerTranslation);
	XMMATRIX rotationM = XMMatrixIdentity();
	XMMATRIX scaleM = XMMatrixScaling(playerScales.x, playerScales.y, playerScales.z);
	worldMatrix = scaleM * rotationM * translationM;

	actor->SETtranslationMatrix(translationM);
	actor->SETscaleMatrix(scaleM);
	actor->SETrotationMatrix(rotationM);
	actor->SETworldMatrix(worldMatrix);
	actor->addComponent(block);

	actor->setType(OBJECTTYPE::PLAYER);

	//Create the new InputComponent (KeyboardComponent or ControllerComponent) and hand it to the ActorObject.
	//input = new ControllerComponent(*actor, 0);
	input = new KeyboardComponent(*actor);

	this->playerInput[0] = input;
	this->arenaObjects.push_back(actor);
	this->graphics.push_back(block);


	/*
	this->go = new GameObject(0);
	this->actorObject = new ActorObject(0);		// HAS TO BE 0 FOR THE ACTOR OBJECT!!!! ControllerComponent::generateCommands() --> XInputGetState()
	
	//this->playerInput[0] = new ControllerComponent(*this->actorObject, 0);
	this->blocks.push_back(new BlockComponent(*this->go, 0.0f, 1.0f, 0.0f, 1.0f));
	*/
}

Projectile* GamePlayState::initProjectile(XMFLOAT3 pos, XMFLOAT3 dir, ProjProp props)
{
	Projectile* proj;
	int nextID = this->newID();

	// Declare Components
	BlockComponent* block;
	PhysicsComponent* phyComp;
	AbilityComponent* abiliComp;

	proj = new Projectile(nextID, pos);
	proj->setDirection(dir);

	//input for blockComp
	XMFLOAT3 scale(props.size, props.size, props.size);
	XMFLOAT3 position = pos;
	block = new BlockComponent(*proj, props.color.x, props.color.y, props.color.z, 255.0f);
	
	// Create matrixes for world-matrix
	XMVECTOR translation = XMLoadFloat3(&position);
	XMMATRIX worldMatrix;
	XMMATRIX translationM = XMMatrixTranslationFromVector(translation);
	XMMATRIX rotationM = XMMatrixIdentity();
	XMMATRIX scaleM = XMMatrixScaling(scale.x, scale.y, scale.z);
	worldMatrix = scaleM * rotationM * translationM;

	// Apply matrixes
	proj->SETtranslationMatrix(translationM);
	proj->SETscaleMatrix(scaleM);
	proj->SETrotationMatrix(rotationM);
	proj->SETworldMatrix(worldMatrix);

	// Bind components
	proj->addComponent(block);

	//Add the block to the objects that will be rendered
	this->graphics.push_back(block);
	this->rio.addGraphics(block);

	//Template of components that are beeing worked on by other users
	abiliComp = new FireballComponent(*proj, 1);
	proj->setVelocity(dir * proj->getSpeed());
	proj->addComponent(abiliComp);

	//Template for Physics
	phyComp = new PhysicsComponent(/*pos, */*proj, props.size);
	this->physicsListDynamic.push_back(phyComp);
	proj->addComponent(phyComp);

	
	//Add proj to objectArrays
	this->arenaObjects.push_back(proj);
	this->projectiles.push_back(proj);

	return proj;
}
