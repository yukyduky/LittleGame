#include "RectangleComponent.h"
#include "GameObject.h"

std::vector<Vertex> RectangleComponent::vertices;
std::vector<Vertex> RectangleComponent::normals;
std::vector<DWORD> RectangleComponent::indices;

/*_____________________________
|         START OF            |
|     PRIVATE FUNCTIONS       |
|_____________________________|
*/

void RectangleComponent::createVertices()
{
	/*
	p0 __________________ p1
	  |                  |
	  |                  |
	  |                  |
	  |                  |
	  |__________________|
	p2                   p3
	
	p0 = (-1.0, 0.0, 1.0)
	p1 = (1.0, 0.0, 1.0)
	p2 = (-1.0, 0.0, -1.0)
	p3 = (1.0, 0.0, -1.0)
	*/

	//Push the vertices into the vector (p0-p3)
	RectangleComponent::vertices.push_back(Vertex(-1.0, 0.0, 1.0));
	RectangleComponent::vertices.push_back(Vertex(1.0, 0.0, 1.0));
	RectangleComponent::vertices.push_back(Vertex(-1.0, 0.0, -1.0));
	RectangleComponent::vertices.push_back(Vertex(1.0, 0.0, -1.0));

	//Push the normals into the vector
	RectangleComponent::normals.push_back(Vertex(0.0, 1.0, 0.0));
	RectangleComponent::normals.push_back(Vertex(0.0, 1.0, 0.0));
	RectangleComponent::normals.push_back(Vertex(0.0, 1.0, 0.0));
	RectangleComponent::normals.push_back(Vertex(0.0, 1.0, 0.0));

	DWORD index[] = 
	{
		//Top triangle
		0, 1, 2,
		//Bottom triangle
		2, 1, 3
	};
	//Push indices into the vector
	for (int i = 0; i < 6; i++)
	{
		RectangleComponent::indices.push_back(index[i]);
	}
}

/*_____________________________
|          END OF             |
|     PRIVATE FUNCTIONS       |
|_____________________________|
*/

/*_____________________________
|          START OF           |
|      PUBLIC FUNCTIONS       |
|_____________________________|
*/

RectangleComponent::RectangleComponent(size_t ID, const float r, const float g, const float b, const float a) : ID(ID)
{
	if (RectangleComponent::vertices.size() == 0) {
		//Create the vertices, indices and normals for the rectangle
		this->createVertices();
	}
	//Set the color of the box
	this->color.r = r;
	this->color.g = g;
	this->color.b = b;
	this->color.a = a;
	//Set type to RECTANGLE
	this->type = OBJECTTYPE::RECTANGLE;
}

RectangleComponent::~RectangleComponent()
{
}

void RectangleComponent::receive(GameObject& obj, Message msg)
{
}


const size_t RectangleComponent::getID()
{
	return this->ID;
}

std::vector<Vertex>& RectangleComponent::GETvertices()
{
	return RectangleComponent::vertices;
}

std::vector<Vertex>& RectangleComponent::GETnormals()
{
	return RectangleComponent::normals;
}

std::vector<DWORD>& RectangleComponent::GETindices()
{
	return RectangleComponent::indices;
}

vColor& RectangleComponent::GETcolor()
{
	return this->color;
}

OBJECTTYPE::TYPE RectangleComponent::GETtype()
{
	return this->type;
}

/*_____________________________
|          END OF             |
|      PUBLIC FUNCTIONS       |
|_____________________________|
*/
