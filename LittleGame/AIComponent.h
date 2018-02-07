#pragma once
#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include "InputComponent.h"

namespace AIBEHAVIOR {
	enum KEY {
		STRAIGHTTOWARDS,
		SIZE
	};
}

class ActorObject;

class AIComponent : public InputComponent
{
private:
	size_t ID = -1;
	ActorObject* pHead = nullptr;
	std::vector<ActorObject*> players;
	AIBEHAVIOR::KEY behavior;

	XMFLOAT2 simulatedMovement;
	XMFLOAT2 simulatedRotation;

public:
	AIComponent(ActorObject& obj, AIBEHAVIOR::KEY aiBehavior, std::vector<ActorObject*> players);
	
	void init();

	void receive(GameObject & obj, Message msg);

	void cleanUp();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Checks what keys are pressed and if they were just pressed or if they're being held
	2. Adds the command to the command queue if the key has a command mapped to it
	*/
	void generateCommands();
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Executes all the commands that have been stored in the command queue.
	*/
	void execute();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Returns the simulated vector movement.
	*/
	virtual XMFLOAT2 GETnormalizedVectorOfLeftStick();
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Returns the simulated vector rotation.
	*/
	virtual XMFLOAT2 GETnormalizedVectorOfRightStick();

	const size_t getID();
};





#endif
