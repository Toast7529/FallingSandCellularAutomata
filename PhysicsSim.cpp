#include "renderer.h"
#include "grid.h"
#include "Concrete.h"
#include "water.h"
#include "ToolHandler.h"
#include <iostream>

int main(int argc, char* args[])
{
	const int SCREENHEIGHT = 400, SCREENWIDTH = 600;
	int mouseX = 0, mouseY = 0;
	Renderer renderer(SCREENWIDTH*2, SCREENHEIGHT*2);
	Grid grid(SCREENWIDTH, SCREENHEIGHT);
	ToolHandler toolHandler;


	bool isRunning = true;
	// Variables for FPS calculation
	Uint32 startTime = 0;
	int frameCount = 0;
	int fps = 0;
	startTime = SDL_GetTicks();


	SDL_Event event;

	while (isRunning) {
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				isRunning = false;
			}
			else {
				toolHandler.handleEvent(event);
				if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_SPACE) {
					grid.clearGrid();
				}
			}
			SDL_GetMouseState(&mouseX, &mouseY);
			if (SDL_GetMouseState(NULL, NULL)) {
				toolHandler.applyTool(grid, mouseX, mouseY);
				//toolHandler.lineBrush(grid, mouseX, mouseY);	// laggier but smoother brush

			}
			//else if (event.type == SDL_MOUSEBUTTONDOWN || event.type == SDL_MOUSEMOTION) {
			//	if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_LEFT)) {
			//		SDL_GetMouseState(&mouseX, &mouseY);
			//		int gridX = mouseX / 2;  // Convert to grid coordinates
			//		int gridY = mouseY / 2;  // Convert to grid coordinates
			//		for (int i = -10; i < 10; i++) {
			//			for (int j = -10; j < 10; j++) grid.setElement(gridX+i, gridY+j, new Sand());
			//		}
			//	}
			//	else if (SDL_GetMouseState(NULL, NULL) & SDL_BUTTON(SDL_BUTTON_RIGHT)) {
			//		SDL_GetMouseState(&mouseX, &mouseY);
			//		int gridX = mouseX / 2;  // Convert to grid coordinates
			//		int gridY = mouseY / 2;  // Convert to grid coordinates
			//		for (int i = -10; i < 10; i++) {
			//			for (int j = -10; j < 10; j++) grid.removeElement(gridX + i, gridY + j);
			//		}
			//	}
			//}

		}
		grid.update();

		renderer.clear();
		renderer.renderGrid(grid);
		toolHandler.drawBrushOutline(renderer, mouseX, mouseY);
		renderer.present();
		// FPS calculation
		frameCount++;
		if (SDL_GetTicks() - startTime > 1000) { // Every second
			fps = frameCount;
			frameCount = 0;
			startTime = SDL_GetTicks();
			std::cout << "FPS: " << fps << std::endl;
		}
		//SDL_Delay(16); // Simple frame rate control
	}

	return 0;
}
