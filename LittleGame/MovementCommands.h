#pragma once
#ifndef MOVEMENTCOMMANDS_H
#define MOVEMENTCOMMANDS_H

#include "Command.h"
#include "GamePlayState.h"

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class MoveLeftCommand : public Command
{
public:
	virtual void execute(size_t player) { GamePlayState::getInstance()->commandMoveLeft(); }
};





// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class MoveRightCommand : public Command
{
public:
	virtual void execute(size_t player) { GamePlayState::getInstance()->commandMoveRight(); }
};





// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class MoveUpCommand : public Command
{
public:
	virtual void execute(size_t player) { GamePlayState::getInstance()->commandMoveUp(); }
};




// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class MoveDownCommand : public Command
{
public:
	virtual void execute(size_t player) { GamePlayState::getInstance()->commandMoveDown(); }
};




#endif
