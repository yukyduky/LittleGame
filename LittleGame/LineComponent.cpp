#include "LineComponent.h"
#include "GameObject.h"

std::vector<Vertex> LineComponent::vertices;
std::vector<Vertex> LineComponent::normals;
std::vector<DWORD> LineComponent::indices;

/*_____________________________
|         START OF            |
|     PRIVATE FUNCTIONS       |
|_____________________________|
*/

void LineComponent::createVertices()
{
	/*
	p0_______________________p1
	
	p0 = (0.0f, 0.0f, 0.0f);
	p1 = (1.0f, 0.0f, 0.0f);
	*/
	//Push the vertices of the line (p0, p1).
	LineComponent::vertices.push_back(Vertex(0.0f, 0.0f, 0.0f));
	LineComponent::vertices.push_back(Vertex(1.0f, 0.0f, 0.0f));

	//Create indices for the line.
	DWORD index[] =
	{
		0, 1
	};
	//Push indices into the vector.
	for (int i = 0; i < 2; i++) {
		LineComponent::indices.push_back(index[i]);
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

LineComponent::LineComponent(size_t ID, vColor startColor, vColor endColor) : ID(ID)
{
	if (LineComponent::vertices.size() == 0) {
		//Create vertices and indices for the line
		this->createVertices();
	}
	//Set the colors of the box
	this->colors.push_back(startColor);
	this->colors.push_back(endColor);
	//Set type to LINE
	this->type = OBJECTTYPE::LINE;
}

LineComponent::~LineComponent()
{
}

void LineComponent::receive(GameObject& obj, Message msg)
{
}

const size_t LineComponent::getID()
{
	return this->ID;
}

std::vector<Vertex>& LineComponent::GETvertices()
{
	return LineComponent::vertices;
}

std::vector<DWORD>& LineComponent::GETindices()
{
	return LineComponent::indices;
}

std::vector<vColor>& LineComponent::GETcolor()
{
	return this->colors;
}

OBJECTTYPE::TYPE LineComponent::GETtype()
{
	return this->type;
}

/*_____________________________
|          END OF             |
|      PUBLIC FUNCTIONS       |
|_____________________________|
*/
