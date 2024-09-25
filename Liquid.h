#pragma once
#include "Element.h"
#include "ChunkWorker.h"
class Liquid : public Element
{
public:
	void move(ChunkWorker& grid, int x, int y, int dir);
protected:
	int dispersion;

};

