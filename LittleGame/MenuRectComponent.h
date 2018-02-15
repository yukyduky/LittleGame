#pragma once
#ifndef MENURECTCOMPONENT_H
#define MENURECTCOMPONENT_H

#include "GraphicsComponent.h"
#include "Camera.h"

#include <vector>
#include <array>
#include <Windows.h>

struct PrimitiveVertexData;
class MenuState;

class MenuRectComponent : public GraphicsComponent
{
private:
	const size_t ID;
	ID3D11Buffer* gVertexBuffer;
	ID3D11Buffer* gIndexBuffer;
	size_t stride;
	size_t offset;
	size_t numIndices;
	vColor color;
	MenuObject* head;
	XMFLOAT3 points[4];
	XMFLOAT3 normal;

	void createVertices(XMFLOAT4 color);

public:
	MenuRectComponent(Menu& pMenu, MenuObject& obj, Camera &cam, XMFLOAT4 color, XMFLOAT3 scale);
	~MenuRectComponent();


	virtual ID3D11Buffer*& GETvertexBuffer();
	virtual ID3D11Buffer*& GETindexBuffer();
	virtual size_t& GETstride();
	virtual size_t& GEToffset();
	virtual size_t& GETnumIndices();
	virtual XMMATRIX& getWorld();


	virtual void receive(GameObject& obj, Message msg);
	virtual void update();
	/*--------<INFORMATION>--------
	1. Returns the ID of the component.
	*/
	virtual const size_t getID();
	virtual void cleanUp();
	virtual OBJECTSTATE::TYPE GETstate();

};


#endif