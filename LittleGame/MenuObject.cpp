#include "MenuObject.h"
#include "Component.h"

MenuObject::MenuObject() : ID(0)
{
	this->pos = XMFLOAT3{ 100.0f, 100.0f, 100.0f };
}

MenuObject::MenuObject(size_t ID, XMFLOAT3 pos) : ID(ID)
{
	this->pos = pos;
}


MenuObject::~MenuObject()
{
}

void MenuObject::cleanUp()
{
}

void MenuObject::addComponent(Component * component)
{
	this->components.push_back(component);
}

void MenuObject::updateWorldMatrix()
{
	this->translationMatrix = XMMatrixTranslation(this->pos.x, this->pos.y, this->pos.z);
	this->world = this->scaleMatrix * this->rotationMatrix * this->translationMatrix;
}