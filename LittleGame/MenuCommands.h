#pragma once
#ifndef MENUCOMMANDS_H
#define MENUCOMMANDS_H

#include "Command.h"
#include "GamePlayState.h"

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class OpenMenu0Command : public Command
{
public:
	virtual void execute(size_t player) { GamePlayState::getInstance()->commandOpenMenu0(); }
};


// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class OpenMenu1Command : public Command
{
public:
	virtual void execute(size_t player) { GamePlayState::getInstance()->commandOpenMenu1(); }
};




#endif
