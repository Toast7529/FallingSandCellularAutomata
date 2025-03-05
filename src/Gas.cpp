#include "Gas.h"
void Gas::move(ChunkWorker& grid, int x, int y, int dir) {
    int newX = x + dir;
    for (int i = 1; i < dispersion; i++) {
        if (grid.canSwap(x + (dir * i), y)) {
            newX = x + (dir * i);
        }
        else {
            break;
        }
    }
    grid.swapElements(x, y, newX, y);

}