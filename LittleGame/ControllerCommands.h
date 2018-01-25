#pragma once
#ifndef CONTROLLERCOMMANDS_H
#define CONTROLLERCOMMANDS_H

#include "Command.h"
#include "GamePlayState.h"

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class ControllerMovementCommand : public Command
{
public:
	virtual void execute(size_t player) { GamePlayState::getInstance()->commandControllerMovement(); }
};


// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class ControllerRotationCommand : public Command
{
public:
	virtual void execute(size_t player) { GamePlayState::getInstance()->commandControllerRotation(); }
};

#endif
