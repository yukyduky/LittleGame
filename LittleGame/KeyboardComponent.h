#pragma once
#ifndef KEYBOARDCOMPONENT_H
#define KEYBOARDCOMPONENT_H

#include "InputComponent.h"
#include <DirectXMath.h>

using namespace DirectX;

class KeyboardComponent : public InputComponent
{
private:
	XMFLOAT2 cursorPos;
public:
	KeyboardComponent(GameObject& obj);
	virtual void receive(GameObject & obj, Message msg);
	virtual void generateCommands();
	virtual XMFLOAT2 GETcursorPos();
};

#endif // !KEYBOARDCOMPONENT_H
