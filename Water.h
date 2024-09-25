#pragma once
#include "Liquid.h"

class Water : public Liquid {
public:
	Water();
	SDL_Color getColor() const override;
	void update(ChunkWorker& grid, int x, int y) override;
};

