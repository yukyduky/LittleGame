#pragma once
#ifndef RENDERINPUTORGANIZER_H
#define RENDERINPUTORGANIZER_H

#include <vector>
#include <list>
#include "Camera.h"

struct Light
{
	XMVECTOR pos;
	float pad0;
	XMVECTOR diffuse;
	float pad1;
	XMVECTOR ambient;
	float pad2;
	XMVECTOR attenuation;
	float specPower;
};

struct MatrixBufferCalc {
	DirectX::XMMATRIX* world;
	DirectX::XMMATRIX* view;
	DirectX::XMMATRIX* proj;

	DirectX::XMMATRIX worldView;
	DirectX::XMMATRIX worldViewProj;
};

struct MatrixBufferPack {
	DirectX::XMFLOAT4X4 world;
	DirectX::XMFLOAT4X4 worldViewProj;

	DirectX::XMFLOAT3 ka;
	float padding1;
	DirectX::XMFLOAT3 kd;
	float padding2;
	DirectX::XMFLOAT3 ks;
	float padding3;
};

// This is the 'packaged' format of the matrices, which we send to the shaders.


class GraphicsComponent;

class RenderInputOrganizer
{
private:
	std::vector<GraphicsComponent*> graphics;
	std::list<Light>* lights;

	MatrixBufferCalc	rawMatrixData;
	MatrixBufferPack	packagedMatrixData;
	ID3D11Buffer*		cMatrixBuffer;
	ID3D11Buffer*		cLightBuffer;

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Re-formats the WORLD, VIEW, & PROJECTION matrix data.
	2. Format Change Details: XMMATRIX --> XMFLOAT4X4.
	*/
	void packageMatrices();
	
	void drawGraphics(GraphicsComponent*& graphics);

public:
	void initialize(Camera& camera, std::list<Light>*& lights);
	void render();
	void injectResourcesIntoSecondPass();
	void addGraphics(GraphicsComponent* graphics);
};

#endif // !RENDERINPUTORGANIZER_H
