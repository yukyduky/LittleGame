#pragma once
#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include "IInputHandler.h"
#include <array>
#include <Windows.h>
#include <Xinput.h>
#include <map>
#include <unordered_map>

const int MAX_NUM_CONTROLLERS = 4;

class InputHandler : public IInputHandler
{
private:
	std::map<size_t, Key> keyboardCommandMap;
	std::map<size_t, Key> controllerCommandMap;
	std::unordered_map<KEYBOARD::KEYS, size_t> keyboardKeyMap;
	std::unordered_map<CONTROLLER::KEYS, size_t> controllerKeyMap;
	std::array<XINPUT_STATE, MAX_NUM_CONTROLLERS> controllerStates;
	bool thumbLSet;
	bool thumbRSet;
	
	void mapKeyCodesToEnums();
	void updateKeyboard(std::vector<Input>& commandQueue);
	void updateControllers(std::vector<Input>& commandQueue);
public:
	InputHandler();
	virtual void update(std::vector<Input>& commandQueue);
	virtual void mapCommandToKeyboardKey(KEYBOARD::KEYS enumKey, Key key);
	virtual void mapCommandToControllerKey(CONTROLLER::KEYS enumKey, Key key);
	virtual void mapCommandToLeftThumbStick(Command* command);
	virtual void mapCommandToRightThumbStick(Command* command);
	virtual void remapKeyboardKey(size_t vkc, Key key);
	virtual void remapControllerKey(size_t vkc, Key key);
	virtual void resetKeyBindings();
	virtual void vibrate(int controllerID, int left, int right);
};

#endif
