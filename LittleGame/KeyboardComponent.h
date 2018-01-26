#pragma once
#ifndef KEYBOARDCOMPONENT_H
#define KEYBOARDCOMPONENT_H

#include "InputComponent.h"

class KeyboardComponent : public InputComponent
{
public:
	KeyboardComponent(GameObject& obj);
	virtual void receive(GameObject & obj, Message msg);
	virtual void generateCommands();
	virtual void execute();
};

#endif // !KEYBOARDCOMPONENT_H
