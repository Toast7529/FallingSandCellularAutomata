#pragma once
#include "Grid.h"
#include "Renderer.h"
#include "ElementType.h"
class ToolHandler
{
public:
	ToolHandler();

	void handleEvent(const SDL_Event& event);
	void applyTool(Grid& grid, int mouseX, int mouseY);
	void drawBrushOutline(Renderer& renderer, int mouseX, int mouseY) const;
	void lineBrush(Grid& grid, int mouseX, int mouseY);
	
private:
	int brushSize;
	bool erasing;
	int lastY, lastX;
	std::unique_ptr<Element> createElement() const;
	ElementType currentElement;
};

