#pragma once
#ifndef MENUOBJECT_H
#define MENUOBJECT_H

#include <vector>
#include <list>
#include <d3d11.h>
#include <DirectXMath.h>


class Component;

using namespace DirectX;


class MenuObject
{
public:
	MenuObject();
	MenuObject(size_t ID, XMFLOAT3 pos);
	~MenuObject();

	// Needs to be filled
	void cleanUp();
	void addComponent(Component* component);
	const size_t getID() const { return this->ID; }

	XMFLOAT3 GETPosition() { return this->pos; };
	XMMATRIX& GETWorld() { return this->world; };
	//OBJECTSTATE::TYPE GETState() { return OBJECTSTATE::TYPE::ACTIVATED; };
	void SETworldMatrix(XMMATRIX wMatrix) { this->world = wMatrix; }
	void SETtranslationMatrix(XMMATRIX translationM) { this->translationMatrix = translationM; }
	void SETscaleMatrix(XMMATRIX scaleM) { this->scaleMatrix = scaleM; }
	void SETrotationMatrix(XMMATRIX rotationM) { this->rotationMatrix = rotationM; }
	void updateWorldMatrix();

private:
	XMMATRIX world;
	XMMATRIX translationMatrix;
	XMMATRIX scaleMatrix;
	XMMATRIX rotationMatrix;

protected:
	std::list<Component*> components;

	const size_t ID;
	XMFLOAT3 pos;
};



#endif // !MENUOBJECT_H
