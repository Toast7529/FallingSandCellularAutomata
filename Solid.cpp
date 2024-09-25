#include "Solid.h"

bool Solid::isFree(ChunkWorker& grid, int x, int y) const {
    if (grid.isValidPosition(x, y)) {
        if (grid.getElement(x, y) == nullptr) {
            return true;
        }
        else if (!grid.getElement(x, y)->isSolid && grid.getElement(x, y)->density < density) {
            return true;
        }
    }
    return false;
}