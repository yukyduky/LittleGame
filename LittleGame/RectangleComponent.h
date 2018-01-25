#pragma once
#ifndef RECTANGLECOMPONENT_H_
#define RECTANGLECOMPONENT_H_

#include "GraphicsComponent.h"
#include <Windows.h>

class RectangleComponent : public GraphicsComponent
{
private:
	const size_t ID;
	OBJECTTYPE::TYPE type;
	static std::vector<Vertex> vertices;
	static std::vector<Vertex> normals;
	static std::vector<DWORD> indices;
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
	1. Something.
	*/
	virtual void receive(GameObject& obj, Message msg);

	/*--------<INFORMATION>--------
	1. Returns the ID of the component.
	*/
	virtual const size_t getID();
	
	/*--------<INFORMATION>--------
	1. Returns the vertices of the rectangle.
	*/
	static std::vector<Vertex>& GETvertices();
	
	/*--------<INFORMATION>--------
	1. Returns the normals of the rectangles.
	*/
	static std::vector<Vertex>& GETnormals();
	
	/*--------<INFORMATION>--------
	1. Returns the indices of the rectangle.
	*/
	static std::vector<DWORD>& GETindices();
	
	/*--------<INFORMATION>--------
	1. Returns the color of the rectangle.
	*/
	vColor& GETcolor();
	
	/*--------<INFORMATION>--------
	1. Returns the type of the component.
	*/
	OBJECTTYPE::TYPE GETtype();

};


#endif
