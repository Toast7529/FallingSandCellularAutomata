#pragma once
#include "Element.h"
#include "Chunk.h"
#include <SDL.h>
#include <vector>
#include <memory>
#include <utility>
#include <unordered_map>
struct pair_hash {
    template<typename T1, typename T2>
    size_t operator() (const std::pair<T1, T2>& pair) const {
        return (std::hash<T1>()(pair.first) * 0x1f1f1f1f)
            ^ std::hash<T2>()(pair.second);
    }
};

class Grid {
public:
    Grid(int width, int height);
    ~Grid();
    bool oddUpdate = false;
    void clearGrid();
    void setElement(int x, int y, std::unique_ptr<Element> element);
    void update();
    void render(SDL_Renderer* renderer) const;

    Element* getElement(int x, int y);
    void removeElement(int x, int y);
    bool isValidPosition(int x, int y) const;
    void swapElements(int x0, int y0, int x1, int y1);
    bool canSwap(int x, int y);

    // Chunks:
    Chunk* getChunk(int x, int y);
    std::pair<int, int> getChunkLocation(int x, int y) const;
    Chunk* getChunkDirect(std::pair<int, int> location) const;
    Chunk* createChunk(std::pair<int, int> location);
    void removeEmptyChunks();
    void keepAlive(int x, int y);
private:
    int width, height, chunkWidth, chunkHeight;
    std::vector<std::vector<std::unique_ptr<Element>>> grid;

    // Store chunks
    std::vector<Chunk*> chunks;
    std::unordered_map<std::pair<int, int>, Chunk*, pair_hash> chunkLookup;
};


