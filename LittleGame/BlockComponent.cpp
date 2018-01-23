#include "BlockComponent.h"
#include "GameObject.h"

std::vector<Vertex> BlockComponent::vertices;
std::vector<Vertex> BlockComponent::normals;
std::vector<DWORD> BlockComponent::indices;

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
	BlockComponent::vertices.push_back(Vertex(-1.0, 1.0, -1.0));
	BlockComponent::vertices.push_back(Vertex(1.0, 1.0, -1.0));
	BlockComponent::vertices.push_back(Vertex(-1.0, -1.0, -1.0));
	BlockComponent::vertices.push_back(Vertex(1.0, -1.0, -1.0));
	//Left p4, p0, p5, p2
	BlockComponent::vertices.push_back(Vertex(-1.0, 1.0, 1.0));
	BlockComponent::vertices.push_back(Vertex(-1.0, 1.0, -1.0));
	BlockComponent::vertices.push_back(Vertex(-1.0, -1.0, 1.0));
	BlockComponent::vertices.push_back(Vertex(-1.0, -1.0, -1.0));
	//Right p1, p6, p3, p7
	BlockComponent::vertices.push_back(Vertex(1.0, 1.0, -1.0));
	BlockComponent::vertices.push_back(Vertex(1.0, 1.0, 1.0));
	BlockComponent::vertices.push_back(Vertex(1.0, -1.0, -1.0));
	BlockComponent::vertices.push_back(Vertex(1.0, -1.0, 1.0));
	//Back p6, p4, p7, p5
	BlockComponent::vertices.push_back(Vertex(-1.0, 1.0, 1.0));
	BlockComponent::vertices.push_back(Vertex(-1.0, -1.0, 1.0));
	BlockComponent::vertices.push_back(Vertex(1.0, 1.0, 1.0));
	BlockComponent::vertices.push_back(Vertex(1.0, -1.0, 1.0));
	//Top p4, p6, p0, p1
	BlockComponent::vertices.push_back(Vertex(-1.0, 1.0, 1.0));
	BlockComponent::vertices.push_back(Vertex(1.0, 1.0, 1.0));
	BlockComponent::vertices.push_back(Vertex(-1.0, 1.0, -1.0));
	BlockComponent::vertices.push_back(Vertex(1.0, 1.0, -1.0));
	//Bottom p2, p3, p5, p7
	BlockComponent::vertices.push_back(Vertex(-1.0, -1.0, -1.0));
	BlockComponent::vertices.push_back(Vertex(1.0, -1.0, -1.0));
	BlockComponent::vertices.push_back(Vertex(-1.0, -1.0, 1.0));
	BlockComponent::vertices.push_back(Vertex(1.0, -1.0, 1.0));

	//Push the normals into the vector
	//Front
	BlockComponent::normals.push_back(Vertex(0.0, 0.0, -1.0));
	BlockComponent::normals.push_back(Vertex(0.0, 0.0, -1.0));
	BlockComponent::normals.push_back(Vertex(0.0, 0.0, -1.0));
	BlockComponent::normals.push_back(Vertex(0.0, 0.0, -1.0));
	//Left
	BlockComponent::normals.push_back(Vertex(-1.0, 0.0, 0.0));
	BlockComponent::normals.push_back(Vertex(-1.0, 0.0, 0.0));
	BlockComponent::normals.push_back(Vertex(-1.0, 0.0, 0.0));
	BlockComponent::normals.push_back(Vertex(-1.0, 0.0, 0.0));
	//Right
	BlockComponent::normals.push_back(Vertex(1.0, 0.0, 0.0));
	BlockComponent::normals.push_back(Vertex(1.0, 0.0, 0.0));
	BlockComponent::normals.push_back(Vertex(1.0, 0.0, 0.0));
	BlockComponent::normals.push_back(Vertex(1.0, 0.0, 0.0));
	//Back
	BlockComponent::normals.push_back(Vertex(0.0, 0.0, -1.0));
	BlockComponent::normals.push_back(Vertex(0.0, 0.0, -1.0));
	BlockComponent::normals.push_back(Vertex(0.0, 0.0, -1.0));
	BlockComponent::normals.push_back(Vertex(0.0, 0.0, -1.0));
	//Top
	BlockComponent::normals.push_back(Vertex(0.0, 1.0, 0.0));
	BlockComponent::normals.push_back(Vertex(0.0, 1.0, 0.0));
	BlockComponent::normals.push_back(Vertex(0.0, 1.0, 0.0));
	BlockComponent::normals.push_back(Vertex(0.0, 1.0, 0.0));
	//Bottom
	BlockComponent::normals.push_back(Vertex(0.0, -1.0, 0.0));
	BlockComponent::normals.push_back(Vertex(0.0, -1.0, 0.0));
	BlockComponent::normals.push_back(Vertex(0.0, -1.0, 0.0));
	BlockComponent::normals.push_back(Vertex(0.0, -1.0, 0.0));

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
	for (int i = 0; i < 36; i++) {
		BlockComponent::indices.push_back(index[i]);
	}

	this->color.r = r;
	this->color.g = g;
	this->color.b = b;
	this->color.a = a;
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

void BlockComponent::receive(GameObject& obj, Message msg)
{
}

const size_t BlockComponent::getID()
{
	return this->ID;
}

std::vector<Vertex>& BlockComponent::GETvertices()
{
	return BlockComponent::vertices;
}

std::vector<Vertex>& BlockComponent::GETnormals()
{
	return BlockComponent::normals;
}

std::vector<DWORD>& BlockComponent::GETindices()
{
	return BlockComponent::indices;
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
