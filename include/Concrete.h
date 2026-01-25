#pragma once
#include "Solid.h"

class Concrete : public Solid {
public:
	Concrete();
	SDL_Color getColor() const override;
	void update(ChunkWorker& grid, int x, int y) override;

};

