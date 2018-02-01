#pragma once
#ifndef COMMANDS_H
#define COMMANDS_H
#include "ActorObject.h"
//#include "ControllerComponent.h"

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


class CommandMoveUp : public Command
{
public:
	virtual void execute(ActorObject& actor) { actor.moveUp(); }
};
// -+-+-+


class CommandMoveLeft : public Command
{
public:
	virtual void execute(ActorObject& actor) { actor.moveLeft(); }
};
// -+-+-+


class CommandMoveDown : public Command
{
public:
	virtual void execute(ActorObject& actor) { actor.moveDown(); }
};
// -+-+-+


class CommandMoveRight : public Command
{
public:
	virtual void execute(ActorObject& actor) { actor.moveRight(); }
};
// -+-+-+


class CommandControllerMove : public Command
{
public:
	virtual void execute(ActorObject& actor) { actor.move(); }
};
// -+-+-+


class CommandRotate : public Command
{
public:
	virtual void execute(ActorObject& actor) { actor.rotate(); }
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
		actor.fireAbilityX();
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
