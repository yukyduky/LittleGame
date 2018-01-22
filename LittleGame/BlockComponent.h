#pragma once
#ifndef BLOCKCOMPONENT_H_
#define BLOCKCOMPONENT_H_

#include "GraphicsComponent.h"
#include <array>


class BlockComponent : GraphicsComponent
{
private:
	int nrOfVertices;
	Vertex* vertices;
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
	ID3D11InputLayout* inputLayout;

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
	};

	Vertex* createBuffers(const float x, const float y, const float z, 
							const float r, const float g, const float b, const float a);
	

public:
	BlockComponent(const float x, const float y, const float z,
						const float r, const float g, const float b, const float a);
	~BlockComponent();
	virtual void recieve(GameObject& obj, Message msg);

	ID3D11Buffer* GETvertexBuffer();
	ID3D11Buffer* GETindexBuffer();
};


#endif