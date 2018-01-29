#pragma once
#ifndef LINECOMPONENT_H_
#define LINECOMPONENT_H_

#include "GraphicsComponent.h"
#include <Windows.h>

class LineComponent : public GraphicsComponent
{
private:
	const size_t ID;
	OBJECTTYPE::TYPE type;
	static std::vector<Vertex> vertices;
	static std::vector<Vertex> normals;
	static std::vector<DWORD> indices;
	std::vector<vColor> colors;

	/*--------<INFORMATION>--------
	1. Creates a line with points ranging from 0.0 to 1.0 in x-dimension.
	2. All vertices is in modelspace with origin in first vertice of the line.
	3. Creates indices for the indexBuffer.
	*/
	void createVertices();
public:
	/*--------<INFORMATION>--------
	1. Calls the private function createVertices() if it's the first time a LineComponent is being created.
	*/
	LineComponent(size_t ID, vColor startColor, vColor endColor);
	~LineComponent();
	
	/*--------<INFORMATION>--------
	1. Something
	*/
	virtual void receive(GameObject& obj, Message msg);

	/*--------<INFORMATION>--------
	1. Returns the ID of the component.
	*/
	virtual const size_t getID();
	
	/*--------<INFORMATION>--------
	1. Returns the vertices of the line.
	*/
	static std::vector<Vertex>& GETvertices();


	/*--------<INFORMATION>--------
	1. Returns the indices of the line.
	*/
	static std::vector<DWORD>& GETindices();

	/*--------<INFORMATION>--------
	1. Returns the colors of the line as std::vector<vColor>&.
	2. First color is the start color, second color is the end color.
	*/
	std::vector<vColor>& GETcolor();

	/*--------<INFORMATION>--------
	1. Returns the type of the component.
	*/
	OBJECTTYPE::TYPE GETtype();
};

#endif