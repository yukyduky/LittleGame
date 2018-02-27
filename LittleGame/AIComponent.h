#pragma once
#ifndef AICOMPONENT_H
#define AICOMPONENT_H

#include "InputComponent.h"
#include "EnemyState.h"
#include "EnemyMovingState.h"

class EnemyObject;
class Command;
class EnemyMoveState;

namespace AIBEHAVIOR {
	enum KEY {
		STRAIGHTTOWARDS, TEMPLATE0, TEMPLATE1,
		SIZE
	};
}

namespace AICOMMANDS {
	enum KEY {
		MOVE, ATTACK,
		SIZE
	};
}

class ActorObject;

class AIComponent : public InputComponent
{
private:
	size_t ID = -1;
	EnemyObject* pHead = nullptr;
	std::vector<ActorObject*>* players = nullptr;
	AIBEHAVIOR::KEY behavior;
	Command* commands[AICOMMANDS::SIZE];

	// Same vector as the one which relies in pHead
	std::vector<EnemyState*> states;

	XMFLOAT2 simulatedMovement;
	XMFLOAT2 simulatedRotation;

	void bindCommands();


public:
	AIComponent(EnemyObject& obj, AIBEHAVIOR::KEY aiBehavior);
	virtual ~AIComponent() {}

	void pushCommand(AICOMMANDS::KEY command);
	void pushState(EnemyState& state);
	void popState();

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
