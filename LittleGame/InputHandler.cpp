#include "InputHandler.h"


void InputHandler::mapKeyCodesToEnums()
{
	// Keyboard
	int i = 0;
	// 48 is '0' in decimal
	int k = 48;
	// Maps keys 0-9
	for (i = 0; i < 10; i++) {
		this->keyboardKeyMap.insert(this->keyboardKeyMap.end(), std::pair<KEYBOARD::KEYS, size_t>(static_cast<KEYBOARD::KEYS>(i), k++));
	}

	// 65 is 'A' in decimal
	k = 65;
	// Maps keys A-Z
	for (; i < 26 + 10; i++) {
		this->keyboardKeyMap.insert(this->keyboardKeyMap.end(), std::pair<KEYBOARD::KEYS, size_t>(static_cast<KEYBOARD::KEYS>(i), k++));
	}
	
	// Controller
	k = 1;
	// Maps all the controller buttons
	for (i = 0; i < CONTROLLER::SIZE - 4; i++) {
		this->controllerKeyMap.insert(this->controllerKeyMap.end(), std::pair<CONTROLLER::KEYS, size_t>(static_cast<CONTROLLER::KEYS>(i), k));
		k *= 2;
	}
	k *= 4;
	for (; i < CONTROLLER::SIZE; i++) {
		this->controllerKeyMap.insert(this->controllerKeyMap.end(), std::pair<CONTROLLER::KEYS, size_t>(static_cast<CONTROLLER::KEYS>(i), k));
		k *= 2;
	}
}

void InputHandler::updateKeyboard(std::vector<Input>& commandQueue)
{
	// Iterates through all the keyboard keys that have a mapped command to them
	for (auto &it : this->keyboardCommandMap) {
		// GetAsyncKeyState returns true if key is pressed and it was not pressed last frame
		if (GetAsyncKeyState(it.first) && it.second.type == COMMANDTYPE::TAP) {
			commandQueue.push_back(Input(it.second.command, 0));
		}
		// GetKeyState returns true if key is pressed
		else if (GetKeyState(it.first) && it.second.type == COMMANDTYPE::HOLD) {
			commandQueue.push_back(Input(it.second.command, 0));
		}
	}
}

void InputHandler::updateControllers(std::vector<Input>& commandQueue)
{
	XINPUT_STATE nextState;
	// Iterates through the max number of controllers
	for (int i = 0; i < this->controllerStates.size(); i++) {
		ZeroMemory(&nextState, sizeof(XINPUT_STATE));

		// Gets the new state of the controller if it is connected
		DWORD result = XInputGetState(i, &nextState);
		// If it is connected then result = ERROR_SUCCESS
		if (result == ERROR_SUCCESS) {
			// Iterates through all the controller buttons that have a mapped command to them
			for (auto &it : this->controllerCommandMap) {
				// If the key is being pressed and was pressed last frame and type is HOLD: continue
				if (nextState.Gamepad.wButtons & it.first && this->controllerStates[i].Gamepad.wButtons & it.first && it.second.type == COMMANDTYPE::HOLD) {
					commandQueue.push_back(Input(it.second.command, i + 1));
				}
				// If the key is being pressed and was not pressed last frame and type is TAP: continue
				else if (nextState.Gamepad.wButtons & it.first && this->controllerStates[i].Gamepad.wButtons ^ it.first && it.second.type == COMMANDTYPE::TAP) {
					commandQueue.push_back(Input(it.second.command, i + 1));
				}
			}

			float LX = this->controllerStates[i].Gamepad.sThumbLX;
			float LY = this->controllerStates[i].Gamepad.sThumbLY;
			float RX = this->controllerStates[i].Gamepad.sThumbRX;
			float RY = this->controllerStates[i].Gamepad.sThumbRY;

			float magL = sqrt(pow(LX, 2) + pow(LY, 2));
			float magR = sqrt(pow(RX, 2) + pow(RY, 2));

			LX /= magL;
			LY /= magL;
			RX /= magR;
			RY /= magR;

			if (magL > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE) {
				if (magL > 32767) {
					magL = 32767;
				}

				magL -= XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;

				magL /= 32767 - XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE;
			}
			else {
				magL = 0.0f;
			}
			if (magR > XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE) {
				if (magR > 32767) {
					magR = 32767;
				}

				magR -= XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;

				magR /= 32767 - XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE;
			}
			else {
				magR = 0.0f;
			}

			if (this->thumbLSet && magL != 0.0f) {
				commandQueue.push_back(Input(this->controllerCommandMap[CONTROLLER::LTHUMB].command, i + 1));
			}
			if (this->thumbRSet && magR != 0.0f) {
				commandQueue.push_back(Input(this->controllerCommandMap[CONTROLLER::RTHUMB].command, i + 1));
			}


			// Update the current state of the controller
			this->controllerStates[i] = nextState;
		}
	}
}

InputHandler::InputHandler()
{
	this->mapKeyCodesToEnums();
	this->thumbLSet = false;
	this->thumbRSet = false;
}

void InputHandler::update(std::vector<Input>& commandQueue)
{
	updateKeyboard(commandQueue);
	updateControllers(commandQueue);
}

void InputHandler::mapCommandToKeyboardKey(KEYBOARD::KEYS enumKey, Key key)
{
	// Finds the keycode that corresponds with the provided enum and adds the command to the current keyboard map
	this->keyboardCommandMap.insert(this->keyboardCommandMap.end(), std::pair<size_t, Key>(this->keyboardKeyMap[enumKey], key));
}

void InputHandler::mapCommandToControllerKey(CONTROLLER::KEYS enumKey, Key key)
{
	// Finds the keycode that corresponds with the provided enum and adds the command to the current controller map
	this->controllerCommandMap.insert(this->controllerCommandMap.end(), std::pair<size_t, Key>(this->controllerKeyMap[enumKey], key));
}

void InputHandler::mapCommandToLeftThumbStick(Command * command)
{
	this->controllerCommandMap.insert(this->controllerCommandMap.end(), std::pair<size_t, Key>(CONTROLLER::LTHUMB, Key(command, COMMANDTYPE::HOLD)));
	this->thumbLSet = true;
}

void InputHandler::mapCommandToRightThumbStick(Command * command)
{
	this->controllerCommandMap.insert(this->controllerCommandMap.end(), std::pair<size_t, Key>(CONTROLLER::RTHUMB, Key(command, COMMANDTYPE::HOLD)));
	this->thumbRSet = true;
}

void InputHandler::remapKeyboardKey(size_t vkc, Key key)
{
	// Overwrites the command with a new one at the corresponding keyboard keycode location
	this->keyboardCommandMap[vkc] = key;
}

void InputHandler::remapControllerKey(size_t vkc, Key key)
{
	// Overwrites the command with a new one at the corresponding controller keycode location
	this->controllerCommandMap[vkc] = key;
}

void InputHandler::resetKeyBindings()
{
	this->keyboardCommandMap.clear();
	this->controllerCommandMap.clear();
	this->thumbLSet = false;
	this->thumbRSet = false;
}

void InputHandler::vibrate(size_t controllerID, int left, int right)
{
	// Create a Vibraton State
	XINPUT_VIBRATION vib;
	// Clear the Vibration
	ZeroMemory(&vib, sizeof(XINPUT_VIBRATION));

	// Set the Vibration Values
	vib.wLeftMotorSpeed = left;
	vib.wRightMotorSpeed = right;

	// Vibrate the controller
	XInputSetState(controllerID, &vib);
}
