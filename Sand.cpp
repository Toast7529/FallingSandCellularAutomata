#include "sand.h"
#include <SDL.h>
#include "ChunkWorker.h"
#include <random>
Sand::Sand() {
    isSolid = true;
    density = 1400;
    colorShift = rand() % 20;
}
SDL_Color Sand::getColor() const {
    return { static_cast<Uint8>(240 - colorShift), static_cast<Uint8>(230 - colorShift), 0, 255 }; // Gold color for sand
}

void Sand::update(ChunkWorker& grid, int x, int y) {
    velocityY++;
    int newY = y + velocityY;
    if (isFree(grid,x,newY)) {
        grid.swapElements(x, y, x, newY);
    }
    else if (isFree(grid, x - 1, newY)) {
        grid.swapElements(x, y, x - 1, newY);
    } else if (isFree(grid, x + 1, newY)) {
        grid.swapElements(x, y, x + 1, newY);
    }
    else {
        velocityY = 0;
        velocityX = 0;
    }
}