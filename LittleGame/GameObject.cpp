#include "GameObject.h"
#include "Component.h"
#include "Locator.h"


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

void GameObject::nudgePos() {
	int nudgeValue = Locator::getRandomGenerator()->GenerateFloat(1, 3);

	this->pos.x += nudgeValue;
	this->pos.y += (nudgeValue * 0.5);
}

void GameObject::updateWorldMatrix()
{
	this->translationMatrix = XMMatrixTranslation(this->pos.x, this->pos.y, this->pos.z);
	this->world = this->scaleMatrix * this->rotationMatrix * this->translationMatrix;
}