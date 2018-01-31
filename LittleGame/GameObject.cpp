#include "GameObject.h"
#include "Component.h"


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
