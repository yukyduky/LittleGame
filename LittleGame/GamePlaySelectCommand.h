#pragma once
#ifndef GAMEPLAYSELECTCOMMAND_H
#define GAMEPLAYSELECTCOMMAND_H

#include "Command.h"
#include "GamePlayState.h"

class GamePlaySelectCommand : public Command
{
public:
	virtual void execute(size_t player) { GamePlayState::getInstance()->commandSelect(player); }
};

#endif
