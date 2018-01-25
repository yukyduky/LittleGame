#pragma once
#ifndef RENDERINPUTORGANIZER_H
#define RENDERINPUTORGANIZER_H

#include "DeferredRendering.h"
#include <vector>

struct vColor;
struct Vertex;

class GraphicsComponent;
class BlockComponent;

class RenderInputOrganizer
{
private:
	DeferredRendering defRenderer;
	std::vector<GraphicsComponent*> graphics;
	
	void drawGraphics(GraphicsComponent*& graphics);
public:
	void init();
	void render();
	void addGraphics(GraphicsComponent* graphics);
};

#endif // !RENDERINPUTORGANIZER_H
