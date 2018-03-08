#pragma once
#ifndef COMMANDS_H
#define COMMANDS_H
#include "ActorObject.h"
#include "EnemyObject.h"

/* Command pattern */
class ActorObject;

/*
mapKeyCodesToEnums();
mapCommands();
mapKeys();
command



*/

class Command
{
public:
	// Executes the command
	virtual void execute(ActorObject& actor) = 0;
};
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
class CommandBossAttack01 : public Command
{
public:
	virtual void execute(ActorObject& actor) {
		EnemyObject* trueObject = static_cast<EnemyObject*>(&actor);
		trueObject->bossAttack01();
	}
};

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
class CommandBossAttack02 : public Command
{
public:
	virtual void execute(ActorObject& actor) {
		EnemyObject* trueObject = static_cast<EnemyObject*>(&actor);
		trueObject->bossAttack02();
	}
};

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
class CommandBossAttack03 : public Command
{
public:
	virtual void execute(ActorObject& actor) {
		EnemyObject* trueObject = static_cast<EnemyObject*>(&actor);
		trueObject->bossAttack03();
	}
};

// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
// +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-
class CommandEnemyAttack : public Command
{
public:
	virtual void execute(ActorObject& actor) {
		EnemyObject* trueObject = static_cast<EnemyObject*>(&actor);
		trueObject->attack();
	}
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
		actor.selectAbility1();
	}
};
// -+-+-+


class CommandSelectAbility2 : public Command
{
public:
	virtual void execute(ActorObject& actor) {
		actor.selectAbility2();
	}
};
// -+-+-+


class CommandSelectAbility3 : public Command
{
public:
	virtual void execute(ActorObject& actor) {
		actor.selectAbility3();
	}
};
// -+-+-+


class CommandSelectAbility4 : public Command
{
public:
	virtual void execute(ActorObject& actor) {
		actor.selectAbility4();
	}
};
// -+-+-+


class CommandOpenMenu0 : public Command
{
public:
	virtual void execute(ActorObject& actor) {
		actor.pauseMenu();
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
