#include "GameObject.h"
#include "Component.h"


void GameObject::send(Message msg)
{
	// Send the message to all the components that have been added to the object
	for (auto &c : this->components) {
		c->receive(*this, msg);
	}
}

void GameObject::update()
{
	for (auto &i : this->components) {
		i->update();
	}
}

void GameObject::addComponent(Component* component)
{
	this->components.push_back(component);
}

void GameObject::updateWorldMatrix()
{
	this->translationMatrix = XMMatrixTranslation(this->pos.x, this->pos.y, this->pos.z);
	this->world = this->scaleMatrix * this->rotationMatrix * this->translationMatrix;
}