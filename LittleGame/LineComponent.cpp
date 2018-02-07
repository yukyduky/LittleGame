#include "LineComponent.h"
#include "GameObject.h"
#include "Locator.h"

/*_____________________________
|         START OF            |
|     PRIVATE FUNCTIONS       |
|_____________________________|
*/

void LineComponent::createVertices(vColor startColor, vColor endColor)
{
	/*
	p0_______________________p1
	
	p0 = (0.0f, 0.0f, 0.0f);
	p1 = (1.0f, 0.0f, 0.0f);
	*/
	//Push the vertices of the line (p0, p1).
	std::array<PrimitiveVertexData, 2> vertexData;
	vertexData[0] = PrimitiveVertexData(0.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, startColor.r, startColor.g, startColor.b, startColor.a);
	vertexData[1] = PrimitiveVertexData(1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, endColor.r, endColor.g, endColor.b, endColor.a);

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
	this->createVertices(startColor, endColor);	
	this->head = &obj;
}

LineComponent::~LineComponent()
{
}

void LineComponent::receive(GameObject& obj, Message msg)
{
}

void LineComponent::update()
{

}

void LineComponent::cleanUp()
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

bool LineComponent::checkIfDead()
{
	bool returnValue = false;
	if (this->head->getState() == OBJECTSTATE::TYPE::DEAD)
	{
		returnValue = true;
	}
	return returnValue;
}

/*_____________________________
|          END OF             |
|      PUBLIC FUNCTIONS       |
|_____________________________|
*/
