#pragma once
#ifndef MOUSECOMMANDS_H
#define MOUSECOMMANDS_H

#include "Command.h"
#include "GamePlayState.h"

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class MouseRotateCommand : public Command
{
public:
	virtual void execute(size_t player) { GamePlayState::getInstance()->commandMouseRotation(); }
};


// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+




#endif
