#include "LineComponent.h"
#include "GameObject.h"
#include "Locator.h"

/*
std::vector<Vertex> LineComponent::vertices;
std::vector<Vertex> LineComponent::normals;
std::vector<DWORD> LineComponent::indices;
*/

/*_____________________________
|         START OF            |
|     PRIVATE FUNCTIONS       |
|_____________________________|
*/

void LineComponent::createVertices()
{
	/*
	p0_______________________p1
	
	p0 = (0.0f, 0.0f, 0.0f);
	p1 = (1.0f, 0.0f, 0.0f);
	*/
	//Push the vertices of the line (p0, p1).
	std::array<PrimitiveVertexData, 2> vertexData;
	vertexData[0] = PrimitiveVertexData(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 255.0f, 255.0f);
	vertexData[1] = PrimitiveVertexData(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 255.0f, 255.0f);

	/*
	LineComponent::vertices.push_back(Vertex(0.0f, 0.0f, 0.0f));
	LineComponent::vertices.push_back(Vertex(1.0f, 0.0f, 0.0f));
	*/

	//Create indices for the line.
	DWORD index[] =
	{
		0, 1, 0
	};
	this->numIndices = 3;

	this->offset = 0;
	this->stride = sizeof(PrimitiveVertexData);

	Locator::getD3D()->createVertexBuffer(&this->gVertexBuffer, vertexData.data(), this->stride, this->offset, vertexData.size());
	Locator::getD3D()->createIndexBuffer(&this->gIndexBuffer, index, this->numIndices);
	/*
	//Push indices into the vector.
	for (int i = 0; i < 2; i++) {
		LineComponent::indices.push_back(index[i]);
	}
	*/
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

LineComponent::LineComponent(GameObject& obj, vColor startColor, vColor endColor) : ID(obj.getID())
{
	this->createVertices();	
	this->head = &obj;
}

LineComponent::~LineComponent()
{
}

void LineComponent::receive(GameObject& obj, Message msg)
{
}

const size_t LineComponent::getID()
{
	return this->ID;
}

ID3D11Buffer*& LineComponent::GETvertexBuffer()
{
	return this->gVertexBuffer;
}

ID3D11Buffer*& LineComponent::GETindexBuffer()
{
	return this->gIndexBuffer;
}

size_t& LineComponent::GETstride()
{
	return this->stride;
}

size_t& LineComponent::GEToffset()
{
	return this->offset;
}

size_t& LineComponent::GETnumIndices()
{
	return this->numIndices;
}

XMMATRIX& LineComponent::getWorld()
{
	return this->head->getWorld();
}

/*_____________________________
|          END OF             |
|      PUBLIC FUNCTIONS       |
|_____________________________|
*/
