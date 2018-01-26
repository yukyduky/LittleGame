#include "ControllerComponent.h"
#include "GameObject.h"


float ControllerComponent::checkThumb(THUMB thumb, size_t deadzone, XINPUT_STATE state)
{
	XMFLOAT2 axis;

	// Checks for movement on either LTHUMB or RTHUMB
	if (thumb == THUMB::LTHUMB) {
		axis.x = state.Gamepad.sThumbLX;
		axis.y = state.Gamepad.sThumbLY;
	}
	else {
		axis.x = state.Gamepad.sThumbRX;
		axis.y = state.Gamepad.sThumbRY;
	}

	float mag = sqrt(pow(axis.x, 2) + pow(axis.y, 2));

	axis.x /= mag;
	axis.y /= mag;

	if (mag > deadzone) {
		if (mag > 32767) {
			mag = 32767;
		}

		mag -= deadzone;

		mag /= 32767 - deadzone;
	}
	else {
		mag = 0.0f;
	}

	return mag;
}

ControllerComponent::ControllerComponent(GameObject& obj, size_t controllerID) : InputComponent(obj), controllerID(controllerID)
{
	ZeroMemory(&this->currentState, sizeof(XINPUT_STATE));
	XInputGetState(this->controllerID, &this->currentState);

	this->thumbLSet = false;
	this->thumbRSet = false;
}

void ControllerComponent::receive(GameObject & obj, Message msg)
{
}

void ControllerComponent::generateCommands()
{
	XINPUT_STATE nextState;
	ZeroMemory(&nextState, sizeof(XINPUT_STATE));

	DWORD result = XInputGetState(this->controllerID, &nextState);

	if (result == ERROR_SUCCESS && this->currentState.dwPacketNumber != nextState.dwPacketNumber) {
		// Iterates through all the controller buttons except LSHOULDER & RSHOULDER
		for (auto &it : this->controllerCommandMap) {

			// If the key is being pressed and was pressed last frame and type is HOLD: continue
			if (nextState.Gamepad.wButtons == it.first && this->currentState.Gamepad.wButtons == it.first && it.second.type == COMMANDTYPE::HOLD) {
				this->commandQueue.push_back(it.second.command);
			}
			// If the key is being pressed and was not pressed last frame and type is TAP: continue
			else if (nextState.Gamepad.wButtons == it.first && this->currentState.Gamepad.wButtons != it.first && it.second.type == COMMANDTYPE::TAP) {
				this->commandQueue.push_back(it.second.command);
			}
		}


		if (this->thumbLSet) {
			float mag = this->checkThumb(THUMB::LTHUMB, XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE, nextState);
			// Send commands that either the left or the right thumbstick has been moved.
			if (mag != 0.0f) {
				commandQueue.push_back(this->controllerCommandMap[CONTROLLER::LTHUMB].command);
				this->thumbLDir = { nextState.Gamepad.sThumbLX, nextState.Gamepad.sThumbLY };
			}
			else {
				this->thumbLDir = { 0.0f, 0.0f };
			}
		}
		if (this->thumbRSet) {
			float mag = this->checkThumb(THUMB::RTHUMB, XINPUT_GAMEPAD_RIGHT_THUMB_DEADZONE, nextState);
			if (mag != 0.0f) {
				commandQueue.push_back(this->controllerCommandMap[CONTROLLER::RTHUMB].command);
				this->thumbRDir = { nextState.Gamepad.sThumbRX, nextState.Gamepad.sThumbRY };
			}
			else {
				this->thumbRDir = { 0.0f, 0.0f };
			}
		}
		
		// Check if either LSHOULDER or RSHOULDER was triggered
		if (nextState.Gamepad.bLeftTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
			commandQueue.push_back(this->controllerCommandMap[CONTROLLER::LSHOULDER].command);
			this->trigLValue = nextState.Gamepad.bLeftTrigger;
		}
		else {
			this->trigLValue = 0;
		}
		if (nextState.Gamepad.bRightTrigger > XINPUT_GAMEPAD_TRIGGER_THRESHOLD) {
			commandQueue.push_back(this->controllerCommandMap[CONTROLLER::RSHOULDER].command);
			this->trigRValue = nextState.Gamepad.bRightTrigger;
		}
		else {
			this->trigRValue = 0;
		}

		this->currentState = nextState;
	}
}

void ControllerComponent::execute()
{
}

void ControllerComponent::vibrate(size_t left, size_t right)
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

