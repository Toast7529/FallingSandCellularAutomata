#pragma once
#include "Element.h"
#include "ChunkWorker.h"
class Fire : public Element
{
public:
	Fire();
	SDL_Color getColor() const override;
	bool checkNeighbor(ChunkWorker& grid, int x, int y) const;
	void setFire(ChunkWorker& grid, int x, int y);
	void update(ChunkWorker& grid, int x, int y) override;
private:
	int lifeTime;
};

