#pragma once
#ifndef RENDERINPUTORGANIZER_H
#define RENDERINPUTORGANIZER_H

#include <vector>

class GraphicsComponent;

class RenderInputOrganizer
{
private:
	std::vector<GraphicsComponent*> graphics;
	
	void drawGraphics(GraphicsComponent*& graphics);
public:
	void render();
	void addGraphics(GraphicsComponent* graphics);
};

#endif // !RENDERINPUTORGANIZER_H
