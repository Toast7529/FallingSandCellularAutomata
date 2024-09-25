#pragma once
#include "Element.h"
#include <SDL.h>
#include <vector>
#include <memory>
#include <utility>

class Chunk {
public:
    Chunk(int width, int height, int x, int y);
    ~Chunk();



    void clearChunk();
    void setElement(int x, int y, std::unique_ptr<Element> element);


    Element* getElement(int x, int y) const;
    std::unique_ptr<Element> removeElement(int x, int y);
    bool isValidPosition(int x, int y) const;
    void swapElements(int x0, int y0, int x1, int y1);
    bool canSwap(int x, int y) const;

    int getY(int y) const;  // return localized coords
    int getX(int x) const;


    bool oddUpdate = true;
    int mx,my, mwidth, mheight;
    int totalElements = 0;

    int minX, minY, maxX, maxY; // dirt rectangle
    void keepAlive(int x, int y);
    void UpdateRect();
private:
    int minXw, minYw, maxXw, maxYw; // working dirt rectangle
    std::vector<std::vector<std::unique_ptr<Element>>> chunk;
};


