#pragma once
#include <SDL.h>
#include "grid.h"
class Renderer
{
public:
	Renderer(int width, int height);
	~Renderer();

	void renderGrid(Grid& grid);
	void clear();
	void present();
	void drawBrushOutline(int x, int y, int size);


private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	SDL_Texture* screenBuffer;	// offscreen
};

