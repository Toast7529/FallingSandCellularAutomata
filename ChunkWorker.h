#pragma once
#include "Grid.h"
#include "Element.h"
class ChunkWorker
{
protected:
	Grid& grid;
	Chunk* chunk;
public:
	ChunkWorker(Grid& grid, Chunk* chunk);
	~ChunkWorker();
	void updateChunk(bool oddUpdate);
	Element* getElement(int x, int y);
	void setElement(int x, int y, std::unique_ptr<Element> element);
	bool canSwap(int x, int y);
	void swapElements(int x0, int y0, int x1, int y1);
	bool isValidPosition(int x, int y) const;
	void removeElement(int x, int y);
};

