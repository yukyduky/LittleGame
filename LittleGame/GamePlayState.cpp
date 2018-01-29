#include "GamePlayState.h"
#include "GameManager.h"
#include "Locator.h"
#include "RectangleComponent.h"
#include "LineComponent.h"
#include "BlockComponent.h"
#include "KeyboardComponent.h"
#include "ControllerComponent.h"


GamePlayState GamePlayState::sGamePlayState;


void GamePlayState::mapCommands() 
{
	/*this->commands[Commands::SELECT] = new GamePlaySelectCommand();
	this->commands[Commands::MOVEUP] = new MoveUpCommand();
	this->commands[Commands::MOVEDOWN] = new MoveDownCommand();
	this->commands[Commands::MOVELEFT] = new MoveLeftCommand();
	this->commands[Commands::MOVERIGHT] = new MoveRightCommand();
	this->commands[Commands::MOUSEMOVE] = new MouseRotateCommand();
	this->commands[Commands::CONTROLLERMOVE] = new ControllerMovementCommand();
	this->commands[Commands::CONTROLLERROTATE] = new ControllerRotationCommand();
	this->commands[Commands::SELECTABILITY1] = new SelectAbility1Command();
	this->commands[Commands::SELECTABILITY2] = new SelectAbility2Command();
	this->commands[Commands::SELECTABILITY3] = new SelectAbility3Command();
	this->commands[Commands::SELECTABILITY4] = new SelectAbility4Command();
	this->commands[Commands::FIREABILITY0] = new FireAbility0Command();
	this->commands[Commands::FIREABILITYX] = new FireAbilityXCommand();
	this->commands[Commands::OPENMENU0] = new OpenMenu0Command();
	this->commands[Commands::OPENMENU1] = new OpenMenu1Command();*/
}

void GamePlayState::mapKeys()
{
	// KEYBOARD -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	/*// Movement & Rotation
	Locator::getInputHandler()->mapCommandToKeyboardKey(KEYBOARD::W, Key(this->commands[Commands::MOVEUP], COMMANDTYPE::TAP));
	Locator::getInputHandler()->mapCommandToKeyboardKey(KEYBOARD::A, Key(this->commands[Commands::MOVELEFT], COMMANDTYPE::TAP));
	Locator::getInputHandler()->mapCommandToKeyboardKey(KEYBOARD::S, Key(this->commands[Commands::MOVEDOWN], COMMANDTYPE::TAP));
	Locator::getInputHandler()->mapCommandToKeyboardKey(KEYBOARD::D, Key(this->commands[Commands::MOVERIGHT], COMMANDTYPE::TAP));
	Locator::getInputHandler()->mapCommandToMouseKey(MOUSE::MOVE, Key(this->commands[Commands::MOUSEMOVE], COMMANDTYPE::HOLD));
	/* Rotation is handled in GamePlayState::handleEvents(); */

	/*// Selecting Abilities
	Locator::getInputHandler()->mapCommandToKeyboardKey(KEYBOARD::NUM1, Key(this->commands[Commands::SELECTABILITY1], COMMANDTYPE::TAP));
	Locator::getInputHandler()->mapCommandToKeyboardKey(KEYBOARD::NUM2, Key(this->commands[Commands::SELECTABILITY2], COMMANDTYPE::TAP));
	Locator::getInputHandler()->mapCommandToKeyboardKey(KEYBOARD::NUM3, Key(this->commands[Commands::SELECTABILITY3], COMMANDTYPE::TAP));
	Locator::getInputHandler()->mapCommandToKeyboardKey(KEYBOARD::NUM4, Key(this->commands[Commands::SELECTABILITY4], COMMANDTYPE::TAP));

	// Shoot Abilities
	Locator::getInputHandler()->mapCommandToMouseKey(MOUSE::LEFTCLICK, Key(this->commands[Commands::FIREABILITY0], COMMANDTYPE::TAP));
	Locator::getInputHandler()->mapCommandToMouseKey(MOUSE::RIGHTCLICK, Key(this->commands[Commands::FIREABILITYX], COMMANDTYPE::TAP));
	
	// Menu relevant
	Locator::getInputHandler()->mapCommandToKeyboardKey(KEYBOARD::ESC, Key(this->commands[Commands::OPENMENU0], COMMANDTYPE::TAP));


	// CONTROLLER -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	// Movement & Rotation
	Locator::getInputHandler()->mapCommandToLeftThumbStick(this->commands[Commands::CONTROLLERMOVE]);
	Locator::getInputHandler()->mapCommandToRightThumbStick(this->commands[Commands::CONTROLLERROTATE]);
	// DPAD
	Locator::getInputHandler()->mapCommandToControllerKey(CONTROLLER::DPADUP, Key(this->commands[Commands::MOVEUP], COMMANDTYPE::HOLD));
	Locator::getInputHandler()->mapCommandToControllerKey(CONTROLLER::DPADDOWN, Key(this->commands[Commands::MOVEDOWN], COMMANDTYPE::HOLD));
	Locator::getInputHandler()->mapCommandToControllerKey(CONTROLLER::DPADLEFT, Key(this->commands[Commands::MOVELEFT], COMMANDTYPE::HOLD));
	Locator::getInputHandler()->mapCommandToControllerKey(CONTROLLER::DPADRIGHT, Key(this->commands[Commands::MOVERIGHT], COMMANDTYPE::HOLD));

	// Selecting Abilities
	Locator::getInputHandler()->mapCommandToControllerKey(CONTROLLER::A, Key(this->commands[Commands::SELECTABILITY1], COMMANDTYPE::TAP));
	Locator::getInputHandler()->mapCommandToControllerKey(CONTROLLER::X, Key(this->commands[Commands::SELECTABILITY2], COMMANDTYPE::TAP));
	Locator::getInputHandler()->mapCommandToControllerKey(CONTROLLER::Y, Key(this->commands[Commands::SELECTABILITY3], COMMANDTYPE::TAP));
	Locator::getInputHandler()->mapCommandToControllerKey(CONTROLLER::B, Key(this->commands[Commands::SELECTABILITY4], COMMANDTYPE::TAP));

	// Shoot Abilities
	Locator::getInputHandler()->mapCommandToControllerKey(CONTROLLER::LTRIGGER, Key(this->commands[Commands::FIREABILITYX], COMMANDTYPE::TAP));
	Locator::getInputHandler()->mapCommandToControllerKey(CONTROLLER::RTRIGGER, Key(this->commands[Commands::FIREABILITY0], COMMANDTYPE::TAP));
	Locator::getInputHandler()->mapCommandToLeftShoulder(this->commands[Commands::FIREABILITYX]);
	Locator::getInputHandler()->mapCommandToRightShoulder(this->commands[Commands::FIREABILITY0]);
	
	// Menu relevant
	Locator::getInputHandler()->mapCommandToControllerKey(CONTROLLER::START, Key(this->commands[Commands::OPENMENU0], COMMANDTYPE::TAP));
	Locator::getInputHandler()->mapCommandToControllerKey(CONTROLLER::BACK, Key(this->commands[Commands::OPENMENU1], COMMANDTYPE::TAP));*/
}

void GamePlayState::initInputMapping()
{
	// TrueInput --> Internal 'Keys' --> Internal 'Commands' --> rest of system
	// First we map the internal 'Keys' to commands.
	this->mapCommands();
	// Then we map the trueInput to the internal 'Keys'
	this->mapKeys();
}


void GamePlayState::init()
{
	this->initArena();

	for (auto &i : this->graphics) {
		rio.addGraphics(i);
	}
}

void GamePlayState::cleanup()
{

}

void GamePlayState::pause()
{
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
}

void GamePlayState::update(GameManager * gm)
{
}

void GamePlayState::render(GameManager * gm)
{
	this->rio.render();
	gm->display(this);
}

GamePlayState* GamePlayState::getInstance()
{
	sGamePlayState.initArena();
	return &sGamePlayState;
}

void GamePlayState::initArena()
{
	this->createArenaFloor();
	this->createArenaNeonGrid();
	this->createArenaWalls();
	int test12 = 7;
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
	vColor color(72.0f, 118.0f, 255.0f, 255.0f);
	//Create the RectangleComponent and give it the finished world matrix.
	rect = new RectangleComponent(nextID, color.r, color.g, color.b, color.a);
	object->SETworldMatrix(worldM);
	//Give the RectangleComponent to the new GameObject.
	object->addComponent(rect);
	//Push the new GameObject into the arenaObject vector and graphics vector.
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
	int test3 = 4;
}

void GamePlayState::createLine(XMFLOAT3 pos, XMMATRIX wMatrix, XMFLOAT4 startColor, XMFLOAT4 endColor)
{
	GameObject* object = nullptr;
	LineComponent* line = nullptr;
	//Get ID for next object.
	int nextID = this->arenaObjects.size();
	//Create the GameObject
	object = new GameObject(nextID, pos);
	//Create the LineComponent and give it it's world matrix.
	vColor startC(startColor.x, startColor.w, startColor.z, startColor.w);
	vColor endC(startColor.x, startColor.w, startColor.z, startColor.w);
	line = new LineComponent(nextID, startC, endC);
	object->SETworldMatrix(wMatrix);
	//Add the LineComponent to the GameObject and push the GameObject into the vectors.
	object->addComponent(line);
	this->graphics.push_back(line);
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
	//Create an array with the index of the walls that will not be created. 
	//These will be the openings where the monsters can spawn.
	//The array is hardcoded to open the middle sections of each wall until
	//the randomized function is implemented.
	int skip[8] = { 3, 4, 11, 12, 21, 22, 33, 34 };
	int skipChecker = 0; //shitty implementation until we make the real one.

	//Create rotation matrix for Left and right row of walls. Rotates 90 degres around Y-axis.
	XMMATRIX rotLR = DirectX::XMMatrixRotationY((float)(PI / 2));
	//Create rotation matrix for Top and Bottom row of walls. No rotation so it will be identity matrix.
	XMMATRIX rotTB = DirectX::XMMatrixIdentity();
	//Create scale matrix for all of the walls.
	XMMATRIX scaleM = DirectX::XMMatrixScaling(LENGTHOFWALLS * ARENASQUARESIZE / 2, HEIGHTOFWALLS * ARENASQUARESIZE / 2, ARENASQUARESIZE / 2);
	//Initialize a translation matrix for future use.
	XMMATRIX translationM = DirectX::XMMatrixIdentity();
	//Inititalize worldMatrix that will be passed to the BlockComponent.
	XMMATRIX worldMatrix = DirectX::XMMatrixIdentity();
	//Create a color to be used in the BlockComponent.
	XMFLOAT4 wallColor(255.0f, 48.0f, 48.0f, 255.0f);


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
		skipChecker++;//remove when we implement the real random openings.
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
	object = new GameObject(nextID, pos);
	//Create the BlockComponent and give it it's world matrix.
	block = new BlockComponent(*object, color.x, color.y, color.z, color.w);
	object->SETworldMatrix(wMatrix);
	//Add the BlockComponent to the GameObject and push the GameObject into the vectors.
	object->addComponent(block);
	this->graphics.push_back(block);
	this->arenaObjects.push_back(object);


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
		object = new GameObject(nextID, currPos);
		vec = DirectX::XMLoadFloat3(&currPos);
		//Prepare the new lines world matrix.
		translationM = DirectX::XMMatrixTranslationFromVector(vec);
		worldMatrix = scaleMH * rotMH * translationM;
		//Create the new LineComponent and hand it it's world matrix.
		currentLine = new LineComponent(nextID, startColor, endColor);
		object->SETworldMatrix(worldMatrix);
		//Give the new GameObject the LineComponent and push them into their vectors for storage.
		object->addComponent(currentLine);
		this->arenaObjects.push_back(object);
		this->graphics.push_back(currentLine);

		//Calculate the parallel line and do the same steps as above.
		parallelPos = currPos + parallelStep;
		nextID = this->arenaObjects.size();
		object = new GameObject(nextID, parallelPos);
		vec = DirectX::XMLoadFloat3(&parallelPos);
		translationM = DirectX::XMMatrixTranslationFromVector(vec);
		worldMatrix = scaleMH * rotMH * translationM;
		currentLine = new LineComponent(nextID, startColor, endColor);
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
		object = new GameObject(nextID, currPos);
		vec = DirectX::XMLoadFloat3(&currPos);
		//Prepare the lines world Matrix.
		translationM = DirectX::XMMatrixTranslationFromVector(vec);
		worldMatrix = scaleMV * rotMV * translationM;
		//Create the new LineComponent and hand it it's world matrix.
		currentLine = new LineComponent(nextID, startColor, endColor);
		object->SETworldMatrix(worldMatrix);
		//Give the GameObject the LineComponent and push them into their vectors for storage.
		object->addComponent(currentLine);
		this->arenaObjects.push_back(object);
		this->graphics.push_back(currentLine);

		//Calculate the parallel line and do the same steps as above.
		parallelPos = currPos + parallelStep;
		nextID = this->arenaObjects.size();
		object = new GameObject(nextID, parallelPos);
		vec = DirectX::XMLoadFloat3(&parallelPos);
		translationM = DirectX::XMMatrixTranslationFromVector(vec);
		worldMatrix = scaleMV * rotMV * translationM;
		currentLine = new LineComponent(nextID, startColor, endColor);
		object->SETworldMatrix(worldMatrix);
		object->addComponent(currentLine);
		this->arenaObjects.push_back(object);
		this->graphics.push_back(currentLine);

		//Prepare currPos for next iteration.
		currPos = currPos + stepL;
	}
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