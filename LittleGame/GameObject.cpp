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

DirectX::XMMATRIX& GameObject::getWorld() {
	DirectX::XMMATRIX worldMatrix = DirectX::XMLoadFloat4x4(&this->world);
	
	return worldMatrix;
}

void GameObject::SETworldMatrix(XMMATRIX wMatrix) {
	DirectX::XMStoreFloat4x4(&this->world, wMatrix);
}

void GameObject::SETtranslationMatrix(XMMATRIX translationM) {
	DirectX::XMStoreFloat4x4(&this->translationMatrix, translationM);
}

void GameObject::SETscaleMatrix(XMMATRIX scaleM) {
	DirectX::XMStoreFloat4x4(&this->scaleMatrix, scaleM);
}

void GameObject::SETrotationMatrix(XMMATRIX rotationM) {
	DirectX::XMStoreFloat4x4(&this->rotationMatrix, rotationM);
}

void GameObject::updateWorldMatrix()
{
	DirectX::XMMATRIX scaleMatrix = DirectX::XMLoadFloat4x4(&this->scaleMatrix);
	DirectX::XMMATRIX rotationMatrix = DirectX::XMLoadFloat4x4(&this->rotationMatrix);
	DirectX::XMMATRIX translationMatrix = XMMatrixTranslation(this->pos.x, this->pos.y, this->pos.z);

	DirectX::XMMATRIX worldMatrix = scaleMatrix * rotationMatrix * translationMatrix;

	DirectX::XMStoreFloat4x4(&this->world, worldMatrix);
}

XMMATRIX GameObject::getRotationMatrix() {
	DirectX::XMMATRIX rotationMatrix = DirectX::XMLoadFloat4x4(&this->rotationMatrix);

	return rotationMatrix;
}