#pragma once
#ifndef GAMEPLAYSELECTCOMMAND_H
#define GAMEPLAYSELECTCOMMAND_H

#include "Command.h"
#include "GamePlayState.h"

class GamePlaySelectCommand : public Command
{
private:
	GamePlayState * gamePlayState;
public:
	GamePlaySelectCommand(GamePlayState& gamePlayState) { this->gamePlayState = &gamePlayState; }
	virtual void execute(size_t player) { this->gamePlayState->commandSelect(player); }
};

#endif
