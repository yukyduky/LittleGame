#include "MenuRectComponent.h"
#include "MenuState.h"
#include "MenuObject.h"
#include "Locator.h"


/*_____________________________
|         START OF            |
|     PRIVATE FUNCTIONS       |
|_____________________________|
*/


void MenuRectComponent::createVertices(XMFLOAT4 color)
{/*
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

	float r, g, b, a;
	r = color.x;
	g = color.y;
	b = color.z;
	a = color.w;
	//r = 200;
	//g = 200;
	//b = 200;
	//a = 200;

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

MenuRectComponent::MenuRectComponent(MenuState& pMS, MenuObject& obj, Camera &cam, XMFLOAT4 color, XMFLOAT3 scale)
	: ID(obj.getID())
{
	// Connections
	this->head = &obj;
	obj.addComponent(this);
	pMS.addGraphics(this);

	this->color.r = color.x;
	this->color.g = color.y;
	this->color.b = color.z;
	this->color.a = color.w;
	this->createVertices(color);

	// Create matrixes for world-matrix
	XMVECTOR translation = XMLoadFloat3(&obj.GETPosition());
	XMMATRIX translationM = XMMatrixTranslationFromVector(translation);

	//XMVECTOR nor = XMLoadFloat3(&this->normal);
	//XMVECTOR camDir = cam.GETfacingDir();
	//XMMATRIX rotationX = XMMatrixRotationX((XMVector3AngleBetweenNormals(nor, camDir)));
	XMMATRIX rotationX = XMMatrixRotationX(-.2);
	//XMMATRIX rotationX = XMMatrixIdentity();

	XMMATRIX scaleM = XMMatrixScaling(scale.x, scale.y, scale.z);
	XMMATRIX worldMatrix = scaleM * rotationX * translationM;

	// Apply matrixes
	obj.SETtranslationMatrix(translationM);
	obj.SETscaleMatrix(scaleM);
	obj.SETrotationMatrix(rotationX);
	obj.SETworldMatrix(worldMatrix);

}

MenuRectComponent::~MenuRectComponent()
{
}

void MenuRectComponent::receive(GameObject& obj, Message msg)
{
}

void MenuRectComponent::update()
{
	this->head->updateWorldMatrix();
}

void MenuRectComponent::cleanUp()
{
	this->gVertexBuffer->Release();
	this->gIndexBuffer->Release();
}


ID3D11Buffer *& MenuRectComponent::GETvertexBuffer()
{
	return this->gVertexBuffer;
}

ID3D11Buffer *& MenuRectComponent::GETindexBuffer()
{
	return this->gIndexBuffer;
}

size_t & MenuRectComponent::GETstride()
{
	return this->stride;
}

size_t & MenuRectComponent::GEToffset()
{
	return this->offset;
}

size_t & MenuRectComponent::GETnumIndices()
{
	return this->numIndices;
}

XMMATRIX& MenuRectComponent::getWorld()
{
	return this->head->GETWorld();
}

const size_t MenuRectComponent::getID()
{
	return this->ID;
}

OBJECTSTATE::TYPE MenuRectComponent::GETstate()
{
	return OBJECTSTATE::TYPE::ACTIVATED;
}