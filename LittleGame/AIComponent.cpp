#include "AIComponent.h"
#include "Commands.h"
#include "ActorObject.h"
#include "EnemyObject.h"
#include "EnemyMovingState.h"
#include "EnemyAttackingState.h"
#include "EnemyState.h"

void AIComponent::bindCommands()
{
	this->commands[AICOMMANDS::MOVE] = new CommandControllerMove;
	this->commands[AICOMMANDS::ATTACK] = new CommandEnemyAttack;
	this->commands[AICOMMANDS::BOSSATTACK01] = new CommandBossAttack01;
	this->commands[AICOMMANDS::BOSSATTACK02] = new CommandBossAttack02;
	this->commands[AICOMMANDS::BOSSATTACK03] = new CommandBossAttack03;
}

AIComponent::AIComponent(EnemyObject& obj) : commands()
{
	/// Set up head
	this->pHead = &obj;
	this->pHead->SETinputComponent(this);
	this->ID = obj.getID();
	

	/// Set internal data
	this->players = obj.getPlayers();

	/// Initialize
	this->init();
}

void AIComponent::pushCommand(AICOMMANDS::KEY command)
{
	this->commandQueue.push_back(this->commands[command]);
}

void AIComponent::pushState(EnemyState& state)
{
	this->states.push_back(&state);
}

void AIComponent::popState()
{
	EnemyState* stateToBeRemoved = this->states.back();
	this->states.pop_back();
	stateToBeRemoved->cleanUp();
	delete stateToBeRemoved;
}

void AIComponent::init()
{
	this->bindCommands();
}

void AIComponent::receive(GameObject & obj, Message msg)
{

}

void AIComponent::cleanUp()
{
	this->commandQueue.clear();
	/// The 3 functions below cause the infamous 'NO-INPUT BUG'
//	this->controllerCommandMap.clear();
//	this->keyboardCommandMap.clear();
//	this->mouseCommandMap.clear();
	// Might be missing things in accordance with vector!

	EnemyState* stateToBeRemoved = nullptr;
	for (auto &currentState : this->states) {
		// Fetch state
		stateToBeRemoved = currentState;
		// Delete it
		delete stateToBeRemoved;
		// Set pointers to nullptr
		currentState = nullptr;
		stateToBeRemoved = nullptr;
	}
	this->states.clear();
}

EnemyState * AIComponent::getCurrentState()
{
	return this->states.back();
}

void AIComponent::generateCommands()
{
	/// Execute behavior according to current state
	this->states.back()->executeBehavior();
}

void AIComponent::update()
{
	this->generateCommands();
	this->execute();
}

void AIComponent::execute()
{
	for (auto &command : this->commandQueue) {
		command->execute(*this->pHead);
	}
	this->commandQueue.clear();
}

void AIComponent::SETsimulatedMovement(XMFLOAT2 simulatedMovement)
{
	this->simulatedMovement = simulatedMovement;
}

const size_t AIComponent::getID()
{
	return this->ID;
}

XMFLOAT2 AIComponent::GETnormalizedVectorOfLeftStick()
{
	return this->simulatedMovement;
}

XMFLOAT2 AIComponent::GETnormalizedVectorOfRightStick()
{
	return this->simulatedRotation;
}