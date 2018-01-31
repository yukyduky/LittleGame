#pragma once
#ifndef BLOCKCOMPONENT_H_
#define BLOCKCOMPONENT_H_

#include "GraphicsComponent.h"
#include <vector>
#include <array>
#include <Windows.h>

struct PrimitiveVertexData;

class BlockComponent : public GraphicsComponent
{
private:
	const size_t ID;
	ID3D11Buffer* gVertexBuffer;
	ID3D11Buffer* gIndexBuffer;
	vColor color;
	size_t stride;
	size_t offset;
	size_t numIndices;
	void createVertices(float r, float g, float b, float a);
	
public:
	BlockComponent(GameObject& obj, float r, float g, float b, float a);
	~BlockComponent();
	virtual void receive(GameObject& obj, Message msg);

	virtual ID3D11Buffer*& GETvertexBuffer();
	virtual ID3D11Buffer*& GETindexBuffer();
	virtual size_t& GETstride();
	virtual size_t& GEToffset();
	virtual size_t& GETnumIndices();
	virtual XMMATRIX& getWorld();

	virtual const size_t getID();
};


#endif