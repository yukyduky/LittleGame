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
	static std::vector<Vertex> vertices;
	static std::vector<Vertex> normals;
	static std::vector<DWORD> indices;
	vColor color;
	void createVertices(const float r, const float g, const float b, const float a);
	
public:
	BlockComponent(size_t ID, const float r, const float g, const float b, const float a);
	~BlockComponent();
	virtual void receive(GameObject& obj, Message msg);
	
	virtual const size_t getID();
	static std::vector<Vertex>& GETvertices();
	static std::vector<Vertex>& GETnormals();
	static std::vector<DWORD>& GETindices();
	vColor& GETcolor();
	OBJECTTYPE::TYPE GETtype();
};


#endif