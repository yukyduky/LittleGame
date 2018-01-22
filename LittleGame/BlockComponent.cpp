#include "BlockComponent.h"

BlockComponent::BlockComponent(const float x, const float y, const float z,
										const float r, const float g, const float b, const float a)
{
	this->nrOfVertices = 8;
	this->vertices = this->createBuffers(x, y, z, r, g, b, a);
}

BlockComponent::~BlockComponent() 
{
	this->vertexBuffer->Release();
	this->indexBuffer->Release();
}

Vertex* BlockComponent::createBuffers(const float x, const float y, const float z,
	const float r, const float g, const float b, const float a) 
{
	/*
		x,y,z parameters determines the size of the Block in all three dimensions.
		p4__________p6
		 /|         /|
	  p0/_|______p1/ |
		| |       |  |
		| |p5_____|__|p7
		| /       | /
		|/________|/
		p2        p3
	*/
	Vertex v[] = 
	{
		//Front p0,p1,p2,p3
		Vertex(-x, y, -z, r, g, b, a),
		Vertex(x, y, -z, r, g, b, a),
		Vertex(-x, -y, -z, r, g, b, a),
		Vertex(x, -y, -z, r, g, b, a),
		//Back p6, p4, p7, p5
		Vertex(x, y, z, r, g, b, a),
		Vertex(-x, y, z, r, g, b, a),
		Vertex(x, -y, z, r, g, b, a),
		Vertex(-x, -y, z, r, g, b, a),
	};

	//Create the vertexBuffer
	D3D::createVertexBuffer(v, &this->vertexBuffer, sizeof(Vertex) * 8);
	
	//Create indices for the box
	DWORD indices[] =
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
		//Bot p2, p3, p5, p7
		2, 3, 5,
		5, 3, 7
	};

	D3D::createIndexBuffer(indices, &this->indexBuffer, sizeof(DWORD) * 12 * 3);
}

ID3D11Buffer* BlockComponent::GETvertexBuffer()
{
	return this->vertexBuffer;
}

ID3D11Buffer* BlockComponent::GETindexBuffer()
{
	return this->indexBuffer;
}