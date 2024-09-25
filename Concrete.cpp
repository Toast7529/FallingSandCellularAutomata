#include "Concrete.h"
#include <SDL.h>
#include "ChunkWorker.h"
#include <random>
Concrete::Concrete() {
    colorShift = rand() % 20;
}
SDL_Color Concrete::getColor() const {
    Uint8 color = 120 - colorShift;
    return { color, color, color, 255 }; // Grey color 
}

void Concrete::update(ChunkWorker& grid, int x, int y) {
    std::srand(std::time(nullptr));
}