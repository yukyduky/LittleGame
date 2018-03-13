#pragma once
#ifndef GRAPHICSCOMPONENT_H
#define GRAPHICSCOMPONENT_H

#include "Component.h"
#include <d3d11.h>
#include <DirectXMath.h>
#include "GameObject.h"
#include "MenuObject.h"

using namespace DirectX;

struct vColor
{
	float r, g, b, a;

	vColor(float r, float g, float b, float a)
		: r(r), g(g), b(b), a(a){}
	vColor(){}
};

struct PrimitiveVertexData
{
	DirectX::XMFLOAT3 pos;
	DirectX::XMFLOAT3 normal;
	DirectX::XMFLOAT4 color;

	PrimitiveVertexData(float x, float y, float z, float nx, float ny, float nz, float r, float g, float b, float a) :
		pos(x, y, z), normal(nx, ny, nz), color(r, g, b, a) {}
	PrimitiveVertexData(DirectX::XMFLOAT3 pos, DirectX::XMFLOAT3 normal, DirectX::XMFLOAT4 color) :
		pos(pos), normal(normal), color(color) {}
	PrimitiveVertexData() {}
};

//class RenderInputOrganizer;

class GraphicsComponent : public Component
{
public:
	virtual const size_t getID() = 0;
	virtual void receive(GameObject & obj, Message msg) = 0;
	virtual void update() = 0;
	virtual ID3D11Buffer*& GETvertexBuffer() = 0;
	virtual ID3D11Buffer*& GETindexBuffer() = 0;
	virtual size_t& GETstride() = 0;
	virtual size_t& GEToffset() = 0;
	virtual size_t& GETnumIndices() = 0;
	virtual XMFLOAT4X4& getWorld() = 0;
	virtual OBJECTSTATE::TYPE GETstate() = 0;
	virtual vColor GETcolorOriginal() = 0;
	virtual void updateColor(vColor newColor) = 0;
	
};

#endif // !GRAPHICSCOMPONENT_H
