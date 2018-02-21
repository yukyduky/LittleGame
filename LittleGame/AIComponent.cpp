#include "AIComponent.h"
#include "Commands.h"
#include "ActorObject.h"
#include "EnemyObject.h"
#include "EnemyMovingState.h"
#include "EnemyAttackingState.h"

void AIComponent::bindCommands()
{
	this->commands[AICOMMANDS::MOVE] = new CommandControllerMove;
	this->commands[AICOMMANDS::ATTACK] = new CommandEnemyAttack;
}

AIComponent::AIComponent(EnemyObject& obj, AIBEHAVIOR::KEY aiBehavior) : commands()
{
	/// Set up head
	this->pHead = &obj;
	this->pHead->SETinputComponent(this);
	this->ID = obj.getID();

	/// Set internal data
	this->behavior = aiBehavior;
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
	this->states.pop_back();
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