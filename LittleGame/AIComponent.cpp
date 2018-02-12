#include "AIComponent.h"
#include "Commands.h"
#include "ActorObject.h"
#include "EnemyObject.h"

void AIComponent::bindCommands()
{
	this->commands[AICOMMANDS::MOVE] = new CommandControllerMove;
}

AIComponent::AIComponent(ActorObject& obj, AIBEHAVIOR::KEY aiBehavior, std::vector<ActorObject*> players)
{
	// Set up head
	this->pHead = &obj;
	this->pHead->SETinputComponent(this);
	this->ID = obj.getID();

	// Set internal data
	this->behavior = aiBehavior;
	this->players = players;

	// Initialize
	this->init();
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
	XMVECTOR direction;


	switch (this->behavior) {
		case AIBEHAVIOR::STRAIGHTTOWARDS: {
			/// Update Movement
			EnemyObject* pHead = dynamic_cast<EnemyObject*>(this->pHead);
			this->simulatedMovement = pHead->getVectorToPlayer();

			/// Update Rotation

			// Push back the command!
			this->commandQueue.push_back(this->commands[AICOMMANDS::MOVE]);
			break;
		}
		case AIBEHAVIOR::TEMPLATE0: {

			break;
		}
		case AIBEHAVIOR::TEMPLATE1: {

			break;
		}
	}



	
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

void AIComponent::SETnormalizedVectorOfLeftStick(XMFLOAT2 simulatedMovement)
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