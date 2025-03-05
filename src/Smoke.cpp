#include "Smoke.h"

Smoke::Smoke() {
    dispersion = 50;
    isSolid = false;
    density = 0;
    colorShift = rand() % 100;
}
SDL_Color Smoke::getColor() const {
    return { static_cast<Uint8>(colorShift), static_cast<Uint8>(colorShift), static_cast<Uint8>(colorShift), 155 }; // Gold color for sand
}
void Smoke::update(ChunkWorker& grid, int x, int y) {
    int xDir = rand() % 2 ? 1 : -1; // random direction for left or right
    isMoving = true;
    if (grid.isValidPosition(x, y - 1) && grid.getElement(x, y - 1) == nullptr) {
        grid.swapElements(x, y, x, y - 1);
        velocityY--;
    }
    else if (grid.isValidPosition(x + xDir, y) && grid.getElement(x + xDir, y) == nullptr) {
        int newX = x + xDir;
        for (int i = 2; i < dispersion; i++) {
            if (grid.isValidPosition(x + (xDir * i), y) && grid.getElement(x + (xDir * i), y) == nullptr) {
                newX = x + (xDir * i);
            }
            else {
                break;
            }
        }
        grid.swapElements(x, y, newX, y);
    }
    else {
        isMoving = false;
        velocityY = 0;
    }
    
}