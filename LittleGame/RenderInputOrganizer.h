#pragma once
#ifndef RENDERINPUTORGANIZER_H
#define RENDERINPUTORGANIZER_H

#include <vector>
#include "Camera.h"

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
	MatrixBufferCalc	rawMatrixData;
	MatrixBufferPack	packagedMatrixData;
	ID3D11Buffer*		constantBuffer;

	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Re-formats the WORLD, VIEW, & PROJECTION matrix data.
	2. Format Change Details: XMMATRIX --> XMFLOAT4X4.
	*/
	void packageMatrices();
	
	void drawGraphics(GraphicsComponent*& graphics);

public:
	void initialize(Camera& camera);
	void render(std::vector<GraphicsComponent*>& graphics);
	void cleanUp();
};

#endif // !RENDERINPUTORGANIZER_H
