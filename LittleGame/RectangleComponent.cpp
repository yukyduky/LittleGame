#include "RectangleComponent.h"
#include "GameObject.h"
#include "Locator.h"

/*_____________________________
|         START OF            |
|     PRIVATE FUNCTIONS       |
|_____________________________|
*/

void RectangleComponent::createVertices(const float r, const float g, const float b, const float a)
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

	std::array<PrimitiveVertexData, 4> vertexData;

	vertexData[0] = PrimitiveVertexData(-1.0, 0.0, 1.0, 0.0, 1.0, 0.0, r, g, b, a);
	vertexData[1] = PrimitiveVertexData(1.0, 0.0, 1.0, 0.0, 1.0, 0.0, r, g, b, a);
	vertexData[2] = PrimitiveVertexData(-1.0, 0.0, -1.0, 0.0, 1.0, 0.0, r, g, b, a);
	vertexData[3] = PrimitiveVertexData(1.0, 0.0, -1.0, 0.0, 1.0, 0.0, r, g, b, a);

	DWORD index[] = 
	{
		//Top triangle
		0, 1, 2,
		//Bottom triangle
		2, 1, 3
	};
	this->numIndices = 6;

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
	this->createVertices(r, g, b, a);
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

void RectangleComponent::cleanUp()
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
