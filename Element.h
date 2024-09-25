#pragma once
#include <SDL.h>

class ChunkWorker;

class Element {
public:
    virtual ~Element() = default;
    virtual void update(ChunkWorker& grid, int x, int y) = 0;
    virtual SDL_Color getColor() const = 0;
	bool oddUpdate;
	bool isSolid;
	int density;
	bool isFlammable = false;
protected:
	int velocityY = 0;
	int velocityX = 0;
	int colorShift;
	int friction;
	bool isMoving;
};
