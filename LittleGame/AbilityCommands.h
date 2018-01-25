#pragma once
#ifndef SELECTSPELLCOMMANDS_H
#define SELECTSPELLCOMMANDS_H

#include "Command.h"
#include "GamePlayState.h"

// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class SelectAbility1Command : public Command
{
public:
	virtual void execute(size_t player) { GamePlayState::getInstance()->commandSelectAbility1(); }
};





// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class SelectAbility2Command : public Command
{
public:
	virtual void execute(size_t player) { GamePlayState::getInstance()->commandSelectAbility2(); }
};




// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class SelectAbility3Command : public Command
{
public:
	virtual void execute(size_t player) { GamePlayState::getInstance()->commandSelectAbility3(); }
};




// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class SelectAbility4Command : public Command
{
public:
	virtual void execute(size_t player) { GamePlayState::getInstance()->commandSelectAbility4(); }
};





// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class FireAbility0Command : public Command
{
public:
	virtual void execute(size_t player) { GamePlayState::getInstance()->commandFireAbility0(); }
};





// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
// -+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
class FireAbilityXCommand : public Command
{
public:
	virtual void execute(size_t player) { GamePlayState::getInstance()->commandFireAbilityX(); }
};

#endif
