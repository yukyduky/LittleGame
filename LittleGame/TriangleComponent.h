#pragma once
#ifndef TRIANGLECOMPONENT_H
#define TRIANGLECOMPONENT_H
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN

#include "GraphicsComponent.h"
#include <vector>
#include <array>
#include <Windows.h>

struct PrimitiveVertexData;
class GamePlayState;

namespace T_NORMALS {
	enum {
		NORTH, SOUTH_EAST, SOUTH_WEST,
		UP, DOWN
	};
}
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
class TriangleComponent : public GraphicsComponent
{
private:
	const size_t ID;
	ID3D11Buffer* gVertexBuffer = nullptr;
	ID3D11Buffer* gIndexBuffer = nullptr;
	size_t stride = 0;
	size_t offset = 0;
	size_t numIndices = 0;
	vColor color;
	vColor colorOriginal;
	GameObject* head = nullptr;
	XMFLOAT3 points[6];
	XMFLOAT3 normals[5];
	double counter = 0;
	double transitionTime = 0;



	/*--------<INFORMATION>--------
	1. Creates a block with points ranging from -1.0 to 1.0 in x,y,z dimensions.
	2. All vertices is in modelspace with origin in the center of the block.
	3. Creates normals for the vertices
	4. Creates indices for the indexBuffer.
	*/
	void createVertices(XMFLOAT4 color);

	XMFLOAT3 calculateNormal(XMFLOAT3 point0, XMFLOAT3 joinedPoint, XMFLOAT3 point1);
	PrimitiveVertexData createPrimitiveVertexData(XMFLOAT3 point, XMFLOAT3 normal, XMFLOAT4 colour);

public:
	TriangleComponent(GamePlayState& pGPS, GameObject& obj, XMFLOAT4 color, XMFLOAT3 scale, XMFLOAT3 rotation);
	virtual ~TriangleComponent();


	virtual ID3D11Buffer*& GETvertexBuffer();
	virtual ID3D11Buffer*& GETindexBuffer();
	virtual size_t& GETstride();
	virtual size_t& GEToffset();
	virtual size_t& GETnumIndices();
	virtual XMFLOAT4X4& getWorld();

	void SETcolor(vColor color);
	vColor GETcolor();
	vColor GETcolorOriginal();

	/*--------<INFORMATION>--------
	1. Something
	*/
	virtual void receive(GameObject& obj, Message msg);
	virtual void update();
	/*--------<INFORMATION>--------
	1. Returns the ID of the component.
	*/
	virtual const size_t getID();
	virtual void cleanUp();
	virtual OBJECTSTATE::TYPE GETstate();
	void updateColor(vColor newColor);

};


#endif