#pragma once
#include "Solid.h"

class Wood : public Solid {
public:
	Wood();
	SDL_Color getColor() const override;
	void update(ChunkWorker& grid, int x, int y) override;

};
