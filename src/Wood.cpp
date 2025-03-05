#include "Wood.h"
#include "ChunkWorker.h"
#include <random>
Wood::Wood() {
    isFlammable = true;
}
SDL_Color Wood::getColor() const {
    return { 70, 35, 0, 255 }; // Grey color 
}

void Wood::update(ChunkWorker& grid, int x, int y) {
    //if (grid.canSwap(x, y + 1)) grid.swapElements(x, y, x, y + 1);
    //else 
        if (grid.canSwap(x - 1, y+1)) grid.swapElements(x, y, x - 1, y+1);
    else if (grid.canSwap(x + 1, y+1)) grid.swapElements(x, y, x + 1, y+1);
}