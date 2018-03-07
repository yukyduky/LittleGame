#pragma once
#ifndef RENDERINPUTORGANIZER_H
#define RENDERINPUTORGANIZER_H

#include <vector>
#include <list>
#include <array>
#include "Camera.h"

constexpr int MAX_NUM_POINTLIGHTS = 100;
constexpr int MAX_NUM_FLOORGRIDS_X = 35;
constexpr int MAX_NUM_FLOORGRIDS_Y = 35;

using namespace DirectX;

struct tileData;

struct Light {
	XMFLOAT3 pos;
	float pad0;
	XMFLOAT3 diffuse;
	float pad1;
	XMFLOAT3 ambient;
	float pad2;
	XMFLOAT3 attenuation;
	float specPower;

	Light() : pos(XMFLOAT3(0.0f, 0.0f, 0.0f)), diffuse(XMFLOAT3(0.0f, 0.0f, 0.0f)), ambient(XMFLOAT3(0.0f, 0.0f, 0.0f)) {}
	Light(XMFLOAT3 pos, XMFLOAT3 diffuse, XMFLOAT3 ambient, XMFLOAT3 attenuation, float specPower) : 
		pos(pos), diffuse(diffuse), ambient(ambient), attenuation(attenuation), specPower(specPower) {}
};

struct FloorGrid
{
	XMFLOAT3 color;
	float height;
};

struct LightPassData {
	FloorGrid grid[MAX_NUM_FLOORGRIDS_X][MAX_NUM_FLOORGRIDS_Y];
	XMFLOAT3 camPos;
	float nrOfLights;
	XMFLOAT2 arenaDims;
	XMFLOAT2 gridDims;
	XMFLOAT2 gridStartPos;
	XMFLOAT2 screenDims;

	LightPassData() {}
};

struct MatrixBufferCalc {
	XMFLOAT4X4 world;
	XMFLOAT4X4* view = nullptr;
	XMFLOAT4X4* proj = nullptr;

	XMFLOAT4X4 worldView;
	XMFLOAT4X4 worldViewProj;
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
	std::vector<Light>* lights = nullptr;

	MatrixBufferCalc rawMatrixData;
	MatrixBufferPack packagedMatrixData;
	LightPassData lightPassData;
	ID3D11Buffer* cMatrixBuffer = nullptr;
	ID3D11Buffer* cLightBuffer = nullptr;
	ID3D11Buffer* cLightPassDataBuffer = nullptr;


	/*- - - - - - - -<INFORMATION>- - - - - - - -
	1. Re-formats the WORLD, VIEW, & PROJECTION matrix data.
	2. Format Change Details: XMMATRIX --> XMFLOAT4X4.
	*/
	void packageMatrices();
	
	void drawGraphics(GraphicsComponent*& graphics);

public:
	void initialize(Camera& camera, std::vector<Light>& lights);
	void render(std::list<GraphicsComponent*>& graphics);
	void injectResourcesIntoSecondPass(const std::vector<std::vector<tileData>>& grid);
	void cleanUp();
};

#endif // !RENDERINPUTORGANIZER_H
