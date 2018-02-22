#pragma once
#ifndef GUIOBJECT_H
#define GUIOBJECT_H

#include "GraphicsComponent.h"

class GUIObject : public GraphicsComponent
{
private:
	const size_t ID;
	ID3D11Buffer* gVertexBuffer = nullptr;
	ID3D11Buffer* gIndexBuffer = nullptr;
	size_t stride = 0;
	size_t offset = 0;
	size_t numIndices = 0;
	vColor color;
	GameObject* head = nullptr;
	XMFLOAT3 points[4];
	//XMFLOAT3 normals[6];
	double counter = 0;
	double transitionTime = 0;

	void createVertices(XMFLOAT4 color);

public:
	GUIObject();
	~GUIObject();

	virtual const size_t getID() { return this->ID; }
	virtual void receive(GameObject & obj, Message msg);
	virtual void update();
	virtual ID3D11Buffer*& GETvertexBuffer();
	virtual ID3D11Buffer*& GETindexBuffer();
	virtual size_t& GETstride();
	virtual size_t& GEToffset();
	virtual size_t& GETnumIndices();
	virtual XMFLOAT4X4& getWorld();
	virtual OBJECTSTATE::TYPE GETstate();
};

#endif