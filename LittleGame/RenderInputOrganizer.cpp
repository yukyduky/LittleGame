#include "RenderInputOrganizer.h"
#include "GraphicsComponent.h"
#include "Locator.h"


void RenderInputOrganizer::packageMatrices() {
	XMMATRIX world = *this->rawMatrixData.world;
	world = XMMatrixTranspose(world);
	XMStoreFloat4x4(
		&this->packagedMatrixData.world,
		world
	);

	this->rawMatrixData.worldViewProj = (*this->rawMatrixData.world) * (*this->rawMatrixData.view) * (*this->rawMatrixData.proj);
	this->rawMatrixData.worldViewProj = XMMatrixTranspose(this->rawMatrixData.worldViewProj);
	XMStoreFloat4x4(
		&this->packagedMatrixData.worldViewProj,
		this->rawMatrixData.worldViewProj
	);
}

void RenderInputOrganizer::drawGraphics(GraphicsComponent *& graphics)
{
	
	// Get world matrix
	this->rawMatrixData.world = &graphics->getWorld();
	// Calculate matrices and convert to XMFLOAT4x4

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

void RenderInputOrganizer::injectResourcesIntoSecondPass()
{
	size_t size = this->lights->size() < MAX_NUM_POINTLIGHTS ? this->lights->size() : MAX_NUM_POINTLIGHTS;

	this->lightPassData.nrOfLights = size;

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