#pragma once
#include "Element.h"
#include "ChunkWorker.h"
class Solid : public Element
{
public:
	bool isFree(ChunkWorker& grid, int x, int y) const;

};

