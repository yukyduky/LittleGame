#pragma once
#ifndef RENDERINPUTORGANIZER_H
#define RENDERINPUTORGANIZER_H

#include "DeferredRendering.h"
#include <vector>

struct vColor;
struct Vertex;

class GraphicsComponent;
class BlockComponent;

namespace OBJECTTYPE {
	enum TYPE { BLOCK, SIZE };
}

class RenderInputOrganizer
{
private:
	DeferredRendering defRenderer;
	std::vector<ID3D11Buffer*> gPrimitiveVertexBuffers;
	std::vector<GraphicsComponent*> graphics;
public:
	RenderInputOrganizer();
	void render();
	void addGraphics(GraphicsComponent* graphic);
	void renderBlock(BlockComponent* block);
};

#endif // !RENDERINPUTORGANIZER_H
