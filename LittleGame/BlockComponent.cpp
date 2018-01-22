#include "BlockComponent.h"
#include "GameObject.h"

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
	this->vertices.push_back(PrimitiveVertex(-1.0, 1.0, -1.0));
	this->vertices.push_back(PrimitiveVertex(1.0, 1.0, -1.0));
	this->vertices.push_back(PrimitiveVertex(-1.0, -1.0, -1.0));
	this->vertices.push_back(PrimitiveVertex(1.0, -1.0, -1.0));
	this->vertices.push_back(PrimitiveVertex(-1.0, 1.0, 1.0));
	this->vertices.push_back(PrimitiveVertex(-1.0, -1.0, 1.0));
	this->vertices.push_back(PrimitiveVertex(1.0, 1.0, 1.0));
	this->vertices.push_back(PrimitiveVertex(1.0, -1.0, 1.0));

	//Create indices for the box
	DWORD index[] =
	{
		//Front p0, p1, p2, p3
		0, 1, 2,
		2, 1, 3,
		//Left p4, p0, p5, p2
		4, 0, 5,
		5, 0, 2,
		//Right p1, p6, p3, p7
		1, 6, 3,
		3, 6, 7,
		//Back p6, p4, p7, p5
		6, 4, 7,
		7, 4, 5,
		//Top p4, p6, p0, p1
		4, 6, 0,
		0, 6, 1,
		//Bottom p2, p3, p5, p7
		2, 3, 5,
		5, 3, 7
	};
	//Push indices into the vector
	for (int i = 0; i < 36; i++) {
		this->indices.push_back(index[i]);
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

void BlockComponent::recieve(GameObject& obj, Message msg)
{
}

const size_t BlockComponent::getID()
{
	return this->ID;
}

std::vector<PrimitiveVertex>& BlockComponent::GETvertices()
{
	return vertices;
}

std::vector<DWORD>& BlockComponent::GETindices()
{
	return indices;
}

PrimitiveColor& BlockComponent::GETcolor()
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
