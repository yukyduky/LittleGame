#include "InputComponent.h"
#include "GameObject.h"
#include "Locator.h"
#include "Commands.h"


std::unordered_map<KEYBOARD::KEY, size_t> InputComponent::keyboardKeyMap;
std::unordered_map<MOUSE::KEY, size_t> InputComponent::mouseKeyMap;
std::unordered_map<CONTROLLER::KEY, size_t> InputComponent::controllerKeyMap;
Command* InputComponent::commands[Commands::Size] = {};

std::map<size_t, Key> InputComponent::keyboardCommandMap;
std::map<size_t, Key> InputComponent::mouseCommandMap;
std::map<size_t, Key> InputComponent::controllerCommandMap;

void InputComponent::mapCommands()
{
	commands[Commands::SELECT] = new CommandSelect();
	commands[Commands::MOVEUP] = new CommandMoveUp();
	commands[Commands::MOVEDOWN] = new CommandMoveDown();
	commands[Commands::MOVELEFT] = new CommandMoveLeft();
	commands[Commands::MOVERIGHT] = new CommandMoveRight();
	commands[Commands::MOUSEMOVE] = new CommandRotate();
	commands[Commands::CONTROLLERMOVE] = new CommandControllerMove();
	commands[Commands::CONTROLLERROTATE] = new CommandRotate();
	commands[Commands::SELECTABILITY1] = new CommandSelectAbility1();
	commands[Commands::SELECTABILITY2] = new CommandSelectAbility2();
	commands[Commands::SELECTABILITY3] = new CommandSelectAbility3();
	commands[Commands::SELECTABILITY4] = new CommandSelectAbility4();
	commands[Commands::FIREABILITY0] = new CommandFireAbility0();
	commands[Commands::FIREABILITYX] = new CommandFireAbilityX();
	commands[Commands::OPENMENU0] = new CommandOpenMenu0();
	commands[Commands::OPENMENU1] = new CommandOpenMenu1();
}

void InputComponent::mapKeys()
{
	// KEYBOARD -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	// Movement & Rotation
	mapKeyboardKeyToCommand(Key(commands[Commands::MOVEUP], COMMANDTYPE::TAP), KEYBOARD::W);
	mapKeyboardKeyToCommand(Key(commands[Commands::MOVELEFT], COMMANDTYPE::TAP), KEYBOARD::A);
	mapKeyboardKeyToCommand(Key(commands[Commands::MOVEDOWN], COMMANDTYPE::TAP), KEYBOARD::S);
	mapKeyboardKeyToCommand(Key(commands[Commands::MOVERIGHT], COMMANDTYPE::TAP), KEYBOARD::D);
	mapMouseKeyToCommand(Key(commands[Commands::MOUSEMOVE], COMMANDTYPE::HOLD), MOUSE::MOVE);
	/* Rotation is handled in GamePlayState::handleEvents(); */

	// Selecting Abilities
	mapKeyboardKeyToCommand(Key(commands[Commands::SELECTABILITY1], COMMANDTYPE::TAP), KEYBOARD::NUM1);
	mapKeyboardKeyToCommand(Key(commands[Commands::SELECTABILITY2], COMMANDTYPE::TAP), KEYBOARD::NUM2);
	mapKeyboardKeyToCommand(Key(commands[Commands::SELECTABILITY3], COMMANDTYPE::TAP), KEYBOARD::NUM3);
	mapKeyboardKeyToCommand(Key(commands[Commands::SELECTABILITY4], COMMANDTYPE::TAP), KEYBOARD::NUM4);

	// Shoot Abilities
	mapMouseKeyToCommand(Key(commands[Commands::FIREABILITY0], COMMANDTYPE::TAP), MOUSE::LEFTCLICK);
	mapMouseKeyToCommand(Key(commands[Commands::FIREABILITYX], COMMANDTYPE::TAP), MOUSE::RIGHTCLICK);

	// Menu relevant
	mapKeyboardKeyToCommand(Key(commands[Commands::OPENMENU0], COMMANDTYPE::TAP), KEYBOARD::ESC);


	// CONTROLLER -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
	// Movement & Rotation
	mapLeftThumbStickToCommand(commands[Commands::CONTROLLERMOVE]);
	mapRightThumbStickToCommand(commands[Commands::CONTROLLERROTATE]);
	// DPAD
	mapControllerKeyToCommand(Key(commands[Commands::MOVEUP], COMMANDTYPE::HOLD), CONTROLLER::DPADUP);
	mapControllerKeyToCommand(Key(commands[Commands::MOVEDOWN], COMMANDTYPE::HOLD), CONTROLLER::DPADDOWN);
	mapControllerKeyToCommand(Key(commands[Commands::MOVELEFT], COMMANDTYPE::HOLD), CONTROLLER::DPADLEFT);
	mapControllerKeyToCommand(Key(commands[Commands::MOVERIGHT], COMMANDTYPE::HOLD), CONTROLLER::DPADRIGHT);

	// Selecting Abilities
	mapControllerKeyToCommand(Key(commands[Commands::SELECTABILITY1], COMMANDTYPE::TAP), CONTROLLER::A);
	mapControllerKeyToCommand(Key(commands[Commands::SELECTABILITY2], COMMANDTYPE::TAP), CONTROLLER::X);
	mapControllerKeyToCommand(Key(commands[Commands::SELECTABILITY3], COMMANDTYPE::TAP), CONTROLLER::Y);
	mapControllerKeyToCommand(Key(commands[Commands::SELECTABILITY4], COMMANDTYPE::TAP), CONTROLLER::B);

	// Shoot Abilities
	mapControllerKeyToCommand(Key(commands[Commands::FIREABILITYX], COMMANDTYPE::TAP), CONTROLLER::LTRIGGER);
	mapControllerKeyToCommand(Key(commands[Commands::FIREABILITY0], COMMANDTYPE::TAP), CONTROLLER::RTRIGGER);
	mapLeftShoulderToCommand(commands[Commands::FIREABILITYX]);
	mapRightShoulderToCommand(commands[Commands::FIREABILITY0]);

	// Menu relevant
	mapControllerKeyToCommand(Key(commands[Commands::OPENMENU0], COMMANDTYPE::TAP), CONTROLLER::START);
	mapControllerKeyToCommand(Key(commands[Commands::OPENMENU1], COMMANDTYPE::TAP), CONTROLLER::BACK);
}

void InputComponent::mapKeyCodesToEnums()
{
	// WARNING!!
	// "i" needs to correspond to the order in KEYBOARD::KEY, CONTROLLER::KEY and MOUSE::KEY
	//

	// Keyboard
	int i = 0;
	// 48 is '0' in decimal
	int k = 48;

	// Maps keys 0-9
	for (i = 0; i < 10; i++) {
		keyboardKeyMap.insert(keyboardKeyMap.end(), std::pair<KEYBOARD::KEY, size_t>(static_cast<KEYBOARD::KEY>(i), k++));
	}

	// 65 is 'A' in decimal
	k = 65;
	// Maps keys A-Z
	for (; i < 26 + 10; i++) {
		keyboardKeyMap.insert(keyboardKeyMap.end(), std::pair<KEYBOARD::KEY, size_t>(static_cast<KEYBOARD::KEY>(i), k++));
	}

	// Map ESCAPE to enum (Mapped to index = i with the hexadecimal value of 27)
	keyboardKeyMap.insert(keyboardKeyMap.end(), std::pair<KEYBOARD::KEY, size_t>(static_cast<KEYBOARD::KEY>(i), 27));


	k = 1;
	// Mouse
	for (i = 0; i < 2; i++) {
		mouseKeyMap.insert(mouseKeyMap.end(), std::pair<MOUSE::KEY, size_t>(static_cast<MOUSE::KEY>(i), k++));
	}

	// Controller
	k = 1;
	// Maps all the controller buttons
	for (i = 0; i < CONTROLLER::SIZE - 6; i++) {
		controllerKeyMap.insert(controllerKeyMap.end(), std::pair<CONTROLLER::KEY, size_t>(static_cast<CONTROLLER::KEY>(i), k));
		k *= 2;
	}
	k *= 4;
	for (; i < CONTROLLER::SIZE; i++) {
		controllerKeyMap.insert(controllerKeyMap.end(), std::pair<CONTROLLER::KEY, size_t>(static_cast<CONTROLLER::KEY>(i), k));
		k *= 2;
	}

	// Map LSHOULDER & RSHOULDER
	// LSHOULDER
	controllerKeyMap.insert(controllerKeyMap.end(), std::pair<CONTROLLER::KEY, size_t>(static_cast<CONTROLLER::KEY>(i++), 15));
	// RSHOULDER
	controllerKeyMap.insert(controllerKeyMap.end(), std::pair<CONTROLLER::KEY, size_t>(static_cast<CONTROLLER::KEY>(i++), 16));
}

void InputComponent::update()
{
	this->generateCommands();
	this->execute();
}

void InputComponent::init()
{
	mapKeyCodesToEnums();
	mapCommands();
	mapKeys();
}

void InputComponent::vibrate(unsigned short left, unsigned short right)
{
}

void InputComponent::mapKeyboardKeyToCommand(Key key, KEYBOARD::KEY enumKey)
{
	// Finds the keycode that corresponds with the provided enum and adds the command to the current keyboard map
	keyboardCommandMap.insert(keyboardCommandMap.end(), std::pair<size_t, Key>(keyboardKeyMap[enumKey], key));
}

void InputComponent::mapMouseKeyToCommand(Key key, MOUSE::KEY enumKey)
{
	// Finds the keycode that corresponds with the provided enum and adds the command to the current controller map
	mouseCommandMap.insert(mouseCommandMap.end(), std::pair<size_t, Key>(mouseKeyMap[enumKey], key));
}

void InputComponent::mapControllerKeyToCommand(Key key, CONTROLLER::KEY enumKey)
{
	// Finds the keycode that corresponds with the provided enum and adds the command to the current controller map
	controllerCommandMap.insert(controllerCommandMap.end(), std::pair<size_t, Key>(controllerKeyMap[enumKey], key));
}

void InputComponent::mapLeftThumbStickToCommand(Command* command)
{
	controllerCommandMap.insert(
		controllerCommandMap.end(),
		std::pair<size_t, Key>(CONTROLLER::LTHUMB, Key(command, COMMANDTYPE::HOLD))
	);
}

void InputComponent::mapRightThumbStickToCommand(Command* command)
{
	controllerCommandMap.insert(
		controllerCommandMap.end(),
		std::pair<size_t, Key>(CONTROLLER::RTHUMB, Key(command, COMMANDTYPE::HOLD))
	);
}

void InputComponent::mapLeftShoulderToCommand(Command* command)
{
	controllerCommandMap.insert(
		controllerCommandMap.end(),
		std::pair<size_t, Key>(CONTROLLER::LSHOULDER, Key(command, COMMANDTYPE::HOLD))
	);
}

void InputComponent::mapRightShoulderToCommand(Command* command)
{
	controllerCommandMap.insert(
		controllerCommandMap.end(),
		std::pair<size_t, Key>(CONTROLLER::RSHOULDER, Key(command, COMMANDTYPE::HOLD))
	);
}

void InputComponent::remapKeyboardKey(size_t vkc, Key key)
{
	// Overwrites the command with a new one at the corresponding keyboard keycode location
	keyboardCommandMap[vkc] = key;
}

void InputComponent::remapMouseKey(size_t vkc, Key key)
{
	// Overwrites the command with a new one at the corresponding mouse keycode location
	mouseCommandMap[vkc] = key;
}

void InputComponent::remapControllerKey(size_t vkc, Key key)
{
	// Overwrites the command with a new one at the corresponding controller keycode location
	controllerCommandMap[vkc] = key;
}

void InputComponent::resetKeyBindings()
{
	keyboardCommandMap.clear();
	mouseCommandMap.clear();
	controllerCommandMap.clear();
	init();
}

XMFLOAT2 InputComponent::GETnormalizedVectorOfLeftStick()
{

	return XMFLOAT2(1.0f, 1.0f);
}

XMFLOAT2 InputComponent::GETnormalizedVectorOfRightStick()
{
	return XMFLOAT2(1.0f, 1.0f);
}

float InputComponent::GETnormalizedValueOfLeftTrigger()
{
	return 1.0f;
}

float InputComponent::GETnormalizedValueOfRightTrigger()
{
	return 1.0f;
}

XMFLOAT2 InputComponent::GETcursorPos()
{
	return XMFLOAT2(0.0f, 0.0f);
}

void InputComponent::cleanup()
{
	for (auto &i : commands) {
		delete i;
		i = nullptr;
	}
	while (keyboardKeyMap.size() > 0) {
		keyboardKeyMap.erase(keyboardKeyMap.begin());
	}
	while (mouseKeyMap.size() > 0) {
		mouseKeyMap.erase(mouseKeyMap.begin());
	}
	while (controllerKeyMap.size() > 0) {
		controllerKeyMap.erase(controllerKeyMap.begin());
	}
}
