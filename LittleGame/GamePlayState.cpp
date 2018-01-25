#include "GamePlayState.h"
#include "GameManager.h"
#include "GamePlaySelectCommand.h"
#include "Locator.h"
#include "BlockComponent.h"
#include "RectangleComponent.h"

GamePlayState GamePlayState::sGamePlayState;

void GamePlayState::mapKeys()
{
	Locator::getInputHandler()->mapCommandToKeyboardKey(KEYBOARD::W, Key(this->selectCommand, COMMANDTYPE::TAP));
	Locator::getInputHandler()->mapCommandToControllerKey(CONTROLLER::A, Key(this->selectCommand, COMMANDTYPE::TAP));
	Locator::getInputHandler()->mapCommandToLeftThumbStick(this->selectCommand);
}

void GamePlayState::init()
{
	this->selectCommand = new GamePlaySelectCommand();
	this->mapKeys();
}

void GamePlayState::cleanup()
{
	delete this->selectCommand;
}

void GamePlayState::pause()
{
	Locator::getInputHandler()->resetKeyBindings();
}

void GamePlayState::resume()
{
	this->mapKeys();
}

void GamePlayState::handleEvents(GameManager * gm)
{
	MSG msg;

	while (gm->pollEvent(msg)) {
		// Exit the application when 'X' is pressed
		if (msg.message == WM_QUIT) {
			gm->quit();
		}

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	// Update input devices
	Locator::getInputHandler()->update(this->commandQueue);
}

void GamePlayState::update(GameManager * gm)
{
	// Execute any generated commands
	for (auto &i : this->commandQueue) {
		i.command->execute(i.player);
	}
	this->commandQueue.clear();
}

void GamePlayState::render(GameManager * gm)
{
	gm->display(this);
}

void GamePlayState::commandSelect(size_t player)
{
	int test = player;
}

GamePlayState* GamePlayState::getInstance()
{
	sGamePlayState.initArena();
	return &sGamePlayState;
}

void GamePlayState::initArena()
{
	this->createArenaFloor();
	this->createArenaWalls();
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
	object = new GameObject(nextID, pos);
	//Prepare the worldMatrix for the RectangleComponent.
	XMMATRIX worldM = DirectX::XMMatrixIdentity();
	XMMATRIX rotationM = DirectX::XMMatrixIdentity();
	XMMATRIX scaleM = DirectX::XMMatrixScaling(ARENAWIDTH / 2, 0, ARENAHEIGHT / 2);
	XMMATRIX translationM = DirectX::XMMatrixTranslationFromVector(vec);
	worldM = scaleM * rotationM * translationM;
	//Prepare the color of the rectangle.
	vColor color(0.0f, 255.0f, 0.0f, 255.0f);
	//Create the RectangleComponent and give it the finished world matrix.
	rect = new RectangleComponent(nextID, color.r, color.g, color.b, color.a);
	rect->SETworldMatrix(worldM);
	//Give the RectangleComponent to the new GameObject.
	object->addComponent(rect);
	//Push the new GameObject into the arenaObject vector.
	this->arenaObjects.push_back(object);

	int test = 2;
}

void GamePlayState::createArenaWalls()
{
	//Calculate the number of walls in each row based on the arenas width, height,
	//grid size and the length of each piece of wall
	int nrOfWallsLR = ARENAHEIGHT / (ARENASQUARESIZE * LENGTHOFWALLS); //Should be 8 during testing
	int nrOfWallsTB = ARENAWIDTH / (ARENASQUARESIZE * LENGTHOFWALLS); //Should be 12 during testing
	//Prepare the ID for the first GameObject we will create.
	int nextID = this->arenaObjects.size();
	//Create an array with the index of the walls that will not be created. 
	//These will be the openings where the monsters can spawn.
	//The array is hardcoded to open the middle sections of each wall until
	//the randomized function is implemented.
	int skip[8] = { 3, 4, 11, 12, 21, 22, 33, 34 };
	int skipChecker = 0; //shitty implementation until we make the real one.

	//Create rotation matrix for Left and right row of walls. Rotates 90 degres around Y-axis.
	XMMATRIX rotLR = DirectX::XMMatrixRotationY(PI / 2);
	//Create rotation matrix for Top and Bottom row of walls. No rotation so it will be identity matrix.
	XMMATRIX rotTB = DirectX::XMMatrixIdentity();
	//Create scale matrix for all of the walls.
	XMMATRIX scaleM = DirectX::XMMatrixScaling(LENGTHOFWALLS * ARENASQUARESIZE / 2, HEIGHTOFWALLS * ARENASQUARESIZE / 2, ARENASQUARESIZE / 2);
	//Initialize a translation matrix for future use.
	XMMATRIX translationM = DirectX::XMMatrixIdentity();
	//Inititalize worldMatrix that will be passed to the BlockComponent.
	XMMATRIX worldMatrix = DirectX::XMMatrixIdentity();
	//Create a color to be used in the BlockComponent.
	XMFLOAT4 wallColor(255.0f, 0.0f, 0.0f, 255.0f);


	XMFLOAT3 currPos;
	XMVECTOR vec;
	XMFLOAT2 posIndex; // used to find all the indexes of a wall section.
	//Creates left row of arena walls
	for (int i = 0; i < nrOfWallsLR; i++) {
		//Calculate new pos
		currPos = XMFLOAT3(ARENASQUARESIZE / 2.0f, (ARENASQUARESIZE * HEIGHTOFWALLS) / 2.0f, ((ARENASQUARESIZE * LENGTHOFWALLS) / 2.0f) + i * LENGTHOFWALLS * ARENASQUARESIZE);
		
		//Check if the new position is a spawn location.
		if (skipChecker == skip[0] || skipChecker == skip[1]) {
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
			this->createAWall(currPos, worldMatrix, wallColor);

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
		skipChecker++;//remove when we implement the real random openings.
	}
	//Creates right row of arena walls
	for (int i = 0; i < nrOfWallsLR; i++) {
		//Calculate new pos
		currPos = XMFLOAT3(ARENAWIDTH - ARENASQUARESIZE / 2.0f, (ARENASQUARESIZE * HEIGHTOFWALLS) / 2.0f, ((ARENASQUARESIZE * LENGTHOFWALLS) / 2.0f) + i * LENGTHOFWALLS * ARENASQUARESIZE);
		
		//Check if the new position is a spawn location.
		if (skipChecker == skip[2] || skipChecker == skip[3]) {
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
			this->createAWall(currPos, worldMatrix, wallColor);

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
		skipChecker++;//remove when we implement the real random openings.
	}
	//Creates bottom row of arena walls
	for (int i = 0; i < nrOfWallsTB; i++) {
		//Calculate new pos
		currPos = XMFLOAT3(((ARENASQUARESIZE * LENGTHOFWALLS) / 2.0f) + i * LENGTHOFWALLS * ARENASQUARESIZE, (ARENASQUARESIZE * HEIGHTOFWALLS) / 2.0f, ARENASQUARESIZE / 2.0f);

		//Check if the new position is a spawn location.
		if (skipChecker == skip[4] || skipChecker == skip[5]) {
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
			this->createAWall(currPos, worldMatrix, wallColor);
		
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
		skipChecker++; //remove when we implement the real random openings.
	}
	//Creates top row of arena walls
	for (int i = 0; i < nrOfWallsTB; i++) {
		//Calculate new pos
		currPos = XMFLOAT3(((ARENASQUARESIZE * LENGTHOFWALLS) / 2.0f) + i * LENGTHOFWALLS * ARENASQUARESIZE, (ARENASQUARESIZE * HEIGHTOFWALLS) / 2.0f, ARENAHEIGHT - ARENASQUARESIZE / 2.0f);
	
		//Check if the new position is a spawn location.
		if (skipChecker == skip[6] || skipChecker == skip[7]) {
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
			this->createAWall(currPos, worldMatrix, wallColor);
		
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
		skipChecker++;//remove when we implement the real random openings.
	}
	int test2 = 2;
}

void GamePlayState::createAWall(XMFLOAT3 pos, XMMATRIX wMatrix, XMFLOAT4 color)
{
	GameObject* object;
	BlockComponent* block;
	//Get ID for next object.
	int nextID = this->arenaObjects.size();
	//Create the GameObject.
	object = new GameObject(nextID, pos);
	//Create the BlockComponent and give it it's world matrix.
	block = new BlockComponent(nextID, color.x, color.y, color.z, color.w);
	block->SETworldMatrix(wMatrix);
	//Add the BlockComponent to the GameObject and push the GameObject into the vector.
	object->addComponent(block);
	this->arenaObjects.push_back(object);
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