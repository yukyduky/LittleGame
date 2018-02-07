#include "AIComponent.h"
#include "ActorObject.h"

AIComponent::AIComponent(ActorObject& obj, AIBEHAVIOR::KEY aiBehavior, std::vector<ActorObject*> players)
{
	// Set up head
	this->pHead = &obj;
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
		// Loop starts at 1 because, the first time is always the shortest one that loop, so no comparison needed.
		XMVECTOR closestPosition = XMLoadFloat3(&players.front()->GETPosition());
		XMVECTOR candidate;

		for (int i = 1; i < players.size(), i++;) {
			candidate = XMLoadFloat3(&players[i]->GETPosition());

			// If candidate is closer
			if (XMVector3Greater(closestPosition, candidate)) {
				closestPosition = candidate;
			}
		}

		// Move straight towards 
		XMVECTOR position = XMLoadFloat3(&this->pHead->GETPosition());
		direction = XMVector3Normalize(position - closestPosition);
	}
	
	// Update values
	XMFLOAT3 current = this->pHead->GETPosition();
	current.x +=
	this->pHead->setPosition()
}

void AIComponent::execute()
{

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