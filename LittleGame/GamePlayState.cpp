#include "GamePlayState.h"
#include "GameManager.h"
#include "Locator.h"
#include "BlockComponent.h"
#include "KeyboardComponent.h"
#include "ControllerComponent.h"


GamePlayState GamePlayState::sGamePlayState;


void GamePlayState::mapCommands()  {
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

void GamePlayState::mapKeys() {
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

void GamePlayState::initInputMapping() {
	// TrueInput --> Internal 'Keys' --> Internal 'Commands' --> rest of system
	// First we map the internal 'Keys' to commands.
	this->mapCommands();
	// Then we map the trueInput to the internal 'Keys'
	this->mapKeys();
}


void GamePlayState::init() {
	this->go = new GameObject(0);
	this->playerInput[0] = new KeyboardComponent(*this->go);

	this->initInputMapping();
	//this->selectCommand = new GamePlaySelectCommand();
	this->mapKeys();

	this->blocks.push_back(new BlockComponent(*this->go, 0.0f, 1.0f, 0.0f, 1.0f));

	for (auto &i : this->blocks) {
		this->rio.addGraphics(i);
	}
}

void GamePlayState::cleanup() {
	for (int i = 0; i < Commands::Size; i++) {
		delete commands[i];
	}
}

void GamePlayState::pause() {

}

void GamePlayState::resume() {
	this->mapKeys();
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

void GamePlayState::update(GameManager * gm) {

}

void GamePlayState::render(GameManager * gm) {
	this->rio.render();
	gm->display(this);
}

GamePlayState* GamePlayState::getInstance() {
	return &sGamePlayState;
}
