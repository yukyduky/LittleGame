#include "GraphicsComponent.h"
#include "GameObject.h"

const size_t GraphicsComponent::getID() {
	return this->ID;
}

void GraphicsComponent::recieve(GameObject& obj, Message msg) {

}