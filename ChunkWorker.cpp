#include "ChunkWorker.h"
#include <iostream>
ChunkWorker::ChunkWorker(Grid& grid, Chunk* chunk) : grid(grid), chunk(chunk) {};

ChunkWorker::~ChunkWorker() {};

void ChunkWorker::updateChunk(bool oddUpdate) {
    //if (chunk->minY < chunk->maxY && chunk->minX < chunk->maxX)
    for (int y = 0; y < chunk->mheight; y++) {
        for (int x = 0; x < chunk->mwidth; x++) {
            int globalY = y + (chunk->mheight * chunk->my);
            int globalX = x + (chunk->mwidth * chunk->mx);
            if (Element* element = chunk->getElement(globalX, globalY)) {
               if (element->oddUpdate != oddUpdate) {
                    element->update(*this, globalX, globalY);
                    element->oddUpdate = oddUpdate;
               }
            }
        }
    }
}

Element* ChunkWorker::getElement(int x, int y) {
    if (chunk->isValidPosition(x, y))  return chunk->getElement(x, y);
    return grid.getElement(x, y);
}

void ChunkWorker::setElement(int x, int y, std::unique_ptr<Element> element) {
    if (chunk->isValidPosition(x, y)) {
        chunk->setElement(x, y, std::move(element));
    }
    else {
        grid.setElement(x, y, std::move(element));
    }
}

bool ChunkWorker::canSwap(int x, int y) {
    return (chunk->isValidPosition(x, y) || grid.isValidPosition(x, y)) && getElement(x, y) == nullptr;
}


void ChunkWorker::swapElements(int x0, int y0, int x1, int y1) {
    int offSetX = 0, offSetY = 0;
    int globalChunkX = chunk->mx * chunk->mwidth;
    int globalChunkY = chunk->my * chunk->mheight;

    if (x0 == globalChunkX) offSetX = -1;
    if (x0 == globalChunkX + chunk->mwidth - 1) offSetX = 1;
    if (y0 == globalChunkY) offSetY = -1;
    if (y0 == globalChunkY + chunk->mheight - 1) offSetY = 1;

    if (offSetX != 0 || offSetY != 0) grid.keepAlive(x0 + offSetX, y0 + offSetY);

    if (chunk->isValidPosition(x0, y0) && chunk->isValidPosition(x1, y1)) {
        chunk->swapElements(x0, y0, x1, y1);
    } else {
        grid.swapElements(x0, y0, x1, y1);
    }
}

bool ChunkWorker::isValidPosition(int x, int y) const {
    return chunk->isValidPosition(x, y) || grid.isValidPosition(x, y);
}

void ChunkWorker::removeElement(int x, int y) {
    if (chunk->isValidPosition(x, y)) {
        chunk->removeElement(x, y);
    }
    else {
        grid.removeElement(x, y);
    }
}
