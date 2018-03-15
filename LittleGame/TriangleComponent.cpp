#include "TriangleComponent.h"
#include "GamePlayState.h"
#include "GameObject.h"
#include "Locator.h"


/*_____________________________
 |         START OF            |
 |     PRIVATE FUNCTIONS       |
 |_____________________________|
 */


void TriangleComponent::createVertices(XMFLOAT4 color)
{
	float r, g, b, a;
	r = color.x;
	g = color.y;
	b = color.z;
	a = color.w;


	/*
[4]	 _____________ [5]
	|\          / | 
[1] \ \        / / [2]
     \ \      /	/	    ^ z
	  \ \    / /	y \ |
	   \ \[3]/ /	   \---> x
		\ \/ /
	     \ |/
		  [0]
	*/
	this->points[0] = XMFLOAT3(0, -1, -1);
	this->points[1] = XMFLOAT3(-1, -1, 1);
	this->points[2] = XMFLOAT3(1, -1, 1);
	this->points[3] = XMFLOAT3(0, 1, -1);
	this->points[4] = XMFLOAT3(-1, 1, 1);
	this->points[5] = XMFLOAT3(1, 1, 1);

	// ------- N O R M A L S ------- 
	XMFLOAT3 edge0;
	XMFLOAT3 edge1;
	XMVECTOR vecEdge0;
	XMVECTOR vecEdge1;
	XMVECTOR vecNormal;

	// Down 
	this->normals[T_NORMALS::DOWN] = XMFLOAT3(0, -1, 0);
	// Up
	this->normals[T_NORMALS::UP] = XMFLOAT3(0, 1, 0);
	// North ([5]-[2]) x ([1]-[2])
	this->normals[T_NORMALS::NORTH] = this->calculateNormal(
		this->points[5],
		this->points[2],
		this->points[1]
	);
	// South-East ([3]-[0]) x ([2]-[0])
	this->normals[T_NORMALS::SOUTH_EAST] = this->calculateNormal(
		this->points[5],
		this->points[2],
		this->points[1]
	);
	// South-West ([4]-[1]) x ([0]-[1])
	this->normals[T_NORMALS::SOUTH_WEST] = this->calculateNormal(
		this->points[4],
		this->points[1],
		this->points[0]
	);

	std::array<PrimitiveVertexData, 18> vertexData;
	// DOWN
	vertexData[0] = this->createPrimitiveVertexData(this->points[0], this->normals[T_NORMALS::DOWN], color);
	vertexData[1] = this->createPrimitiveVertexData(this->points[2], this->normals[T_NORMALS::DOWN], color);
	vertexData[2] = this->createPrimitiveVertexData(this->points[1], this->normals[T_NORMALS::DOWN], color);
	// UP
	vertexData[3] = this->createPrimitiveVertexData(this->points[3], this->normals[T_NORMALS::UP], color);
	vertexData[4] = this->createPrimitiveVertexData(this->points[4], this->normals[T_NORMALS::UP], color);
	vertexData[5] = this->createPrimitiveVertexData(this->points[5], this->normals[T_NORMALS::UP], color);
	// NORTH
	vertexData[6] = this->createPrimitiveVertexData(this->points[5], this->normals[T_NORMALS::NORTH], color);
	vertexData[7] = this->createPrimitiveVertexData(this->points[4], this->normals[T_NORMALS::NORTH], color);
	vertexData[8] = this->createPrimitiveVertexData(this->points[1], this->normals[T_NORMALS::NORTH], color);
	vertexData[9] = this->createPrimitiveVertexData(this->points[2], this->normals[T_NORMALS::NORTH], color);
	// SOUTH_WEST
	vertexData[10] = this->createPrimitiveVertexData(this->points[3], this->normals[T_NORMALS::SOUTH_WEST], color);
	vertexData[11] = this->createPrimitiveVertexData(this->points[0], this->normals[T_NORMALS::SOUTH_WEST], color);
	vertexData[12] = this->createPrimitiveVertexData(this->points[1], this->normals[T_NORMALS::SOUTH_WEST], color);
	vertexData[13] = this->createPrimitiveVertexData(this->points[4], this->normals[T_NORMALS::SOUTH_WEST], color);
	// SOUTH_EAST
	vertexData[14] = this->createPrimitiveVertexData(this->points[5], this->normals[T_NORMALS::SOUTH_EAST], color);
	vertexData[15] = this->createPrimitiveVertexData(this->points[2], this->normals[T_NORMALS::SOUTH_EAST], color);
	vertexData[16] = this->createPrimitiveVertexData(this->points[0], this->normals[T_NORMALS::SOUTH_EAST], color);
	vertexData[17] = this->createPrimitiveVertexData(this->points[3], this->normals[T_NORMALS::SOUTH_EAST], color);

	//Create indices for the box
	DWORD index[] =
	{
		// DOWN
		0, 1, 2,
		// UP
		3, 4, 5,
		// NORTH
		6, 7 ,9,
		9, 7, 8,
		// SOUTH_WEST
		13, 10, 11,
		11, 12, 13,
		// SOUTH_EAST
		17, 14, 15,
		15, 16, 17
	};
	this->numIndices = 24;
	
	this->offset = 0;
	this->stride = sizeof(PrimitiveVertexData);

	Locator::getD3D()->createVertexBuffer(&this->gVertexBuffer, vertexData.data(), this->stride, this->offset, vertexData.size());
	Locator::getD3D()->createIndexBuffer(&this->gIndexBuffer, index, this->numIndices);
}

XMFLOAT3 TriangleComponent::calculateNormal(XMFLOAT3 point0, XMFLOAT3 joinedPoint, XMFLOAT3 point1)
{
	XMFLOAT3 edge0;
	XMFLOAT3 edge1;
	XMFLOAT3 normal;
	XMVECTOR vecEdge0;
	XMVECTOR vecEdge1;
	XMVECTOR vecNormal;

	// Calculate edges
	edge0.x = point0.x - joinedPoint.x;
	edge0.y = point0.y - joinedPoint.y;
	edge0.z = point0.z - joinedPoint.z;
	edge1.x = point1.x - joinedPoint.x;
	edge1.y = point1.y - joinedPoint.y;
	edge1.z = point1.z - joinedPoint.z;
	// Calculate normal
	vecEdge0 = XMLoadFloat3(&edge0);
	vecEdge1 = XMLoadFloat3(&edge1);
	vecNormal = XMVector3Cross(vecEdge0, vecEdge1);
	vecNormal = XMVector3Normalize(vecNormal);
	// Save normal
	XMStoreFloat3(&normal, vecNormal);

	return normal;
}

PrimitiveVertexData TriangleComponent::createPrimitiveVertexData(XMFLOAT3 point, XMFLOAT3 normal, XMFLOAT4 colour)
{
	PrimitiveVertexData data(
		point.x, point.y, point.z,
		normal.x, normal.y, normal.z,
		colour.x, colour.y, colour.z, colour.w
	);
	return data;
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

TriangleComponent::TriangleComponent(
	GamePlayState &pGPS, GameObject& obj, XMFLOAT4 color,
	XMFLOAT3 scale, XMFLOAT3 rotation
) : ID(obj.getID())
{
	// Connections
	this->head = &obj;
	obj.SETgraphicsComponent(this);
	obj.addComponent(this);
	pGPS.addGraphics(this);
	
	this->colorOriginal.r = color.x;
	this->colorOriginal.g = color.y;
	this->colorOriginal.b = color.z;
	this->colorOriginal.a = color.w;

	this->color.r = color.x;
	this->color.g = color.y;
	this->color.b = color.z;
	this->color.a = color.w;
	this->createVertices(color);

	// Create matrixes for world-matrix
	XMVECTOR translation = XMLoadFloat3(&obj.GETPosition());
	XMMATRIX worldMatrix;
	XMMATRIX translationM = XMMatrixTranslationFromVector(translation);

	XMMATRIX rotationX = XMMatrixRotationX(rotation.x);
	XMMATRIX rotationY = XMMatrixRotationY(rotation.y);
	XMMATRIX rotationZ = XMMatrixRotationZ(rotation.z);
	XMMATRIX totalRotation = rotationX * rotationY * rotationZ;

	XMMATRIX scaleM = XMMatrixScaling(scale.x, scale.y, scale.z);
	worldMatrix = scaleM * totalRotation * translationM;

	// Apply matrixes
	obj.SETtranslationMatrix(translationM);
	obj.SETscaleMatrix(scaleM);
	obj.SETrotationMatrix(totalRotation);
	obj.SETworldMatrix(worldMatrix);
	
}

TriangleComponent::~TriangleComponent() 
{
}

void TriangleComponent::receive(GameObject& obj, Message msg)
{
}

void TriangleComponent::update()
{
	this->head->updateWorldMatrix();
}

void TriangleComponent::cleanUp()
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


ID3D11Buffer *& TriangleComponent::GETvertexBuffer()
{
	return this->gVertexBuffer;
}

ID3D11Buffer *& TriangleComponent::GETindexBuffer()
{
	return this->gIndexBuffer;
}

size_t & TriangleComponent::GETstride()
{
	return this->stride;
}

size_t & TriangleComponent::GEToffset()
{
	return this->offset;
}

size_t & TriangleComponent::GETnumIndices()
{
	return this->numIndices;
}

DirectX::XMFLOAT4X4& TriangleComponent::getWorld()
{
	return this->head->getWorld();
}

void TriangleComponent::SETcolor(vColor color)
{
	this->color = color;
}

vColor TriangleComponent::GETcolor() {
	return this->color;
}

vColor TriangleComponent::GETcolorOriginal()
{
	return this->colorOriginal;
}

const size_t TriangleComponent::getID()
{
	return this->ID;
}

OBJECTSTATE::TYPE TriangleComponent::GETstate()
{
	return this->head->getState();
}

void TriangleComponent::updateColor(vColor newColor)
{
	this->color = newColor;
	XMFLOAT4 newColor_(
		newColor.r,
		newColor.g,
		newColor.b,
		newColor.a
	);

	std::array<PrimitiveVertexData, 18> vertexData;
	// DOWN
	vertexData[0] = this->createPrimitiveVertexData(this->points[0], this->normals[T_NORMALS::DOWN], newColor_);
	vertexData[1] = this->createPrimitiveVertexData(this->points[2], this->normals[T_NORMALS::DOWN], newColor_);
	vertexData[2] = this->createPrimitiveVertexData(this->points[1], this->normals[T_NORMALS::DOWN], newColor_);
	// UP
	vertexData[3] = this->createPrimitiveVertexData(this->points[3], this->normals[T_NORMALS::UP], newColor_);
	vertexData[4] = this->createPrimitiveVertexData(this->points[4], this->normals[T_NORMALS::UP], newColor_);
	vertexData[5] = this->createPrimitiveVertexData(this->points[5], this->normals[T_NORMALS::UP], newColor_);
	// NORTH
	vertexData[6] = this->createPrimitiveVertexData(this->points[5], this->normals[T_NORMALS::NORTH], newColor_);
	vertexData[7] = this->createPrimitiveVertexData(this->points[4], this->normals[T_NORMALS::NORTH], newColor_);
	vertexData[8] = this->createPrimitiveVertexData(this->points[1], this->normals[T_NORMALS::NORTH], newColor_);
	vertexData[9] = this->createPrimitiveVertexData(this->points[2], this->normals[T_NORMALS::NORTH], newColor_);
	// SOUTH_WEST
	vertexData[10] = this->createPrimitiveVertexData(this->points[3], this->normals[T_NORMALS::SOUTH_WEST], newColor_);
	vertexData[11] = this->createPrimitiveVertexData(this->points[0], this->normals[T_NORMALS::SOUTH_WEST], newColor_);
	vertexData[12] = this->createPrimitiveVertexData(this->points[1], this->normals[T_NORMALS::SOUTH_WEST], newColor_);
	vertexData[13] = this->createPrimitiveVertexData(this->points[4], this->normals[T_NORMALS::SOUTH_WEST], newColor_);
	// SOUTH_EAST
	vertexData[14] = this->createPrimitiveVertexData(this->points[5], this->normals[T_NORMALS::SOUTH_EAST], newColor_);
	vertexData[15] = this->createPrimitiveVertexData(this->points[2], this->normals[T_NORMALS::SOUTH_EAST], newColor_);
	vertexData[16] = this->createPrimitiveVertexData(this->points[0], this->normals[T_NORMALS::SOUTH_EAST], newColor_);
	vertexData[17] = this->createPrimitiveVertexData(this->points[3], this->normals[T_NORMALS::SOUTH_EAST], newColor_);

	this->gVertexBuffer->Release();

	Locator::getD3D()->createVertexBuffer(&this->gVertexBuffer, vertexData.data(), this->stride, this->offset, vertexData.size());
}
/*_____________________________
|          END OF             |
|      PUBLIC FUNCTIONS       |
|_____________________________|
*/
