#include "RenderInputOrganizer.h"
#include "GraphicsComponent.h"
#include "Locator.h"


void RenderInputOrganizer::packageMatrices() {
	DirectX::XMStoreFloat4x4(
		&this->packagedMatrixData.world,
		*this->rawMatrixData.world
	);

	this->rawMatrixData.worldViewProj = (*this->rawMatrixData.world) * (*this->rawMatrixData.view) * (*this->rawMatrixData.proj);
	this->rawMatrixData.worldViewProj = DirectX::XMMatrixTranspose(this->rawMatrixData.worldViewProj);
	DirectX::XMStoreFloat4x4(
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
	Locator::getD3D()->setConstantBuffer(this->cMatrixBuffer, SHADER::VERTEX, 0);

	Locator::getD3D()->setVertexBuffer(&graphics->GETvertexBuffer(), graphics->GETstride(), graphics->GEToffset());
	Locator::getD3D()->setIndexBuffer(graphics->GETindexBuffer(), 0);

	Locator::getD3D()->GETgDevCon()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Locator::getD3D()->GETgDevCon()->DrawIndexed(graphics->GETnumIndices(), 0, 0);
}

void RenderInputOrganizer::initialize(Camera& camera, std::list<Light>*& lights) {
	this->lights = lights;

	this->rawMatrixData.view = &camera.GETviewMatrix();
	this->rawMatrixData.proj = &camera.GETprojMatrix();

	Locator::getD3D()->createConstantBuffer(
		&this->cMatrixBuffer,
		sizeof(this->packagedMatrixData)
	);

	Locator::getD3D()->createConstantBuffer(
		&this->cLightBuffer,
		sizeof(Light)
	);
}

void RenderInputOrganizer::render()
{
	for (auto &i : this->graphics) {
		this->drawGraphics(i);
	}
}

void RenderInputOrganizer::injectResourcesIntoSecondPass()
{

}

void RenderInputOrganizer::addGraphics(GraphicsComponent * graphics)
{
	this->graphics.push_back(graphics);
}
