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

	/*--------<INFORMATION>--------
	1. Creates a triangle with points ranging from -1.0 to 1.0 in x,y,z dimensions.
	2. Sets the color of every vertex to the r,g,b in the paramaters.
	3. All vertices is in modelspace with origin in the center of the box.
	4. Creates indices for the indexbuffer.
	*/

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
	this->points[1] = XMFLOAT3(-1, -1, -1);
	this->points[2] = XMFLOAT3(1, -1, 1);
	this->points[3] = XMFLOAT3(0, 1, -1);
	this->points[4] = XMFLOAT3(-1, 1, 1);
	this->points[5] = XMFLOAT3(1, 1, 1);

	// North
	this->normals[0] = 

	// Top

	// Bot 

	// West-ish

	// East-ish
	
	//Front
	this->normals[0] = XMFLOAT3(0.0f, 0.0f, -1.0f);
	//Left
	this->normals[1] = XMFLOAT3(-1.0f, 0.0f, 0.0f);
	//Right
	this->normals[2] = XMFLOAT3(1.0f, 0.0f, 0.0f);
	//Back
	this->normals[3] = XMFLOAT3(0.0f, 0.0f, 1.0f);
	//Top
	this->normals[4] = XMFLOAT3(0.0f, 1.0f, 0.0f);
	//Bottom
	this->normals[5] = XMFLOAT3(0.0f, -1.0f, 0.0f);
	
	std::array<PrimitiveVertexData, 24> vertexData;
	//Front p0, p1, p2, p3
	vertexData[0] = PrimitiveVertexData(this->points[0].x, this->points[0].y, this->points[0].z, this->normals[0].x, this->normals[0].y, this->normals[0].z, r, g, b, a);
	vertexData[1] = PrimitiveVertexData(this->points[1].x, this->points[1].y, this->points[1].z, this->normals[0].x, this->normals[0].y, this->normals[0].z, r, g, b, a);
	vertexData[2] = PrimitiveVertexData(this->points[2].x, this->points[2].y, this->points[2].z, this->normals[0].x, this->normals[0].y, this->normals[0].z, r, g, b, a);
	vertexData[3] = PrimitiveVertexData(this->points[3].x, this->points[3].y, this->points[3].z, this->normals[0].x, this->normals[0].y, this->normals[0].z, r, g, b, a);
	//Left p4, p0, p5, p2
	vertexData[4] = PrimitiveVertexData(this->points[4].x, this->points[4].y, this->points[4].z, this->normals[1].x, this->normals[1].y, this->normals[1].z, r, g, b, a);
	vertexData[5] = PrimitiveVertexData(this->points[0].x, this->points[0].y, this->points[0].z, this->normals[1].x, this->normals[1].y, this->normals[1].z, r, g, b, a);
	vertexData[6] = PrimitiveVertexData(this->points[5].x, this->points[5].y, this->points[5].z, this->normals[1].x, this->normals[1].y, this->normals[1].z, r, g, b, a);
	vertexData[7] = PrimitiveVertexData(this->points[2].x, this->points[2].y, this->points[2].z, this->normals[1].x, this->normals[1].y, this->normals[1].z, r, g, b, a);
	//Right p1, p6, p3, p7
	vertexData[8] = PrimitiveVertexData(this->points[1].x, this->points[1].y, this->points[1].z, this->normals[2].x, this->normals[2].y, this->normals[2].z, r, g, b, a);
	vertexData[9] = PrimitiveVertexData(this->points[6].x, this->points[6].y, this->points[6].z, this->normals[2].x, this->normals[2].y, this->normals[2].z, r, g, b, a);
	vertexData[10] = PrimitiveVertexData(this->points[3].x, this->points[3].y, this->points[3].z, this->normals[2].x, this->normals[2].y, this->normals[2].z, r, g, b, a);
	vertexData[11] = PrimitiveVertexData(this->points[7].x, this->points[7].y, this->points[7].z, this->normals[2].x, this->normals[2].y, this->normals[2].z, r, g, b, a);
	//Back p6, p4, p7, p5
	vertexData[12] = PrimitiveVertexData(this->points[6].x, this->points[6].y, this->points[6].z, this->normals[3].x, this->normals[3].y, this->normals[3].z, r, g, b, a);
	vertexData[13] = PrimitiveVertexData(this->points[4].x, this->points[4].y, this->points[4].z, this->normals[3].x, this->normals[3].y, this->normals[3].z, r, g, b, a);
	vertexData[14] = PrimitiveVertexData(this->points[7].x, this->points[7].y, this->points[7].z, this->normals[3].x, this->normals[3].y, this->normals[3].z, r, g, b, a);
	vertexData[15] = PrimitiveVertexData(this->points[5].x, this->points[5].y, this->points[5].z, this->normals[3].x, this->normals[3].y, this->normals[3].z, r, g, b, a);
	//Top p4, p6, p0, p1
	vertexData[16] = PrimitiveVertexData(this->points[4].x, this->points[4].y, this->points[4].z, this->normals[4].x, this->normals[4].y, this->normals[4].z, r, g, b, a);
	vertexData[17] = PrimitiveVertexData(this->points[6].x, this->points[6].y, this->points[6].z, this->normals[4].x, this->normals[4].y, this->normals[4].z, r, g, b, a);
	vertexData[18] = PrimitiveVertexData(this->points[0].x, this->points[0].y, this->points[0].z, this->normals[4].x, this->normals[4].y, this->normals[4].z, r, g, b, a);
	vertexData[19] = PrimitiveVertexData(this->points[1].x, this->points[1].y, this->points[1].z, this->normals[4].x, this->normals[4].y, this->normals[4].z, r, g, b, a);
	//Bottom p2, p3, p5, p7
	vertexData[20] = PrimitiveVertexData(this->points[2].x, this->points[2].y, this->points[2].z, this->normals[5].x, this->normals[5].y, this->normals[5].z, r, g, b, a);
	vertexData[21] = PrimitiveVertexData(this->points[3].x, this->points[3].y, this->points[3].z, this->normals[5].x, this->normals[5].y, this->normals[5].z, r, g, b, a);
	vertexData[22] = PrimitiveVertexData(this->points[5].x, this->points[5].y, this->points[5].z, this->normals[5].x, this->normals[5].y, this->normals[5].z, r, g, b, a);
	vertexData[23] = PrimitiveVertexData(this->points[7].x, this->points[7].y, this->points[7].z, this->normals[5].x, this->normals[5].y, this->normals[5].z, r, g, b, a);
	
	//Create indices for the box
	DWORD index[] =
	{
		//Front p0, p1, p2, p3
		0, 1, 2,
		2, 1, 3,
		//Left p4, p0, p5, p2
		4, 5, 6,
		6, 5, 7,
		//Right p1, p6, p3, p7
		8, 9, 10,
		10, 9, 11,
		//Back p6, p4, p7, p5
		12, 13, 14,
		14, 13, 15,
		//Top p4, p6, p0, p1
		16, 17, 18,
		18, 17, 19,
		//Bottom p2, p3, p5, p7
		20, 21, 22,
		22, 21, 23
	};
	this->numIndices = 36;
	
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

TriangleComponent::TriangleComponent(
	GamePlayState &pGPS, GameObject& obj, XMFLOAT4 color,
	XMFLOAT3 scale, XMFLOAT3 rotation
) : ID(obj.getID())
{
	// Connections
	this->head = &obj;
//	obj.SETgraphicsComponent(this);
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
}
/*_____________________________
|          END OF             |
|      PUBLIC FUNCTIONS       |
|_____________________________|
*/