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

	this->points[0] = XMFLOAT3(-1.0f, 0.0f, 1.0f);
	this->points[1] = XMFLOAT3(1.0f, 0.0f, 1.0f);
	this->points[2] = XMFLOAT3(-1.0f, 0.0f, -1.0f);
	this->points[3] = XMFLOAT3(1.0f, 0.0f, -1.0f);

	this->normal = XMFLOAT3(0.0f, 1.0f, 0.0f);


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
	this->counter = 0.0f;
	this->transitionTime = 5.0f;
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

void RectangleComponent::update()
{
	OBJECTSTATE::TYPE state = this->head->getState();
	float dt = static_cast<float>(Locator::getGameTime()->getDeltaTime());

	switch (state)	
	{
	//This case changes the color of the object from it's start color to red over a set time
	case OBJECTSTATE::TYPE::TFALLING:
		if (dt < 1.0) {
			this->counter += dt;
			if (this->counter < this->transitionTime) {
				vColor finalColor(0.0f, 0.0f, 0.0f, 1.0f);
				vColor aCol = this->color;
				vColor bCol(0.1f, 0.1f, 0.1f, 1.0f);

				aCol.r = aCol.r - (aCol.r / this->transitionTime) * counter;
				aCol.g = aCol.g - (aCol.g / this->transitionTime) * counter;
				aCol.b = aCol.b - (aCol.b / this->transitionTime) * counter;
				bCol.r = (bCol.r / this->transitionTime) * counter;
				finalColor.r = aCol.r + bCol.r;
				finalColor.g = aCol.g + bCol.g;
				finalColor.b = aCol.b + bCol.b;

				this->updateColor(finalColor);
			}
			else {
				this->head->setState(OBJECTSTATE::TYPE::FALLING);
				this->counter = 0.0;
			}
		}
		break;
	//This case sets the objects color to it's original color
	case OBJECTSTATE::TYPE::RESETCOLOR:
		this->updateColor(this->color);
		this->head->setState(OBJECTSTATE::TYPE::ACTIVATED);
		break;
	default:
		break;
	}
}

void RectangleComponent::cleanUp()
{
	this->gVertexBuffer->Release();
	this->gIndexBuffer->Release();
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

DirectX::XMFLOAT4X4& RectangleComponent::getWorld()
{
	return this->head->getWorld();
}

vColor& RectangleComponent::GETcolor()
{
	return this->color;
}

OBJECTSTATE::TYPE RectangleComponent::GETstate()
{
	return this->head->getState();
}

void RectangleComponent::updateColor(vColor newColor)
{
	std::array<PrimitiveVertexData, 4> vertexData;

	vertexData[0] = PrimitiveVertexData(this->points[0].x, this->points[0].y, this->points[0].z, this->normal.x, this->normal.y, this->normal.z, newColor.r, newColor.g, newColor.b, newColor.a);
	vertexData[1] = PrimitiveVertexData(this->points[1].x, this->points[1].y, this->points[1].z, this->normal.x, this->normal.y, this->normal.z, newColor.r, newColor.g, newColor.b, newColor.a);
	vertexData[2] = PrimitiveVertexData(this->points[2].x, this->points[2].y, this->points[2].z, this->normal.x, this->normal.y, this->normal.z, newColor.r, newColor.g, newColor.b, newColor.a);
	vertexData[3] = PrimitiveVertexData(this->points[3].x, this->points[3].y, this->points[3].z, this->normal.x, this->normal.y, this->normal.z, newColor.r, newColor.g, newColor.b, newColor.a);

	this->gVertexBuffer->Release();

	Locator::getD3D()->createVertexBuffer(&this->gVertexBuffer, vertexData.data(), this->stride, this->offset, vertexData.size());
}

/*_____________________________
|          END OF             |
|      PUBLIC FUNCTIONS       |
|_____________________________|
*/
