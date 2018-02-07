#pragma once
#ifndef BLOCKCOMPONENT_H_
#define BLOCKCOMPONENT_H_

#include "GraphicsComponent.h"
#include <vector>
#include <array>
#include <Windows.h>

struct PrimitiveVertexData;
class GamePlayState;

class BlockComponent : public GraphicsComponent
{
private:
	const size_t ID;
	ID3D11Buffer* gVertexBuffer;
	ID3D11Buffer* gIndexBuffer;
	size_t stride;
	size_t offset;
	size_t numIndices;
	GameObject* head;

	

	/*--------<INFORMATION>--------
	1. Creates a block with points ranging from -1.0 to 1.0 in x,y,z dimensions.
	2. All vertices is in modelspace with origin in the center of the block.
	3. Creates normals for the vertices
	4. Creates indices for the indexBuffer.
	*/
	void createVertices(XMFLOAT4 color);
	
public:
	BlockComponent(GamePlayState& pGPS, GameObject& obj, XMFLOAT4 color, XMFLOAT3 scale, XMFLOAT3 rotation);
	~BlockComponent();


	virtual ID3D11Buffer*& GETvertexBuffer();
	virtual ID3D11Buffer*& GETindexBuffer();
	virtual size_t& GETstride();
	virtual size_t& GEToffset();
	virtual size_t& GETnumIndices();
	virtual XMMATRIX& getWorld();


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
	virtual bool checkIfDead();
	
};


#endif