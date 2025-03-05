#pragma once
#include "Gas.h"

class Smoke : public Gas {
public:
	Smoke();
	SDL_Color getColor() const override;
	void update(ChunkWorker& grid, int x, int y) override;
};



