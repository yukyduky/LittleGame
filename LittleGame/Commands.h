#pragma once
#ifndef COMMANDS_H
#define COMMANDS_H
#include "ActorObject.h"

/* Command pattern */
class ActorObject;

class Command
{
public:
	// Executes the command
	virtual void execute(ActorObject& actor) = 0;
};

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
class CommandSelect : public Command
{
public:
	virtual void execute(ActorObject& actor) {

	}
};
// -+-+-+
class CommandMove : public Command
{
public:
	virtual void execute(ActorObject& actor) {

	}
};
// -+-+-+
class CommandRotate : public Command
{
public:
	virtual void execute(ActorObject& actor) {

	}
};
// -+-+-+
class CommandFireAbility0 : public Command
{
public:
	virtual void execute(ActorObject& actor) {
		actor.fireAbility0();
	}
};
// -+-+-+
class CommandFireAbilityX : public Command
{
public:
	virtual void execute(ActorObject& actor) {

	}
};
// -+-+-+
class CommandSelectAbility1 : public Command
{
public:
	virtual void execute(ActorObject& actor) {

	}
};
// -+-+-+
class CommandSelectAbility2 : public Command
{
public:
	virtual void execute(ActorObject& actor) {

	}
};
// -+-+-+
class CommandSelectAbility3 : public Command
{
public:
	virtual void execute(ActorObject& actor) {

	}
};
// -+-+-+
class CommandSelectAbility4 : public Command
{
public:
	virtual void execute(ActorObject& actor) {

	}
};
// -+-+-+
class CommandOpenMenu0 : public Command
{
public:
	virtual void execute(ActorObject& actor) {

	}
};
// -+-+-+
class CommandOpenMenu1 : public Command
{
public:
	virtual void execute(ActorObject& actor) {

	}
};
#endif
