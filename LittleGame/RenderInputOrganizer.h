#pragma once
#ifndef RENDERINPUTORGANIZER_H
#define RENDERINPUTORGANIZER_H

#include <vector>
#include <list>
#include <array>
#include "Camera.h"

constexpr int MAX_NUM_POINTLIGHTS = 50;

using namespace DirectX;

struct Light {
	XMFLOAT3 pos;
	float pad0;
	XMFLOAT3 diffuse;
	float pad1;
	XMFLOAT3 ambient;
	float pad2;
	XMFLOAT3 attenuation;
	float specPower;

	Light() {}
	Light(XMFLOAT3 pos, XMFLOAT3 diffuse, XMFLOAT3 ambient, XMFLOAT3 attenuation, float specPower) : 
		pos(pos), diffuse(diffuse), ambient(ambient), attenuation(attenuation), specPower(specPower) {}
};

struct LightPassData {
	float nrOfLights;
	XMFLOAT3 pad0;

	LightPassData() {}
};

struct MatrixBufferCalc {
	XMMATRIX* world;
	XMMATRIX* view;
	XMMATRIX* proj;

	XMMATRIX worldView;
	XMMATRIX worldViewProj;
};

struct MatrixBufferPack {
	XMFLOAT4X4 world;
	XMFLOAT4X4 worldViewProj;
};

// This is the 'packaged' format of the matrices, which we send to the shaders.


class GraphicsComponent;

class RenderInputOrganizer
{
private:
	std::vector<GraphicsComponent*> graphics;
	std::vector<Light>* lights;

	MatrixBufferCalc rawMatrixData;
	MatrixBufferPack packagedMatrixData;
	LightPassData lightPassData;
	ID3D11Buffer* cMatrixBuffer;
	ID3D11Buffer* cLightBuffer;
	ID3D11Buffer* cLightPassDataBuffer;


	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Re-formats the WORLD, VIEW, & PROJECTION matrix data.
	2. Format Change Details: XMMATRIX --> XMFLOAT4X4.
	*/
	void packageMatrices();
	
	void drawGraphics(GraphicsComponent*& graphics);

public:
	void initialize(Camera& camera, std::vector<Light>& lights);
	void render(std::vector<GraphicsComponent*>& graphics);
	void injectResourcesIntoSecondPass();
	void addGraphics(GraphicsComponent* graphics);
};

#endif // !RENDERINPUTORGANIZER_H
