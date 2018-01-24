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
	OBJECTTYPE::TYPE type;
	std::array<DWORD, 36> indices;
	std::array<PrimitiveVertexData, 24> vertexData;
	vColor color;
	void createVertices(const float r, const float g, const float b, const float a);
	
public:
	BlockComponent(size_t ID, const float r, const float g, const float b, const float a);
	~BlockComponent();
	virtual void recieve(GameObject& obj, Message msg);
	virtual void render(RenderInputOrganizer* rio);

	std::array<PrimitiveVertexData, 24>& GETVertexData();
	std::array<DWORD, 36>& GETindices();

	virtual const size_t getID();
	
	vColor& GETcolor();
	OBJECTTYPE::TYPE GETtype();
};


#endif