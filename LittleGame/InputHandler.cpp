#include "InputHandler.h"

std::array<Command*, InputHandler::InputHandler::MAX_KEYS> InputHandler::keyCommands;
std::array<COMMANDTYPE, InputHandler::MAX_KEYS> InputHandler::keyTypes;
std::array<InputHandler::COMMANDSTATE, InputHandler::MAX_KEYS> InputHandler::keyStates;
std::array<InputHandler::COMMANDACTION, InputHandler::MAX_KEYS> InputHandler::keyActions;

void InputHandler::fillCommandQueue(std::vector<Command*>& commandQueue)
{
	for (int i = 0; i < keyCommands.size(); i++) {
		if (keyCommands[i] != nullptr) {
			if (keyIsHeld(i) && keyTypes[i] == COMMANDTYPE::HOLD) {
				commandQueue.push_back(keyCommands[i]);
			}
			else if (keyWasPressed(i) && keyTypes[i] == COMMANDTYPE::TAP) {
				commandQueue.push_back(keyCommands[i]);
			}
		}
	}
}

void InputHandler::eventTranslator(MSG &msg)
{
	if (msg.message == WM_KEYDOWN) {
		keyPress(msg);
	}
	else if (msg.message == WM_KEYUP) {
		keyRelease(msg);
	}
}

void InputHandler::keyPress(MSG &msg)
{
	if (keyStates[msg.wParam] == RELEASED) {
		keyActions[msg.wParam] = EXECUTE;
		keyStates[msg.wParam] = PRESSED;
	}
}

void InputHandler::keyRelease(MSG &msg)
{
	keyStates[msg.wParam] = RELEASED;
}

bool InputHandler::keyIsHeld(size_t key)
{
	return keyStates[key];
}

bool InputHandler::keyWasPressed(size_t key)
{
	return keyActions[key];
}

InputHandler::InputHandler()
{
	for (int i = 0; i < keyCommands.size(); i++) {
		keyCommands[i] = nullptr;
	}
}

void InputHandler::resetCommands()
{
	for (int i = 0; i < keyCommands.size(); i++) {
		if (keyCommands[i] != nullptr) {
			keyStates[i] = RELEASED;
		}
	}
}

void InputHandler::mapCommandToInput(Command* command, COMMANDTYPE commandType, size_t key)
{
	if (key < MAX_KEYS) {
		keyCommands[key] = command;
		keyTypes[key] = commandType;
	}
}

void InputHandler::generateInputCommands(std::vector<Command*>& commandQueue, MSG msg)
{
	eventTranslator(msg);

	fillCommandQueue(commandQueue);
	
	// Resets the Action keys/buttons
	for (int i = 0; i < keyActions.size(); i++) {
		keyActions[i] = STOP;
	}
}
