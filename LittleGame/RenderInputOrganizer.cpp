#include "RenderInputOrganizer.h"
#include "GraphicsComponent.h"
#include "Locator.h"


void RenderInputOrganizer::drawGraphics(GraphicsComponent *& graphics, Camera& camera)
{
	// Skapa matrix, fixa ID3Dbuffer, se
	DirectX::XMMATRIX wvpTemp;

	//Locator::getConstantBuffer()->GETcalcMatrixData(/*graphics.getWorld()*/);

	Locator::getConstantBuffer()->packageMatrices();

	Locator::getConstantBuffer()->editConstantBuffers(
		&this->constantBuffer,
		&this->packagedMatrixData,
		sizeof(this->packagedMatrixData)
	);

	Locator::getD3D()->setVertexBuffer(&graphics->GETvertexBuffer(), graphics->GETstride(), graphics->GEToffset());
	Locator::getD3D()->setIndexBuffer(graphics->GETindexBuffer(), 0);

	Locator::getD3D()->GETgDevCon()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Locator::getD3D()->GETgDevCon()->DrawIndexed(graphics->GETnumIndices(), 0, 0);
}

void RenderInputOrganizer::initialize(Camera& camera) {
	this->rawMatrixData.view = &camera.GETviewMatrix();
	this->rawMatrixData.proj = &camera.GETprojMatrix();
}

void RenderInputOrganizer::packageMatrices() {
	DirectX::XMStoreFloat4x4(&this->packagedMatrixData.world, *this->rawMatrixData.world);
	DirectX::XMStoreFloat4x4(&packagedMatrixData.worldViewProj, *this->rawMatrixData.view);
}

void RenderInputOrganizer::render()
{
	for (auto &i : this->graphics) {
		this->drawGraphics(i);
	}
}

void RenderInputOrganizer::addGraphics(GraphicsComponent * graphics)
{
	this->graphics.push_back(graphics);
}
