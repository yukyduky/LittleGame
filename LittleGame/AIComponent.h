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
	1.  Adds commands to the command queue depending on where the player is and the AIBEHAVIOR
	*/
	void generateCommands();

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Executes all of the queue'd up commands in the commandqueue.
	*/
	void update();
	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Executes all the commands that have been stored in the command queue.
	*/
	void execute();

	void SETnormalizedVectorOfLeftStick(XMFLOAT2 simulatedMovement);

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
