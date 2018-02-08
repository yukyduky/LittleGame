#include "AIComponent.h"
#include "Commands.h"
#include "ActorObject.h"

AIComponent::AIComponent(ActorObject& obj, AIBEHAVIOR::KEY aiBehavior, std::vector<ActorObject*> players)
{
	// Set up head
	this->pHead = &obj;
	this->pHead->SETinputComponent(this);
	this->ID = obj.getID();
	this->behavior = aiBehavior;
	this->players = players;

	this->init();
}

void AIComponent::init()
{

}

void AIComponent::receive(GameObject & obj, Message msg)
{

}

void AIComponent::cleanUp()
{
	this->commandQueue.clear();
	this->controllerCommandMap.clear();
	this->keyboardCommandMap.clear();
	this->mouseCommandMap.clear();
	// Might be missing things in accordance with vector!
}

void AIComponent::generateCommands()
{
	XMVECTOR direction;

	if (this->behavior == AIBEHAVIOR::STRAIGHTTOWARDS) {
		XMVECTOR closestPosition = XMLoadFloat3(&players.front()->GETPosition());
		XMVECTOR candidate;

		for (int i = 0; i < players.size(); i++) {
			candidate = XMLoadFloat3(&players[i]->GETPosition());

			// If candidate is closer
			if (XMVector3Greater(closestPosition, candidate)) {
				closestPosition = candidate;
			}
		}

		// Move straight towards 
		XMVECTOR position = XMLoadFloat3(&this->pHead->GETPosition());
		direction = XMVector3Normalize(closestPosition - position);
	}
	
	// Update values
	XMFLOAT3 formattedDirection;
	XMStoreFloat3(&formattedDirection, direction);
	this->simulatedMovement = XMFLOAT2(formattedDirection.x, formattedDirection.z);

	// Push back the command!
	this->commandQueue.push_back(new CommandControllerMove);

	//XMFLOAT3 originalFormat;
	//XMStoreFloat3(&originalFormat, current);
	//this->pHead->setPosition(originalFormat);
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