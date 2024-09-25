#include "Renderer.h"
#include <SDL.h>

Renderer::Renderer(int width, int height) {
	SDL_Init(SDL_INIT_VIDEO);
	window = SDL_CreateWindow("Falling Sand Simulation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	screenBuffer = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width/2, height/2);
	SDL_RenderSetScale(renderer, 2, 2);
}

Renderer::~Renderer() {
	SDL_DestroyTexture(screenBuffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

void Renderer::clear() {
	SDL_SetRenderTarget(renderer, screenBuffer);
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);
}

void Renderer::present() {
	SDL_SetRenderTarget(renderer, nullptr);
	SDL_RenderCopy(renderer, screenBuffer, nullptr, nullptr);
	SDL_RenderPresent(renderer);
}

void Renderer::renderGrid(Grid& grid) {
	grid.render(renderer);
}

//void Renderer::drawBrushOutline(int x, int y, int size) {
//	x /= 2;
//	y /= 2;
//	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color for outline
//	SDL_Rect rect = { x - size / 2, y - size / 2, size, size };
//	SDL_RenderDrawRect(renderer, &rect);
//}

void Renderer::drawBrushOutline(int mouseX, int mouseY, int size) {
    mouseY /= 2;
    mouseX /= 2;
    int x = size/2;
    int y = 0;
    int decisionOver2 = 1 - x; // Decision variable
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // White color for outline
    while (y <= x) {
        // Draw the eight points of the circle at the current octant
        SDL_RenderDrawPoint(renderer, mouseX + x, mouseY + y); // right
        SDL_RenderDrawPoint(renderer, mouseX + y, mouseY - x); // Bottom-right
        SDL_RenderDrawPoint(renderer, mouseX - x, mouseY + y); // left
        SDL_RenderDrawPoint(renderer, mouseX - y, mouseY - x); // Bottom-left
        SDL_RenderDrawPoint(renderer, mouseX + x, mouseY - y); // bottom
        SDL_RenderDrawPoint(renderer, mouseX - x, mouseY - y); // top
        SDL_RenderDrawPoint(renderer, mouseX + y, mouseY + x); // top-right
        SDL_RenderDrawPoint(renderer, mouseX - y, mouseY + x); // top-left

        y++;

        // Update the decision variable and x-coordinate
        if (decisionOver2 <= 0) {
            decisionOver2 += 2 * y + 1;
        }
        else {
            x--;
            decisionOver2 += 2 * (y - x) + 1;
        }
    }
}