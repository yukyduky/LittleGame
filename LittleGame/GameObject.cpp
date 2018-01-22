#include "GameObject.h"
#include "Component.h"


GameObject::~GameObject()
{
	// Cleanup all the components
	for (auto &c : this->components) {
		delete c;
	}
}

void GameObject::send(Message msg)
{
	// Send the message to all the components that have been added to the object
	for (auto &c : this->components) {
		c->receive(*this, msg);
	}
}

void GameObject::addComponent(Component* component)
{
	this->components.push_back(component);
}
