#include "Fire.h"
#include <SDL.h>
#include "ChunkWorker.h"
#include "Smoke.h"
#include <random>
Fire::Fire() : lifeTime(120) {
    isSolid = false;
}
SDL_Color Fire::getColor() const {
    unsigned char r = rand() % 56 + 170;
    unsigned char g = rand() % 56 + 20;
    unsigned char a = lifeTime / 150 * 255;
    return {r , g, 0, a};
}

bool Fire::checkNeighbor(ChunkWorker& grid, int x, int y) const {
    return grid.isValidPosition(x,y) && grid.getElement(x, y) != nullptr && grid.getElement(x, y)->isFlammable;
}
void Fire::setFire(ChunkWorker& grid, int x, int y) {
    if (checkNeighbor(grid, x, y)) {
        grid.removeElement(x, y);
        grid.setElement(x, y, std::make_unique<Fire>());
    }
}

void Fire::update(ChunkWorker& grid, int x, int y) {
    int xDir = rand() % 2 ? 1 : -1; // random direction for left or right
    if (lifeTime < 0) {
        grid.removeElement(x, y);   // remove fire
        // have a chance of replacing with smoke 66%
        if (!(rand() % 3)) {
            grid.removeElement(x, y);
            grid.setElement(x, y, std::make_unique<Smoke>());
        }

        for (int i = -3; i < 4; i++) {
            for (int j = -3; j < 4; j++) {
                setFire(grid, x + i, y + j);
            }
        }

    }
    else {
        lifeTime -= rand() % 20;
    }
    


}