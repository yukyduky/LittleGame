#include "GUIComponent.h"
#include "GamePlayState.h"
#include "GameObject.h"
#include "Locator.h"

//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//                                    GUI OBJECT           /
///////////////////////////////////////////////////////////
//////////////////////////////
///////////////
///////
//

/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                             |
  |           PRIVATE           |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-*/

void GUIComponent::createVertices(XMFLOAT4 color) {
	float r, g, b, a;

	r = color.x;
	g = color.y;
	b = color.z;
	a = color.w;

/*
	p0 _________p1
	  |         |
	  |         |
	  |         |
	  |_________|
	p2          p3
*/
	
	// Points
	this->points[0] = XMFLOAT3(-1.0f, 1.0f, -1.0f);
	this->points[1] = XMFLOAT3(0.5f, 1.0f, -1.0f);
	this->points[2] = XMFLOAT3(-1.0f, -1.0f, -1.0f);
	this->points[3] = XMFLOAT3(0.5f, -1.0f, -1.0f);

	// Normal(s)
	this->normals[0] = XMFLOAT3(0.0f, 0.0f, -1.0f);

	std::array<PrimitiveVertexData, 4> vertexData;

	//Front p0, p1, p2, p3
	vertexData[0] = PrimitiveVertexData(this->points[0].x, this->points[0].y, this->points[0].z, this->normals[0].x, this->normals[0].y, this->normals[0].z, r, g, b, a);
	vertexData[1] = PrimitiveVertexData(this->points[1].x, this->points[1].y, this->points[1].z, this->normals[0].x, this->normals[0].y, this->normals[0].z, r, g, b, a);
	vertexData[2] = PrimitiveVertexData(this->points[2].x, this->points[2].y, this->points[2].z, this->normals[0].x, this->normals[0].y, this->normals[0].z, r, g, b, a);
	vertexData[3] = PrimitiveVertexData(this->points[3].x, this->points[3].y, this->points[3].z, this->normals[0].x, this->normals[0].y, this->normals[0].z, r, g, b, a);

	// Indices
	DWORD index[] =
	{
		0, 1, 2,
		2, 1, 3
	};
	this->numIndices = 6;

	this->offset = 0;
	this->stride = sizeof(PrimitiveVertexData);

	Locator::getD3D()->createVertexBuffer(&this->gVertexBuffer, vertexData.data(), this->stride, this->offset, vertexData.size());
	Locator::getD3D()->createIndexBuffer(&this->gIndexBuffer, index, this->numIndices);
}

//_________________________________________//
//                                         //
//             END OF PRIVATE              //
//_________________________________________//
/////////////////////////////////////////////





/* _+_+_+_+_+_+_+_+_+_+_+_+_+_+_
  |                             |
  |           PUBLIC            |
   -_-_-_-_-_-_-_-_-_-_-_-_-_-*/

GUIComponent::GUIComponent(
	GamePlayState& pGPS,
	GameObject& obj,
	XMFLOAT4 color,
	XMFLOAT3 scale,
	XMFLOAT3 rotation) : ID(obj.getID())
{
	this->head = &obj;
	obj.SETgraphicsComponent(this);
	obj.addComponent(this);
	pGPS.addGraphics(this);

	this->color.r = color.x;
	this->color.g = color.y;
	this->color.b = color.z;
	this->color.a = color.w;
	this->createVertices(color);

	// Create Matrices for world-matrix

	// Apply matrices
}

GUIComponent::~GUIComponent()
{

}

void GUIComponent::receive(GameObject& obj, Message msg)
{

}

void GUIComponent::update()
{
	this->head->updateWorldMatrix();
}

void GUIComponent::cleanUp()
{
	if (this->gVertexBuffer != nullptr) {
		this->gVertexBuffer->Release();
		this->gVertexBuffer = nullptr;
	}
	if (this->gIndexBuffer != nullptr) {
		this->gIndexBuffer->Release();
		this->gIndexBuffer = nullptr;
	}
}

ID3D11Buffer *& GUIComponent::GETvertexBuffer()
{
	return this->gVertexBuffer;
}

ID3D11Buffer *& GUIComponent::GETindexBuffer()
{
	return this->gIndexBuffer;
}

size_t & GUIComponent::GETstride()
{
	return this->stride;
}

size_t & GUIComponent::GEToffset()
{
	return this->offset;
}

size_t & GUIComponent::GETnumIndices()
{
	return this->numIndices;
}

DirectX::XMFLOAT4X4& GUIComponent::getWorld()
{
	return this->head->getWorld();
}

vColor GUIComponent::GETcolor() {
	return this->color;
}

OBJECTSTATE::TYPE GUIComponent::GETstate()
{
	return this->head->getState();
}

void GUIComponent::updateColor(vColor newColor)
{
	std::array<PrimitiveVertexData, 4> vertexData;
	//Front p0, p1, p2, p3
	vertexData[0] = PrimitiveVertexData(this->points[0].x, this->points[0].y, this->points[0].z, this->normals[0].x, this->normals[0].y, this->normals[0].z, newColor.r, newColor.g, newColor.b, newColor.a);
	vertexData[1] = PrimitiveVertexData(this->points[1].x, this->points[1].y, this->points[1].z, this->normals[0].x, this->normals[0].y, this->normals[0].z, newColor.r, newColor.g, newColor.b, newColor.a);
	vertexData[2] = PrimitiveVertexData(this->points[2].x, this->points[2].y, this->points[2].z, this->normals[0].x, this->normals[0].y, this->normals[0].z, newColor.r, newColor.g, newColor.b, newColor.a);
	vertexData[3] = PrimitiveVertexData(this->points[3].x, this->points[3].y, this->points[3].z, this->normals[0].x, this->normals[0].y, this->normals[0].z, newColor.r, newColor.g, newColor.b, newColor.a);

	this->gVertexBuffer->Release();

	Locator::getD3D()->createVertexBuffer(&this->gVertexBuffer, vertexData.data(), this->stride, this->offset, vertexData.size());
}

//_________________________________________//
//                                         //
//              END OF PUBLIC              //
//_________________________________________//
/////////////////////////////////////////////

//
//\\\\\
//\\\\\\\\\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
//                                 GAMEPLAY STATE          \
////////////////////////////////////////////////////////////