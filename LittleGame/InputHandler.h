#pragma once
#ifndef INPUTHANDLER_H
#define INPUTHANDLER_H

#include <array>
#include <vector>
#include "Command.h"
#include <Windows.h>

// Possible input types: TAP = 1 click, HOLD = key/button continuously pressed
enum class COMMANDTYPE { TAP, HOLD };

class InputHandler
{
private:
	// Number of virtual keys
	static const int MAX_KEYS = 254;
	// Key states: Released or pressed
	enum COMMANDSTATE { RELEASED, PRESSED };
	// Key action: STOP = don't execute (Anymore), EXECUTE = execute command
	enum COMMANDACTION { STOP, EXECUTE };

	// One Command pointer for every key
	static std::array<Command*, MAX_KEYS> keyCommands;
	// One COMMANDTYPE for every key
	static std::array<COMMANDTYPE, MAX_KEYS> keyTypes;
	// One COMMANDSTATE for every key
	static std::array<COMMANDSTATE, MAX_KEYS> keyStates;
	// One COMMANDACTION for every key
	static std::array<COMMANDACTION, MAX_KEYS> keyActions;

	// Fills the command queue with new commands
	static void fillCommandQueue(std::vector<Command*> &commandQueue);
	// Sets the key/button to the correct state according to the event
	static void eventTranslator(MSG &msg);

	static void keyPress(MSG &msg);
	static void keyRelease(MSG &msg);

	static bool keyIsHeld(size_t key);
	static bool keyWasPressed(size_t key);
public:
	InputHandler();

	// Set all keys and buttons to RELEASED
	static void resetCommands();
	// Map command to key with an input type
	static void mapCommandToInput(Command* command, COMMANDTYPE commandType, size_t key);
	// Generate command if the event corresponds to any mapped command, results stored in the given command queue
	static void generateInputCommands(std::vector<Command*> &commandQueue, MSG msg);
};

#endif
