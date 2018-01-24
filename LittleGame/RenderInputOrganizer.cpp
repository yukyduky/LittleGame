#include "RenderInputOrganizer.h"


RenderInputOrganizer::RenderInputOrganizer()
{
	this->defRenderer.init();
}

void RenderInputOrganizer::render()
{
	this->defRenderer.firstPass();



	this->defRenderer.secondPass();
}

void RenderInputOrganizer::addGraphics(GraphicsComponent * graphic)
{
}

void RenderInputOrganizer::renderBlock(BlockComponent * block)
{
	ID3D11Buffer* gVertexBuffer = nullptr;


}
