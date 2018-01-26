#pragma once
#ifndef CONTROLLERCOMPONENT_H
#define CONTROLLERCOMPONENT_H

#include "InputComponent.h"
#include <Windows.h>
#include <Xinput.h>
#include <DirectXMath.h>

class ControllerComponent : public InputComponent
{
private:
	enum class THUMB { LTHUMB, RTHUMB };

	size_t controllerID;
	XINPUT_STATE currentState;
	bool thumbLSet;
	bool thumbRSet;
	XMFLOAT2 thumbLDir;
	XMFLOAT2 thumbRDir;
	float trigLValue;
	float trigRValue;

	float checkThumb(THUMB thumb, size_t deadzone, XINPUT_STATE state);
public:
	ControllerComponent(GameObject& obj, size_t controllerID);
	virtual void receive(GameObject & obj, Message msg);
	virtual void generateCommands();
	virtual void execute();
	virtual void vibrate(size_t left, size_t right);
};

#endif // !CONTROLLERCOMPONENT_H
