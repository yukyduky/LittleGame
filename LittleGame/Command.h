#pragma once
#ifndef COMMAND_H
#define COMMAND_H

/* Command pattern */

class ActorObject;

class Command
{
public:
	// Executes the command
	virtual void execute(ActorObject& actor) = 0;
};

#endif
