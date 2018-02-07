#include "AIComponent.h"
#include "ActorObject.h"

AIComponent::AIComponent(ActorObject& obj, AIBEHAVIOR::KEY aiBehavior)
{
	// Set up head
	this->pHead = &obj;
	this->ID = obj.getID();
	this->behavior = aiBehavior;

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

}

void AIComponent::generateCommands()
{
	// MAIN AI HERE!

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