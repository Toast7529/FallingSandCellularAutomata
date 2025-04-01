#pragma once
#include "Element.h"
#include "Chunk.h"
#include <SDL.h>
#include <vector>
#include <memory>
#include <utility>
#include <unordered_map>
#include "tbb/concurrent_hash_map.h"
#include "ThreadPool.h"
struct pair_hash {
    size_t hash(const std::pair<int, int>& key) const {
        return (std::hash<int>()(key.first) * 0x1f1f1f1f)
            ^ std::hash<int>()(key.second);
    }

    bool equal(const std::pair<int,int>& a, const std::pair<int,int>& b) const {
        return a.first == b.first && a.second == b.second;
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
    //std::unordered_map<std::pair<int, int>, Chunk*, pair_hash> chunkLookup;

    ThreadPool* Task = nullptr;
    std::mutex chunkMutex;
    tbb::concurrent_hash_map<std::pair<int, int>, Chunk*, pair_hash> chunkLookup;

};


