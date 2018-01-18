#include "InputHandler.h"


void InputHandler::mapEnumToVKC()
{
	// Keyboard
	int i = 0;
	for (i = 0; i < 10; i++) {
		this->keyboardMap.insert(this->keyboardMap.end(), std::pair<KEYBOARD::KEYS, UINT>(static_cast<KEYBOARD::KEYS>(i), 30 + i));
	}

	for (; i < 26 + 10; i++) {
		this->keyboardMap.insert(this->keyboardMap.end(), std::pair<KEYBOARD::KEYS, UINT>(static_cast<KEYBOARD::KEYS>(i), 31 + i));
	}
	/*UINT test0 = VK_PAD_A;
	UINT test1 = VK_PAD_B;
	UINT test2 = VK_PAD_X;
	UINT test3 = VK_PAD_Y;
	UINT test4 = VK_PAD_RSHOULDER;
	UINT test5 = VK_PAD_LSHOULDER;
	UINT test6 = VK_PAD_LTRIGGER;
	UINT test7 = VK_PAD_RTRIGGER;
	UINT test8 = VK_PAD_DPAD_UP;
	UINT test9 = VK_PAD_DPAD_DOWN;
	UINT test10 = VK_PAD_DPAD_LEFT;
	UINT test11 = VK_PAD_DPAD_RIGHT;
	UINT test12 = VK_PAD_START;
	UINT test13 = VK_PAD_BACK;
	UINT test14 = VK_PAD_LTHUMB_PRESS;
	UINT test15 = VK_PAD_RTHUMB_PRESS;
	UINT test16 = VK_PAD_LTHUMB_UP;
	UINT test17 = VK_PAD_LTHUMB_DOWN;
	UINT test18 = VK_PAD_LTHUMB_RIGHT;
	UINT test19 = VK_PAD_LTHUMB_LEFT;
	UINT test20 = VK_PAD_LTHUMB_UPLEFT;
	UINT test21 = VK_PAD_LTHUMB_UPRIGHT;
	UINT test22 = VK_PAD_LTHUMB_DOWNRIGHT;
	UINT test23 = VK_PAD_LTHUMB_DOWNLEFT;
	UINT test24 = VK_PAD_RTHUMB_UP;
	UINT test25 = VK_PAD_RTHUMB_DOWN;
	UINT test26 = VK_PAD_RTHUMB_RIGHT;
	UINT test27 = VK_PAD_RTHUMB_LEFT;
	UINT test28 = VK_PAD_RTHUMB_UPLEFT;
	UINT test29 = VK_PAD_RTHUMB_UPRIGHT;
	UINT test30 = VK_PAD_RTHUMB_DOWNRIGHT;
	UINT test31 = VK_PAD_RTHUMB_DOWNLEFT;*/
	//UINT test0 = XINPUT_GAMEPAD_DPAD_UP;
	//UINT test1 = XINPUT_GAMEPAD_START;

	UINT test1 = XINPUT_GAMEPAD_DPAD_UP;
	UINT test2 = XINPUT_GAMEPAD_DPAD_DOWN;
	UINT test3 = XINPUT_GAMEPAD_DPAD_LEFT;
	UINT test4 = XINPUT_GAMEPAD_DPAD_RIGHT;
	UINT test5 = XINPUT_GAMEPAD_START;
	UINT test6 = XINPUT_GAMEPAD_BACK;
	UINT test7 = XINPUT_GAMEPAD_LEFT_THUMB;
	UINT test8 = XINPUT_GAMEPAD_RIGHT_THUMB;
	UINT test9 = XINPUT_GAMEPAD_LEFT_SHOULDER;
	UINT test10 = XINPUT_GAMEPAD_RIGHT_SHOULDER;
	UINT test11 = XINPUT_GAMEPAD_A;
	UINT test12 = XINPUT_GAMEPAD_B;
	UINT test13 = XINPUT_GAMEPAD_X;
	UINT test14 = XINPUT_GAMEPAD_Y;

	// Controller
	int k = 1;
	for (i = 0; i < 14; i++) {
		this->controllerMap.insert(this->controllerMap.end(), std::pair<CONTROLLER::KEYS, UINT>(static_cast<CONTROLLER::KEYS>(i), k));
		k *= 2;
	}

	/*for (i = 0; i < 36 + 8; i++) {
		this->controllerMap.insert(this->controllerMap.end(), std::pair<CONTROLLER::KEYS, UINT>(static_cast<CONTROLLER::KEYS>(i), 22528 + i));
	}

	for (; i < 44 + 8; i++) {
		this->controllerMap.insert(this->controllerMap.end(), std::pair<CONTROLLER::KEYS, UINT>(static_cast<CONTROLLER::KEYS>(i), 9 + 22528 + i));
	}

	for (; i < 52 + 8; i++) {
		this->controllerMap.insert(this->controllerMap.end(), std::pair<CONTROLLER::KEYS, UINT>(static_cast<CONTROLLER::KEYS>(i), (2 * 9) + 22528 + i));
	}

	for (; i < 60 + 8; i++) {
		this->controllerMap.insert(this->controllerMap.end(), std::pair<CONTROLLER::KEYS, UINT>(static_cast<CONTROLLER::KEYS>(i), (3 * 9) + 22528 + i));
	}*/
}

void InputHandler::updateKeyboard(std::vector<Command*> commandQueue)
{
	for (auto &it : this->commandMap) {
		if (GetAsyncKeyState(it.first) && it.second.type == COMMANDTYPE::TAP) {
			commandQueue.push_back(it.second.command);
		}
		else if (GetKeyState(it.first) && it.second.type == COMMANDTYPE::HOLD) {
			commandQueue.push_back(it.second.command);
		}
	}
}

void InputHandler::updateControllers(std::vector<Command*> commandQueue)
{
	XINPUT_STATE nextState;
	/*for (int i = 0; i < 4; i++) {
		XINPUT_STATE nextState;
		ZeroMemory(&nextState, sizeof(XINPUT_STATE));

		DWORD result = XInputGetState(i, &nextState);

		if (result == ERROR_SUCCESS) {
			
		}
	}*/

	DWORD result = XInputGetState(0, &nextState);

}

InputHandler::InputHandler()
{
	this->mapEnumToVKC();
}

void InputHandler::update(std::vector<Command*> commandQueue)
{
	updateKeyboard(commandQueue);
	updateControllers(commandQueue);
}

void InputHandler::mapEnumToKey(KEYBOARD::KEYS enumKey, Key key)
{
	this->commandMap.insert(this->commandMap.end(), std::pair<UINT, Key>(this->keyboardMap[enumKey], key));
}

void InputHandler::remapVKCToKey(UINT vkc, Key key)
{
	this->commandMap[vkc] = key;
}
