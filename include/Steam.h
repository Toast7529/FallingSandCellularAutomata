#pragma once
#include "Gas.h"

class Steam : public Gas {
public:
	Steam();
	SDL_Color getColor() const override;
	void update(ChunkWorker& grid, int x, int y) override;
};

