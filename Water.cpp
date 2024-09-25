#include "Water.h"
#include <SDL.h>
#include "ChunkWorker.h"
#include <random>
Water::Water() {
    dispersion = rand() % 5 + 10;
    isSolid = false;
    density = 1000;
}
SDL_Color Water::getColor() const {
    return { 10, 60, 180 };
}


void Water::update(ChunkWorker& grid, int x, int y) {
    int xDir = rand() % 2 ? 1 : -1; // random direction for left or right
    // Check if water can move downwards based on current velocity

    int tempY = 0;
    for (int i = 1; i <= velocityY; i++) {
        if (grid.canSwap(x, y + i))  tempY = i;
        else break;
    }
    // If the water can fall at least one step, move it
    if (tempY > 0) {
        grid.swapElements(x, y, x, y + tempY);
        velocityY = std::min(velocityY + 1, 10);  // cap velocity at 10
    } else {
        velocityY = 0;  // Reset velocity if it can't fall further
    }

    // handle water when not falling
    if (velocityY == 0) {
        if (grid.canSwap(x, y + 1)) {
            grid.swapElements(x, y, x, y + 1);
            velocityY++;  // Start falling with initial velocityY at 1
        } else if (grid.canSwap(x + xDir, y)) {
            move(grid, x, y, xDir);
        } else if (grid.canSwap(x + 1, y)) {
            move(grid, x, y, 1);
        } else if (grid.canSwap(x - 1, y)) {
            move(grid, x, y, -1);
        }
    }
    
    

}