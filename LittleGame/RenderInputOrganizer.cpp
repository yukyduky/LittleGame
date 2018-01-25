#include "RenderInputOrganizer.h"
#include "BlockComponent.h"
#include "D3D.h"


void RenderInputOrganizer::drawGraphics(GraphicsComponent *& graphics)
{
	D3D::setVertexBuffer(0, 1, &graphics->GETvertexBuffer(), &graphics->GETstride(), &graphics->GEToffset());
	D3D::setIndexBuffer(graphics->GETindexBuffer(), DXGI_FORMAT_R32_UINT, 0);

	D3D::setPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	D3D::drawIndexed(graphics->GETnumIndices(), 0, 0);
}

void RenderInputOrganizer::init()
{
	this->defRenderer.init();
}

void RenderInputOrganizer::render()
{
	/*this->defRenderer.firstPass();

	for (auto &i : this->graphics) {
		this->drawGraphics(i);
	}*/

	this->defRenderer.secondPass();
}

void RenderInputOrganizer::addGraphics(GraphicsComponent * graphics)
{
	this->graphics.push_back(graphics);
}
