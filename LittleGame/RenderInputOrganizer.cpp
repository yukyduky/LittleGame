#include "RenderInputOrganizer.h"
#include "BlockComponent.h"
#include "D3D.h"


RenderInputOrganizer::RenderInputOrganizer()
{
	this->defRenderer.init();
}

void RenderInputOrganizer::render()
{
	this->defRenderer.firstPass();

	for (auto &i : this->graphics) {
		i->render(this);
	}

	this->defRenderer.secondPass();
}

void RenderInputOrganizer::render(BlockComponent * block)
{
	ID3D11Buffer* gVertexBuffer = nullptr;
	ID3D11Buffer* gIndexBuffer = nullptr;
	D3D::createVertexBuffer(block->GETVertexData().data(), &gVertexBuffer, sizeof(PrimitiveVertexData) * block->GETVertexData().size());
	D3D::createIndexBuffer(block->GETindices().data(), &gIndexBuffer, sizeof(DWORD) * block->GETindices().size());
	D3D::setIndexBuffer(gVertexBuffer, DXGI_FORMAT_R32_UINT, 0);

}

void RenderInputOrganizer::addGraphics(GraphicsComponent * graphic)
{
	this->graphics.push_back(graphic);
}
