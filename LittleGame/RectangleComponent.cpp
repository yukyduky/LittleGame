#include "RectangleComponent.h"
#include "GameObject.h"
#include "Locator.h"

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
	/*
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
	*/

	std::array<PrimitiveVertexData, 4> vertexData;

	vertexData[0] = PrimitiveVertexData(-1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0f, 255.0f, 0.0f, 255.0f);
	vertexData[0] = PrimitiveVertexData(1.0, 0.0, 1.0, 0.0, 1.0, 0.0, 0.0f, 255.0f, 0.0f, 255.0f);
	vertexData[0] = PrimitiveVertexData(-1.0, 0.0, -1.0, 0.0, 1.0, 0.0, 0.0f, 255.0f, 0.0f, 255.0f);
	vertexData[0] = PrimitiveVertexData(1.0, 0.0, -1.0, 0.0, 1.0, 0.0, 0.0f, 255.0f, 0.0f, 255.0f);

	DWORD index[] = 
	{
		//Top triangle
		0, 1, 2,
		//Bottom triangle
		2, 1, 3
	};
	this->numIndices = 6;
	/*
	//Push indices into the vector
	for (int i = 0; i < 6; i++)
	{
		RectangleComponent::indices.push_back(index[i]);
	}
	*/

	this->offset = 0;
	this->stride = sizeof(PrimitiveVertexData);

	Locator::getD3D()->createVertexBuffer(&this->gVertexBuffer, vertexData.data(), this->stride, this->offset, vertexData.size());
	Locator::getD3D()->createIndexBuffer(&this->gIndexBuffer, index, this->numIndices);
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

RectangleComponent::RectangleComponent(GameObject& obj, const float r, const float g, const float b, const float a) : ID(obj.getID())
{
	this->createVertices();
	this->head = &obj;
	//Set the color of the box
	this->color.r = r;
	this->color.g = g;
	this->color.b = b;
	this->color.a = a;
}

RectangleComponent::~RectangleComponent()
{
}

const size_t RectangleComponent::getID()
{
	return this->ID;
}

void RectangleComponent::receive(GameObject& obj, Message msg)
{
}

ID3D11Buffer*& RectangleComponent::GETvertexBuffer()
{
	return this->gVertexBuffer;
}

ID3D11Buffer*& RectangleComponent::GETindexBuffer()
{
	return this->gIndexBuffer;
}

size_t& RectangleComponent::GETstride()
{
	return this->stride;
}

size_t& RectangleComponent::GEToffset()
{
	return this->offset;
}

size_t& RectangleComponent::GETnumIndices()
{
	return this->numIndices;
}

XMMATRIX& RectangleComponent::getWorld()
{
	return this->head->getWorld();
}

vColor& RectangleComponent::GETcolor()
{
	return this->color;
}


/*_____________________________
|          END OF             |
|      PUBLIC FUNCTIONS       |
|_____________________________|
*/
