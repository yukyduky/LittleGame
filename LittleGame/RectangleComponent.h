#pragma once
#ifndef RECTANGLECOMPONENT_H_
#define RECTANGLECOMPONENT_H_

#include "GraphicsComponent.h"
#include <Windows.h>
#include <array>

class RectangleComponent : public GraphicsComponent
{
private:
	const size_t ID;
	ID3D11Buffer* gVertexBuffer;
	ID3D11Buffer* gIndexBuffer;
	size_t stride;
	size_t offset;
	size_t numIndices;
	vColor color;

	/*--------<INFORMATION>--------
	1. Creates a rectangle with points ranging from -1.0 to 1.0 in x and z dimensions.
	2. All vertices is in modelspace with origin in the center of the rectangle.
	3. Creates normals for the vertices
	4. Creates indices for the indexbuffer.
	*/
	void createVertices();

public:
	/*--------<INFORMATION>--------
	1. Calls the private function createVertices() if it's the first time a RectangleComponent is being created.
	*/
	RectangleComponent(size_t ID, const float r, const float g, const float b, const float a);
	~RectangleComponent();

	/*--------<INFORMATION>--------
	1. Returns the ID of the component.
	*/
	virtual const size_t getID();

	/*--------<INFORMATION>--------
	1. Something.
	*/
	virtual void receive(GameObject& obj, Message msg);

	virtual ID3D11Buffer*& GETvertexBuffer();

	virtual ID3D11Buffer*& GETindexBuffer();

	virtual size_t& GETstride();

	virtual size_t& GEToffset();

	virtual size_t& GETnumIndices();

	/*--------<INFORMATION>--------
	1. Returns the color of the rectangle.
	*/
	vColor& GETcolor();
	
};


#endif