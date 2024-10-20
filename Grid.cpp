#include "Grid.h"
#include "Element.h"
#include "Chunk.h"
#include "chunkWorker.h"
#include <vector>
#include <iostream>
#include <utility>
#include <memory>
#include <mutex>

Grid::Grid(int width, int height) : width(width), height(height), chunkWidth(width/10), chunkHeight(height/10) {
    std::cout << "Chunk height: " << chunkHeight << std::endl;
    std::cout << "Chunk width: " << chunkWidth << std::endl;

    grid.resize(height);
    for (int i = 0; i < height; ++i) {
        grid[i].resize(width);
    }
}

Grid::~Grid() = default;

bool Grid::isValidPosition(int x, int y) const {
    return x >= 0 && x < width && y >= 0 && y < height;
}

void Grid::swapElements(int x0, int y0, int x1, int y1) {
    if (isValidPosition(x0, y0) && isValidPosition(x1, y1)) {
        Chunk* chunk0 = getChunk(x0, y0);
        Chunk* chunk1 = getChunk(x1, y1);
        chunk0->keepAlive(x0, y0);
        chunk1->keepAlive(x1, y1);


        std::unique_ptr<Element> temp = std::move(chunk0->removeElement(x0, y0));
        chunk0->setElement(x0, y0, std::move(chunk1->removeElement(x1, y1)));
        chunk1->setElement(x1, y1, std::move(temp));

    }
}

bool Grid::canSwap(int x, int y) {
    return isValidPosition(x, y) && getElement(x, y) == nullptr;
}

void Grid::keepAlive(int x, int y) {
    getChunk(x, y)->keepAlive(x, y);
}

Element* Grid::getElement(int x, int y) {
    return getChunk(x,y)->getElement(x,y);
}

void Grid::clearGrid() {
    for (auto& row : grid) {
        for (auto& element : row) {
            element.reset();
        }
    }
    // NEEDS LOGIC TO DELETE THE CHUNKS TOO
}

void Grid::setElement(int x, int y, std::unique_ptr<Element> element) {
    //std::cout << "GridX: " << x << "Y: " << y << std::endl;
    std::pair<int, int> chunkcoords = getChunkLocation(x,y);
    //std::cout << "Placing in chunk: " << chunkcoords.first << " " << chunkcoords.second << std::endl;

    if (isValidPosition(x, y) && getElement(x,y) == nullptr) {
        //std::cout << "X: " << x << " Y: " << y << std::endl;
        Chunk* chunk = getChunk(x, y);
        chunk->setElement(x, y, std::move(element));
    }
}

void Grid::removeElement(int x, int y) {
    if (isValidPosition(x, y)) {
        getChunk(x, y)->removeElement(x, y);
    }
}

void Grid::update() {
    removeEmptyChunks();

    std::mutex mutex;
    std::condition_variable cond;
    int chunkSize = chunks.size();

    for (int i = 0; i < chunkSize; i++) {
        ChunkWorker(*this, chunks[i]).updateChunk(oddUpdate);
    }

    for (Chunk* chunk : chunks) {
        chunk->UpdateRect();
    }
    oddUpdate = !oddUpdate;
}


void Grid::render(SDL_Renderer* renderer) const {
    for (Chunk* chunk : chunks) {
        for (int y = 0; y < chunk->mheight; ++y) {
            for (int x = 0; x < chunk->mwidth; ++x) {
                if (chunk->getElement(x + (chunk->mwidth * chunk->mx), y + (chunk->mheight * chunk->my))) {
                    SDL_Color color = chunk->getElement(x + (chunk->mwidth * chunk->mx), y + (chunk->mheight * chunk->my))->getColor();
                    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
                    SDL_RenderDrawPoint(renderer, x + (chunk->mwidth * chunk->mx), y + (chunk->mheight * chunk->my));
                    //std::cout << x + (chunk->mwidth * chunk->mx) << std::endl;
                }
            }
        }
        //SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Red color

        //// Outline chunk
        //SDL_Rect rect;
        //rect.x = chunk->mx * chunk->mwidth;
        //rect.y = chunk->my * chunk->mheight;
        //rect.w = chunk->mwidth;
        //rect.h = chunk->mheight;

        //SDL_RenderDrawRect(renderer, &rect);

        //SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255); // Green color for dirty rectangles
        //int minX = chunk->minX;
        //int maxX = chunk->maxX;
        //int minY = chunk->minY;
        //int maxY = chunk->maxY;

        //if (minX <= maxX && minY <= maxY) {
        //    SDL_Rect dirtyRect;
        //    dirtyRect.x = chunk->mx * chunk->mwidth + minX;
        //    dirtyRect.y = chunk->my * chunk->mheight + minY;
        //    dirtyRect.w = maxX - minX + 1;
        //    dirtyRect.h = maxY - minY + 1;

        //    SDL_RenderDrawRect(renderer, &dirtyRect);
        //}
    }

    
}

// Chunks:

Chunk* Grid::getChunk(int x, int y) {
    std::pair<int, int> location = getChunkLocation(x, y);
    Chunk* chunk = getChunkDirect(location);
    return chunk ? chunk : createChunk(location);
}

std::pair<int,int> Grid::getChunkLocation(int x, int y) const {
    //std::cout << "Chunk pos: x: " << floor(float(x) / chunkWidth) << " Y: " << floor(float(y) / chunkHeight) << std::endl;
    return { floor(float(x) / chunkWidth), floor(float(y) / chunkHeight) };
}

Chunk* Grid::getChunkDirect(std::pair<int, int> location) const {
    auto itr = chunkLookup.find(location);
    return  itr != chunkLookup.end() ? itr->second : nullptr;
}

Chunk* Grid::createChunk(std::pair<int, int> location) {
    int x = location.first, y = location.second;
    //if (x < -10 || x > 10 || y < -10 || y > 10) return nullptr; // idk waht this does
    
    Chunk* chunk = new Chunk(chunkWidth, chunkHeight, x, y);
    chunkLookup.insert({ location, chunk });
    chunks.push_back(chunk);
    return chunk;
}


void Grid::removeEmptyChunks() {
    for (int i = 0; i < chunks.size(); i++) {
        Chunk* chunk = chunks.at(i);
        if (chunk->totalElements == 0) {
            chunkLookup.erase(getChunkLocation(chunk->mx * chunkWidth, chunk->my * chunkHeight));
            chunks[i] = chunks.back();
            chunks.pop_back();
            i--;
            chunk->clearChunk();
            delete chunk;
        }
    }
}
