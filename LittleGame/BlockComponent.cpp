#include "BlockComponent.h"
#include "GameObject.h"
#include "D3D.h"
#include "RenderInputOrganizer.h"

/*_____________________________
 |         START OF            |
 |     PRIVATE FUNCTIONS       |
 |_____________________________|
 */


void BlockComponent::createVertices(const float r, const float g, const float b, const float a)
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
	//Push the vertices into the vector (p0-p7)
	//Front p0, p1, p2, p3
	this->vertexData[0].pos = XMFLOAT3(-1.0, 1.0, -1.0);
	this->vertexData[1].pos = XMFLOAT3(1.0, 1.0, -1.0);
	this->vertexData[2].pos = XMFLOAT3(-1.0, -1.0, -1.0);
	this->vertexData[3].pos = XMFLOAT3(1.0, -1.0, -1.0);
	//Left p4, p0, p5, p2
	this->vertexData[8].pos = XMFLOAT3(-1.0, 1.0, 1.0);
	this->vertexData[4].pos = XMFLOAT3(-1.0, 1.0, -1.0);
	this->vertexData[9].pos = XMFLOAT3(-1.0, -1.0, 1.0);
	this->vertexData[6].pos = XMFLOAT3(-1.0, -1.0, -1.0);
	//Right p1, p6, p3, p7
	this->vertexData[9].pos = XMFLOAT3(1.0, 1.0, -1.0);
	this->vertexData[14].pos = XMFLOAT3(1.0, 1.0, 1.0);
	this->vertexData[11].pos = XMFLOAT3(1.0, -1.0, -1.0);
	this->vertexData[15].pos = XMFLOAT3(1.0, -1.0, 1.0);
	//Back p6, p4, p7, p5
	this->vertexData[18].pos = XMFLOAT3(-1.0, 1.0, 1.0);
	this->vertexData[16].pos = XMFLOAT3(-1.0, -1.0, 1.0);
	this->vertexData[19].pos = XMFLOAT3(1.0, 1.0, 1.0);
	this->vertexData[17].pos = XMFLOAT3(1.0, -1.0, 1.0);
	//Top p4, p6, p0, p1
	this->vertexData[20].pos = XMFLOAT3(-1.0, 1.0, 1.0);
	this->vertexData[22].pos = XMFLOAT3(1.0, 1.0, 1.0);
	this->vertexData[16].pos = XMFLOAT3(-1.0, 1.0, -1.0);
	this->vertexData[17].pos = XMFLOAT3(1.0, 1.0, -1.0);
	//Bottom p2, p3, p5, p7
	this->vertexData[22].pos = XMFLOAT3(-1.0, -1.0, -1.0);
	this->vertexData[23].pos = XMFLOAT3(1.0, -1.0, -1.0);
	this->vertexData[25].pos = XMFLOAT3(-1.0, -1.0, 1.0);
	this->vertexData[27].pos = XMFLOAT3(1.0, -1.0, 1.0);

	//Push the normals into the vector
	//Front
	
	this->vertexData[0].normal = XMFLOAT3(0.0, 0.0, -1.0);
	this->vertexData[1].normal = XMFLOAT3(0.0, 0.0, -1.0);
	this->vertexData[2].normal = XMFLOAT3(0.0, 0.0, -1.0);
	this->vertexData[3].normal = XMFLOAT3(0.0, 0.0, -1.0);
	//Left
	this->vertexData[4].normal = XMFLOAT3(-1.0, 0.0, 0.0);
	this->vertexData[0].normal = XMFLOAT3(-1.0, 0.0, 0.0);
	this->vertexData[5].normal = XMFLOAT3(-1.0, 0.0, 0.0);
	this->vertexData[2].normal = XMFLOAT3(-1.0, 0.0, 0.0);
	//Right
	this->vertexData[1].normal = XMFLOAT3(1.0, 0.0, 0.0);
	this->vertexData[6].normal = XMFLOAT3(1.0, 0.0, 0.0);
	this->vertexData[3].normal = XMFLOAT3(1.0, 0.0, 0.0);
	this->vertexData[7].normal = XMFLOAT3(1.0, 0.0, 0.0);
	//Back
	this->vertexData[6].normal = XMFLOAT3(0.0, 0.0, -1.0);
	this->vertexData[4].normal = XMFLOAT3(0.0, 0.0, -1.0);
	this->vertexData[7].normal = XMFLOAT3(0.0, 0.0, -1.0);
	this->vertexData[5].normal = XMFLOAT3(0.0, 0.0, -1.0);
	//Top
	this->vertexData[4].normal = XMFLOAT3(0.0, 1.0, 0.0);
	this->vertexData[6].normal = XMFLOAT3(0.0, 1.0, 0.0);
	this->vertexData[0].normal = XMFLOAT3(0.0, 1.0, 0.0);
	this->vertexData[1].normal = XMFLOAT3(0.0, 1.0, 0.0);
	//Bottom
	this->vertexData[2].normal = XMFLOAT3(0.0, -1.0, 0.0);
	this->vertexData[3].normal = XMFLOAT3(0.0, -1.0, 0.0);
	this->vertexData[5].normal = XMFLOAT3(0.0, -1.0, 0.0);
	this->vertexData[7].normal = XMFLOAT3(0.0, -1.0, 0.0);

	for (auto &i : this->vertexData) {
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
	//Push indices into the vector
	for (auto &i : this->indices) {
		i = index[i];
	}
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

BlockComponent::BlockComponent(size_t ID, const float r, const float g, const float b, const float a) : ID(ID)
{
	//Create vertices and indices for the box
	this->createVertices(r, g, b, a);
	//Set type to BLOCK
	this->type = OBJECTTYPE::BLOCK;
}

BlockComponent::~BlockComponent() 
{
}

void BlockComponent::recieve(GameObject& obj, Message msg)
{
}

void BlockComponent::render(RenderInputOrganizer * rio)
{
	rio->render(this);
}

const size_t BlockComponent::getID()
{
	return this->ID;
}

std::array<PrimitiveVertexData, 24>& BlockComponent::GETVertexData()
{
	return this->vertexData;
}

std::array<DWORD, 36>& BlockComponent::GETindices()
{
	return this->indices;
}

vColor& BlockComponent::GETcolor()
{
	return this->color;
}

OBJECTTYPE::TYPE BlockComponent::GETtype()
{
	return this->type;
}

/*_____________________________
|          END OF             |
|      PUBLIC FUNCTIONS       |
|_____________________________|
*/
