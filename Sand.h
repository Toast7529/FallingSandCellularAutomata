#pragma once
#include "Solid.h"

class Sand : public Solid {
public:
	Sand();
	~Sand() override = default;
	void move(ChunkWorker& grid, int x, int y);
	SDL_Color getColor() const override;
	void update(ChunkWorker& grid, int x, int y) override;

};

