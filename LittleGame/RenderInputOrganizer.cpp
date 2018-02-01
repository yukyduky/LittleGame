#include "RenderInputOrganizer.h"
#include "GraphicsComponent.h"
#include "Locator.h"


void RenderInputOrganizer::packageMatrices() {
	XMStoreFloat4x4(
		&this->packagedMatrixData.world,
		*this->rawMatrixData.world
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

void RenderInputOrganizer::initialize(Camera& camera, std::list<Light>& lights) {
	this->lights = &lights;

	this->rawMatrixData.view = &camera.GETviewMatrix();
	this->rawMatrixData.proj = &camera.GETprojMatrix();

	Locator::getD3D()->createConstantBuffer(
		&this->cMatrixBuffer,
		sizeof(this->packagedMatrixData)
	);

	for (auto &i : this->cLightBuffer) {
		Locator::getD3D()->createConstantBuffer(
			&i,
			sizeof(Light)
		);
	}
}

void RenderInputOrganizer::render()
{
	for (auto &i : this->graphics) {
		this->drawGraphics(i);
	}
}

void RenderInputOrganizer::injectResourcesIntoSecondPass()
{
	int i = 0;
	for (std::list<Light>::iterator it = this->lights->begin(); i < MAX_NUM_POINTLIGHTS, i < this->lights->size(); i++, it++) {
		Locator::getD3D()->mapConstantBuffer(&cLightBuffer[i], &(*it), sizeof(Light));
	}

	size_t size = this->lights->size() < MAX_NUM_POINTLIGHTS ? this->lights->size() : MAX_NUM_POINTLIGHTS;
	Locator::getD3D()->setConstantBuffer(*this->cLightBuffer.data(), SHADER::PIXEL, 0, size);
}

void RenderInputOrganizer::addGraphics(GraphicsComponent * graphics)
{
	this->graphics.push_back(graphics);
}
