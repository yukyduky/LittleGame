#include "InputComponent.h"
#include "GameObject.h"
#include "Locator.h"

std::unordered_map<KEYBOARD::KEY, size_t> InputComponent::keyboardKeyMap;
std::unordered_map<MOUSE::KEY, size_t> InputComponent::mouseKeyMap;
std::unordered_map<CONTROLLER::KEY, size_t> InputComponent::controllerKeyMap;

std::map<size_t, Key> InputComponent::keyboardCommandMap;
std::map<size_t, Key> InputComponent::mouseCommandMap;
std::map<size_t, Key> InputComponent::controllerCommandMap;

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

InputComponent::InputComponent(GameObject & obj) : ID(obj.getID())
{
}

const size_t InputComponent::getID()
{
	return this->ID;
}

void InputComponent::init()
{
	mapKeyCodesToEnums();
}

void InputComponent::execute()
{
	for (auto &i : this->commandQueue) {
		//i->execute(this->head); // TODO INPUT
	}
	this->commandQueue.clear();
}

void InputComponent::vibrate(size_t left, size_t right)
{
}

void InputComponent::mapKeyboardKeyToCommand(Key key, KEYBOARD::KEY enumKey)
{
	// Finds the keycode that corresponds with the provided enum and adds the command to the current keyboard map
	this->keyboardCommandMap.insert(this->keyboardCommandMap.end(), std::pair<size_t, Key>(this->keyboardKeyMap[enumKey], key));
}

void InputComponent::mapMouseKeyToCommand(Key key, MOUSE::KEY enumKey)
{
	// Finds the keycode that corresponds with the provided enum and adds the command to the current controller map
	this->mouseCommandMap.insert(this->mouseCommandMap.end(), std::pair<size_t, Key>(this->mouseKeyMap[enumKey], key));
}

void InputComponent::mapControllerKeyToCommand(Key key, CONTROLLER::KEY enumKey)
{
	// Finds the keycode that corresponds with the provided enum and adds the command to the current controller map
	this->controllerCommandMap.insert(this->controllerCommandMap.end(), std::pair<size_t, Key>(this->controllerKeyMap[enumKey], key));
}

void InputComponent::remapKeyboardKey(size_t vkc, Key key)
{
	// Overwrites the command with a new one at the corresponding keyboard keycode location
	this->keyboardCommandMap[vkc] = key;
}

void InputComponent::remapMouseKey(size_t vkc, Key key)
{
	// Overwrites the command with a new one at the corresponding mouse keycode location
	this->mouseCommandMap[vkc] = key;
}

void InputComponent::remapControllerKey(size_t vkc, Key key)
{
	// Overwrites the command with a new one at the corresponding controller keycode location
	this->controllerCommandMap[vkc] = key;
}

void InputComponent::resetKeyBindings()
{
	this->keyboardCommandMap.clear();
	this->mouseCommandMap.clear();
	this->controllerCommandMap.clear();
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
