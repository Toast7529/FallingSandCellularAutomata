#include "Chunk.h"
#include "Element.h"
#include <vector>
#include <iostream>
#include <utility>
#include <algorithm>

Chunk::Chunk(int width, int height, int x, int y) : mwidth(width), mheight(height), mx(x), my(y) {
    //std::cout << "Chunk created at x:" << x << " Y: " << y << std::endl;
    //std::cout << mwidth << " H: " << mheight << std::endl;
    chunk.resize(mheight);
    for (int i = 0; i < mheight; ++i) {
        chunk[i].resize(mwidth);
    }
}

Chunk::~Chunk() = default;

bool Chunk::isValidPosition(int x, int y) const {
    x = getX(x);
    y = getY(y);
    return x >= 0 && x < mwidth && y >= 0 && y < mheight;
}

void Chunk::swapElements(int x0, int y0, int x1, int y1) {
    if (isValidPosition(x0, y0) && isValidPosition(x1, y1)) {
        std::swap(chunk[getY(y0)][getX(x0)], chunk[getY(y1)][getX(x1)]);
        keepAlive(x0, y0);
        keepAlive(x1, y1);
    }
}

bool Chunk::canSwap(int x, int y) const {
    x = getX(x);
    y = getY(y);
    return isValidPosition(x, y) && getElement(x, y) == nullptr;
}

Element* Chunk::getElement(int x, int y) const {
    x = getX(x);
    y = getY(y);
    return chunk[y][x].get();
}

void Chunk::clearChunk() {
    for (auto& row : chunk) {
        for (auto& element : row) {
            element.reset();
        }
    }
    totalElements = 0;
}

void Chunk::setElement(int x, int y, std::unique_ptr<Element> element) {   
    if (chunk[getY(y)][getX(x)] == nullptr && element != nullptr) totalElements++;
    chunk[getY(y)][getX(x)] = std::move(element);
    keepAlive(x, y);
}

std::unique_ptr<Element> Chunk::removeElement(int x, int y) {
    if (!isValidPosition(x, y)) return nullptr;

    std::unique_ptr<Element> temp = std::move(chunk[getY(y)][getX(x)]);
    if (temp != nullptr) {
        chunk[getY(y)][getX(x)] = nullptr;
        totalElements--;
    }
    keepAlive(x, y);
    return temp;
}

void Chunk::keepAlive(int x, int y) {
    x = getX(x);
    y = getY(y);

    minXw = std::clamp(std::min(x - 2, minXw), 0, mwidth);
    minYw = std::clamp(std::min(y - 2, minYw), 0, mheight);
    maxXw = std::clamp(std::max(x + 2, maxXw), 0, mwidth);
    maxYw = std::clamp(std::max(y + 2, maxYw), 0, mheight);
}

void Chunk::UpdateRect() {
    minX = minXw;  minXw = mwidth;
    minY = minYw;  minYw = mheight;
    maxX = maxXw;  maxXw = -1;
    maxY = maxYw;  maxYw = -1;
    
}


// convert gloal coords to local coords

int Chunk::getY(int y) const {
    return y - (mheight * my);
}

int Chunk::getX(int x) const {
    return x - (mwidth * mx);
}

