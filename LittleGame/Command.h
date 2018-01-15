#pragma once
#ifndef COMMAND_H
#define COMMAND_H

/* Command pattern */

class Command
{
public:
	// Executes the command
	virtual void execute() = 0;
};

#endif
