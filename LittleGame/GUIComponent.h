#pragma once
#ifndef GUICOMPONENT_H
#define GUICOMPONENT_H

#include "GraphicsComponent.h"
#include <vector>
#include <array>
#include <Windows.h>

struct PrimitiveVertexData;
class GamePlayState;

class GUIComponent : public GraphicsComponent
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
	XMFLOAT3 normals[1];
	double counter = 0;
	double transitionTime = 0;

	void createVertices(XMFLOAT4 color);

public:
	GUIComponent(GamePlayState& pGPS, GameObject& obj, XMFLOAT4 color, XMFLOAT3 scale, XMFLOAT3 rotation);
	~GUIComponent();

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

	vColor GETcolor();

	virtual void cleanUp();
	void updateColor(vColor newColor);
};

#endif