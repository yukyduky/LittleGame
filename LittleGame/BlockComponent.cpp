#include "BlockComponent.h"
#include "GameObject.h"
#include "Locator.h"

/*
std::vector<Vertex> BlockComponent::vertices;
std::vector<Vertex> BlockComponent::normals;
std::vector<DWORD> BlockComponent::indices;
*/
/*_____________________________
 |         START OF            |
 |     PRIVATE FUNCTIONS       |
 |_____________________________|
 */


void BlockComponent::createVertices(float r, float g, float b, float a)
{
	/*--------<INFORMATION>--------
	1. Creates a box with points ranging from -1.0 to 1.0 in x,y,z dimensions.
	2. Sets the color of every vertex to the r,g,b in the paramaters.
	3. All vertices is in modelspace with origin in the center of the box.
	4. Creates indices for the indexbuffer.
	*/

	/*
	   p4__________p6
	   /|         /|
	p0/_|______p1/ |
	  | |       |  |
	  | |p5_____|__|p7
	  | /       | /
	  |/________|/
	  p2        p3

	p0 = (-1.0, 1.0, -1.0)
	p1 = (1.0, 1.0, -1.0)
	p2 = (-1.0, -1.0, -1.0)
	p3 = (1.0, -1.0, -1.0)
	p4 = (-1.0, 1.0, 1.0)
	p5 = (-1.0, -1.0, 1.0)
	p6 = (1.0, 1.0, 1.0)
	p7 = (1.0, -1.0, 1.0)
	*/
	XMFLOAT3 p0(-1.0f, 1.0f, -1.0f);
	XMFLOAT3 p1(1.0f, 1.0f, -1.0f);
	XMFLOAT3 p2(-1.0f, -1.0f, -1.0f);
	XMFLOAT3 p3(1.0f, -1.0f, -1.0f);
	XMFLOAT3 p4(-1.0f, 1.0f, 1.0f);
	XMFLOAT3 p5(-1.0f, -1.0f, 1.0f);
	XMFLOAT3 p6(1.0f, 1.0f, 1.0f);
	XMFLOAT3 p7(1.0f, -1.0f, 1.0f);

	XMFLOAT3 normalFront(0.0f, 0.0f, -1.0f);
	XMFLOAT3 normalLeft(-1.0f, 0.0f, 0.0f);
	XMFLOAT3 normalRight(1.0f, 0.0f, 0.0f);
	XMFLOAT3 normalBack(0.0f, 0.0f, -1.0f);
	XMFLOAT3 normalTop(0.0f, 1.0f, 0.0f);
	XMFLOAT3 normalBottom(0.0f, -1.0f, 0.0f);

	std::array<PrimitiveVertexData, 24> vertexData2;
	//Front p0, p1, p2, p3
	vertexData2[0] = PrimitiveVertexData(p0.x, p0.y, p0.z, normalFront.x, normalFront.y, normalFront.z, r, g, b, a);
	vertexData2[0] = PrimitiveVertexData(p1.x, p1.y, p1.z, normalFront.x, normalFront.y, normalFront.z, r, g, b, a);
	vertexData2[0] = PrimitiveVertexData(p2.x, p2.y, p2.z, normalFront.x, normalFront.y, normalFront.z, r, g, b, a);
	vertexData2[0] = PrimitiveVertexData(p3.x, p3.y, p3.z, normalFront.x, normalFront.y, normalFront.z, r, g, b, a);
	//Left p4, p0, p5, p2
	vertexData2[0] = PrimitiveVertexData(p4.x, p4.y, p4.z, normalLeft.x, normalLeft.y, normalLeft.z, r, g, b, a);
	vertexData2[0] = PrimitiveVertexData(p0.x, p0.y, p0.z, normalLeft.x, normalLeft.y, normalLeft.z, r, g, b, a);
	vertexData2[0] = PrimitiveVertexData(p5.x, p5.y, p5.z, normalLeft.x, normalLeft.y, normalLeft.z, r, g, b, a);
	vertexData2[0] = PrimitiveVertexData(p2.x, p2.y, p2.z, normalLeft.x, normalLeft.y, normalLeft.z, r, g, b, a);
	//Right p1, p6, p3, p7
	vertexData2[0] = PrimitiveVertexData(p1.x, p1.y, p1.z, normalRight.x, normalRight.y, normalRight.z, r, g, b, a);
	vertexData2[0] = PrimitiveVertexData(p6.x, p6.y, p6.z, normalRight.x, normalRight.y, normalRight.z, r, g, b, a);
	vertexData2[0] = PrimitiveVertexData(p3.x, p3.y, p3.z, normalRight.x, normalRight.y, normalRight.z, r, g, b, a);
	vertexData2[0] = PrimitiveVertexData(p7.x, p7.y, p7.z, normalRight.x, normalRight.y, normalRight.z, r, g, b, a);
	//Back p6, p4, p7, p5
	vertexData2[0] = PrimitiveVertexData(p6.x, p6.y, p6.z, normalBack.x, normalBack.y, normalBack.z, r, g, b, a);
	vertexData2[0] = PrimitiveVertexData(p4.x, p4.y, p4.z, normalBack.x, normalBack.y, normalBack.z, r, g, b, a);
	vertexData2[0] = PrimitiveVertexData(p7.x, p7.y, p7.z, normalBack.x, normalBack.y, normalBack.z, r, g, b, a);
	vertexData2[0] = PrimitiveVertexData(p5.x, p5.y, p5.z, normalBack.x, normalBack.y, normalBack.z, r, g, b, a);
	//Top p4, p6, p0, p1
	vertexData2[0] = PrimitiveVertexData(p4.x, p4.y, p4.z, normalTop.x, normalTop.y, normalTop.z, r, g, b, a);
	vertexData2[0] = PrimitiveVertexData(p6.x, p6.y, p6.z, normalTop.x, normalTop.y, normalTop.z, r, g, b, a);
	vertexData2[0] = PrimitiveVertexData(p0.x, p0.y, p0.z, normalTop.x, normalTop.y, normalTop.z, r, g, b, a);
	vertexData2[0] = PrimitiveVertexData(p1.x, p1.y, p1.z, normalTop.x, normalTop.y, normalTop.z, r, g, b, a);
	//Bottom p2, p3, p5, p7
	vertexData2[0] = PrimitiveVertexData(p2.x, p2.y, p2.z, normalBottom.x, normalBottom.y, normalBottom.z, r, g, b, a);
	vertexData2[0] = PrimitiveVertexData(p3.x, p3.y, p3.z, normalBottom.x, normalBottom.y, normalBottom.z, r, g, b, a);
	vertexData2[0] = PrimitiveVertexData(p5.x, p5.y, p5.z, normalBottom.x, normalBottom.y, normalBottom.z, r, g, b, a);
	vertexData2[0] = PrimitiveVertexData(p7.x, p7.y, p7.z, normalBottom.x, normalBottom.y, normalBottom.z, r, g, b, a);



	/*
	//Push the vertices into the vector (p0-p7)
	//Front p0, p1, p2, p3
	vertexData[0].pos = XMFLOAT3(-1.0, 1.0, -1.0);
	vertexData[1].pos = XMFLOAT3(1.0, 1.0, -1.0);
	vertexData[2].pos = XMFLOAT3(-1.0, -1.0, -1.0);
	vertexData[3].pos = XMFLOAT3(1.0, -1.0, -1.0);
	//Left p4, p0, p5, p2
	vertexData[4].pos = XMFLOAT3(-1.0, 1.0, 1.0);
	vertexData[5].pos = XMFLOAT3(-1.0, 1.0, -1.0);
	vertexData[6].pos = XMFLOAT3(-1.0, -1.0, 1.0);
	vertexData[7].pos = XMFLOAT3(-1.0, -1.0, -1.0);
	//Right p1, p6, p3, p7
	vertexData[8].pos = XMFLOAT3(1.0, 1.0, -1.0);
	vertexData[9].pos = XMFLOAT3(1.0, 1.0, 1.0);
	vertexData[10].pos = XMFLOAT3(1.0, -1.0, -1.0);
	vertexData[11].pos = XMFLOAT3(1.0, -1.0, 1.0);
	//Back p6, p4, p7, p5
	vertexData[12].pos = XMFLOAT3(-1.0, 1.0, 1.0);
	vertexData[13].pos = XMFLOAT3(-1.0, -1.0, 1.0);
	vertexData[14].pos = XMFLOAT3(1.0, 1.0, 1.0);
	vertexData[15].pos = XMFLOAT3(1.0, -1.0, 1.0);
	//Top p4, p6, p0, p1
	vertexData[16].pos = XMFLOAT3(-1.0, 1.0, 1.0);
	vertexData[17].pos = XMFLOAT3(1.0, 1.0, 1.0);
	vertexData[18].pos = XMFLOAT3(-1.0, 1.0, -1.0);
	vertexData[19].pos = XMFLOAT3(1.0, 1.0, -1.0);
	//Bottom p2, p3, p5, p7
	vertexData[20].pos = XMFLOAT3(-1.0, -1.0, -1.0);
	vertexData[21].pos = XMFLOAT3(1.0, -1.0, -1.0);
	vertexData[22].pos = XMFLOAT3(-1.0, -1.0, 1.0);
	vertexData[23].pos = XMFLOAT3(1.0, -1.0, 1.0);

	//Push the normals into the vector
	//Front
	vertexData[0].normal = XMFLOAT3(0.0, 0.0, -1.0);
	vertexData[1].normal = XMFLOAT3(0.0, 0.0, -1.0);
	vertexData[2].normal = XMFLOAT3(0.0, 0.0, -1.0);
	vertexData[3].normal = XMFLOAT3(0.0, 0.0, -1.0);
	//Left
	vertexData[4].normal = XMFLOAT3(-1.0, 0.0, 0.0);
	vertexData[5].normal = XMFLOAT3(-1.0, 0.0, 0.0);
	vertexData[6].normal = XMFLOAT3(-1.0, 0.0, 0.0);
	vertexData[7].normal = XMFLOAT3(-1.0, 0.0, 0.0);
	//Right
	vertexData[8].normal = XMFLOAT3(1.0, 0.0, 0.0);
	vertexData[9].normal = XMFLOAT3(1.0, 0.0, 0.0);
	vertexData[10].normal = XMFLOAT3(1.0, 0.0, 0.0);
	vertexData[11].normal = XMFLOAT3(1.0, 0.0, 0.0);
	//Back
	vertexData[12].normal = XMFLOAT3(0.0, 0.0, -1.0);
	vertexData[13].normal = XMFLOAT3(0.0, 0.0, -1.0);
	vertexData[14].normal = XMFLOAT3(0.0, 0.0, -1.0);
	vertexData[15].normal = XMFLOAT3(0.0, 0.0, -1.0);
	//Top
	vertexData[16].normal = XMFLOAT3(0.0, 1.0, 0.0);
	vertexData[17].normal = XMFLOAT3(0.0, 1.0, 0.0);
	vertexData[18].normal = XMFLOAT3(0.0, 1.0, 0.0);
	vertexData[19].normal = XMFLOAT3(0.0, 1.0, 0.0);
	//Bottom
	vertexData[20].normal = XMFLOAT3(0.0, -1.0, 0.0);
	vertexData[21].normal = XMFLOAT3(0.0, -1.0, 0.0);
	vertexData[22].normal = XMFLOAT3(0.0, -1.0, 0.0);
	vertexData[23].normal = XMFLOAT3(0.0, -1.0, 0.0);

	for (auto &i : vertexData) {
		i.color = XMFLOAT4(this->color.r, this->color.g, this->color.b, this->color.a);
	}

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
	this->numIndices = 36;*/

	std::array<PrimitiveVertexData, 3> vertexData;

	vertexData[0] = PrimitiveVertexData(0.0f, 0.5f, 0.0f, -1.0f, -1.0f, -1.0f, 0.0f, 255.0f, 0.0f, 255.0f);
	vertexData[1] = PrimitiveVertexData(0.5f, -0.5f, 0.0f, -1.0f, -1.0f, -1.0f, 0.0f, 255.0f, 0.0f, 255.0f);
	vertexData[2] = PrimitiveVertexData(-0.5f, -0.5f, 0.0f, -1.0f, -1.0f, -1.0f, 0.0f, 255.0f, 0.0f, 255.0f);

	DWORD index[] =
	{
		0, 1, 2,
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

BlockComponent::BlockComponent(GameObject& obj, float r, float g, float b, float a) : ID(obj.getID())
{
	this->createVertices(r, g, b, a);
	//Set the color of the box
	this->color.r = r;
	this->color.g = g;
	this->color.b = b;
	this->color.a = a;
}

BlockComponent::~BlockComponent() 
{
}

void BlockComponent::receive(GameObject& obj, Message msg)
{
}

ID3D11Buffer *& BlockComponent::GETvertexBuffer()
{
	return this->gVertexBuffer;
}

ID3D11Buffer *& BlockComponent::GETindexBuffer()
{
	return this->gIndexBuffer;
}

size_t & BlockComponent::GETstride()
{
	return this->stride;
}

size_t & BlockComponent::GEToffset()
{
	return this->offset;
}

size_t & BlockComponent::GETnumIndices()
{
	return this->numIndices;
}

const size_t BlockComponent::getID()
{
	return this->ID;
}

/*_____________________________
|          END OF             |
|      PUBLIC FUNCTIONS       |
|_____________________________|
*/
