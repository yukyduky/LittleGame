#pragma once
#ifndef LINECOMPONENT_H_
#define LINECOMPONENT_H_

#include "GraphicsComponent.h"
#include <Windows.h>
#include <array>

class LineComponent : public GraphicsComponent
{
private:
	const size_t ID;
	ID3D11Buffer* gVertexBuffer;
	ID3D11Buffer* gIndexBuffer;
	size_t stride;
	size_t offset;
	size_t numIndices;
	GameObject* head;

	/*--------<INFORMATION>--------
	1. Creates a line with points ranging from 0.0 to 1.0 in x-dimension.
	2. All vertices is in modelspace with origin in first vertice of the line.
	3. Creates indices for the indexBuffer.
	*/
	void createVertices(vColor startColor, vColor endColor);
public:
	/*--------<INFORMATION>--------
	1. Calls the private function createVertices() if it's the first time a LineComponent is being created.
	*/
	LineComponent(GameObject& obj, vColor startColor, vColor endColor);
	~LineComponent();
	
	/*--------<INFORMATION>--------
	1. Something
	*/
	virtual void receive(GameObject& obj, Message msg);

	virtual void cleanUp();

	/*--------<INFORMATION>--------
	1. Returns the ID of the component.
	*/
	virtual const size_t getID();

	virtual ID3D11Buffer*& GETvertexBuffer();
	virtual ID3D11Buffer*& GETindexBuffer();
	virtual size_t& GETstride();
	virtual size_t& GEToffset();
	virtual size_t& GETnumIndices();
	virtual XMMATRIX& getWorld();
	
};

#endif