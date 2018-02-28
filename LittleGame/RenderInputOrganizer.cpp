#include "RenderInputOrganizer.h"
#include "GraphicsComponent.h"
#include "Locator.h"
#include "ArenaGlobals.h"


void RenderInputOrganizer::packageMatrices() {
	XMMATRIX worldMatrix = XMLoadFloat4x4(&this->rawMatrixData.world);
	XMMATRIX viewMatrix = XMLoadFloat4x4(this->rawMatrixData.view);
	XMMATRIX projMatrix = XMLoadFloat4x4(this->rawMatrixData.proj);

	worldMatrix = XMMatrixTranspose(worldMatrix);

	XMStoreFloat4x4(
		&this->packagedMatrixData.world,
		worldMatrix
	);

	worldMatrix = XMLoadFloat4x4(&this->rawMatrixData.world);

	XMMATRIX worldViewProj = worldMatrix * viewMatrix * projMatrix;
	worldViewProj = XMMatrixTranspose(worldViewProj);

	XMStoreFloat4x4(
		&this->packagedMatrixData.worldViewProj,
		worldViewProj
	);
}

void RenderInputOrganizer::drawGraphics(GraphicsComponent *& graphics)
{
	// Get world matrix
	this->rawMatrixData.world = graphics->getWorld();

	this->packageMatrices();

	// Map the matrix package to the buffer
	Locator::getD3D()->mapConstantBuffer(&this->cMatrixBuffer,	&this->packagedMatrixData, sizeof(this->packagedMatrixData));

	// Set the current constant buffer to the matrix package buffer
	Locator::getD3D()->setConstantBuffer(this->cMatrixBuffer, SHADER::VERTEX, 0, 1);

	Locator::getD3D()->setVertexBuffer(&graphics->GETvertexBuffer(), graphics->GETstride(), graphics->GEToffset());
	Locator::getD3D()->setIndexBuffer(graphics->GETindexBuffer(), 0);

	Locator::getD3D()->GETgDevCon()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Locator::getD3D()->GETgDevCon()->DrawIndexed(graphics->GETnumIndices(), 0, 0);
}

void RenderInputOrganizer::initialize(Camera& camera, std::vector<Light>& lights) {
	this->lights = &lights;

	this->rawMatrixData.view = &camera.GETviewMatrix();
	this->rawMatrixData.proj = &camera.GETprojMatrix();

	this->lightPassData.camDir = camera.GETfacingDirFloat3();
	this->lightPassData.camPos = camera.GETcameraPos();
	this->lightPassData.arenaDims = XMFLOAT2(ARENADATA::GETarenaWidth(), ARENADATA::GETarenaHeight());
	this->lightPassData.gridDims = XMFLOAT2(ARENADATA::GETsquareSize(), ARENADATA::GETsquareSize());
	this->lightPassData.gridStartPos = XMFLOAT2(0.0f, 0.0f);

	Locator::getD3D()->createConstantBuffer(
		&this->cMatrixBuffer,
		sizeof(MatrixBufferPack)
	);

	Locator::getD3D()->createConstantBuffer(&this->cLightPassDataBuffer, sizeof(LightPassData));
	Locator::getD3D()->createConstantBuffer(&this->cLightBuffer, sizeof(Light) * MAX_NUM_POINTLIGHTS);
}

void RenderInputOrganizer::render(std::list<GraphicsComponent*>& graphics)
{
	for (auto &i : graphics) {
		if (i->GETstate() != OBJECTSTATE::TYPE::INVISIBLE) {
			this->drawGraphics(i);
		}
	}
}

void RenderInputOrganizer::injectResourcesIntoSecondPass(const std::vector<std::vector<tileData>>& grid)
{
	for (int i = 0; i < grid.size(); i++) {
		for (int j = 0; j < grid[i].size(); j++) {
			this->lightPassData.grid[i][j].color = grid[i][j].color;
			this->lightPassData.grid[i][j].height = grid[i][j].posY;
		}
	}

	size_t size = this->lights->size() < MAX_NUM_POINTLIGHTS ? this->lights->size() : MAX_NUM_POINTLIGHTS;

	this->lightPassData.nrOfLights = static_cast<float>(size);

	Locator::getD3D()->mapConstantBuffer(&this->cLightPassDataBuffer, &this->lightPassData, sizeof(LightPassData));
	Locator::getD3D()->setConstantBuffer(this->cLightPassDataBuffer, SHADER::PIXEL, 0, 1);

	Locator::getD3D()->mapConstantBuffer(&this->cLightBuffer, this->lights->data(), sizeof(Light) * size);
	Locator::getD3D()->setConstantBuffer(this->cLightBuffer, SHADER::PIXEL, 1, 1);
}

void RenderInputOrganizer::cleanUp()
{
	this->cLightBuffer->Release();
	this->cLightPassDataBuffer->Release();
	this->cMatrixBuffer->Release();
}