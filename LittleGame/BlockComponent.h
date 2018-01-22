#pragma once
#ifndef BLOCKCOMPONENT_H_
#define BLOCKCOMPONENT_H_

#include "GraphicsComponent.h"
#include <vector>
#include <Windows.h>

class BlockComponent : GraphicsComponent
{
private:
	const size_t ID;
	OBJECTTYPE::TYPE type;
	static std::vector<PrimitiveVertex> vertices;
	static std::vector<DWORD> indices;
	PrimitiveColor color;
	void createVertices(const float r, const float g, const float b, const float a);
	
public:
	BlockComponent(size_t ID, const float r, const float g, const float b, const float a);
	~BlockComponent();
	virtual void recieve(GameObject& obj, Message msg);
	
	virtual const size_t getID();
	static std::vector<PrimitiveVertex>& GETvertices();
	static std::vector<DWORD>& GETindices();
	PrimitiveColor& GETcolor();
	OBJECTTYPE::TYPE GETtype();
};


#endif