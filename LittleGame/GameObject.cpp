#include "GameObject.h"
#include "Component.h"
#include "Locator.h"
#include "GraphicsComponent.h"


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

void GameObject::nudgePos() 
{
	float nudgeValue = Locator::getRandomGenerator()->GenerateFloat(1.0f, 3.0f);

	this->pos.x += nudgeValue;
	this->pos.y += (nudgeValue * 0.5f);
}

DirectX::XMFLOAT4X4& GameObject::getWorld()
{
	return this->world;
}

void GameObject::SETworldMatrix(XMMATRIX& wMatrix) 
{
	DirectX::XMStoreFloat4x4(&this->world, wMatrix);
}

void GameObject::SETtranslationMatrix(XMMATRIX& translationM) 
{
	DirectX::XMStoreFloat4x4(&this->translationMatrix, translationM);
}

void GameObject::SETscaleMatrix(XMMATRIX& scaleM) 
{
	DirectX::XMStoreFloat4x4(&this->scaleMatrix, scaleM);
}

void GameObject::SETrotationMatrix(XMMATRIX& rotationM) 
{
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

DirectX::XMFLOAT4X4& GameObject::getRotationMatrix()
{
	return this->rotationMatrix;
}