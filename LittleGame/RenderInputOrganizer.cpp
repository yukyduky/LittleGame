#include "RenderInputOrganizer.h"
#include "GraphicsComponent.h"
#include "Locator.h"


void RenderInputOrganizer::drawGraphics(GraphicsComponent *& graphics)
{
	Locator::getD3D()->setVertexBuffer(&graphics->GETvertexBuffer(), &graphics->GETstride(), &graphics->GEToffset());
	Locator::getD3D()->setIndexBuffer(graphics->GETindexBuffer(), 0);

	Locator::getD3D()->GETgDevCon()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	Locator::getD3D()->GETgDevCon()->DrawIndexed(graphics->GETnumIndices(), 0, 0);
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
