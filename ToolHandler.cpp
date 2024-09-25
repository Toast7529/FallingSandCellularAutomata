#include "ToolHandler.h"
#include "Sand.h"
#include "Water.h"
#include "Concrete.h"
#include "Steam.h"
#include "Fire.h"
#include "Smoke.h"
#include "Wood.h"
#include <algorithm>
ToolHandler::ToolHandler() : brushSize(10), erasing(false), lastX(-1), lastY(-1), currentElement(ElementType::Sand) {}

void ToolHandler::handleEvent(const SDL_Event& event) {
	int mouseX, mouseY;
	if (event.type == SDL_MOUSEWHEEL ) {
		if (event.wheel.y > 0 && brushSize <= 200) brushSize += 5;
		if (event.wheel.y < 0 && brushSize > 5) brushSize -= 5;
	}
    // select different elements
    if (event.type == SDL_KEYDOWN) {
        switch (event.key.keysym.sym) {
        case SDLK_1: currentElement = ElementType::Sand; break;
        case SDLK_2: currentElement = ElementType::Water; break;
        case SDLK_3: currentElement = ElementType::Concrete; break;
        case SDLK_4: currentElement = ElementType::Steam; break;
        case SDLK_5: currentElement = ElementType::Fire; break;
        case SDLK_6: currentElement = ElementType::Smoke; break;
        case SDLK_7: currentElement = ElementType::Wood; break;


            // Add more cases for other elements
        default: break;
        }
    }
	// handle erasing
	if (event.type == SDL_MOUSEBUTTONDOWN) {
		if (event.button.button == SDL_BUTTON_RIGHT) {
			erasing = true;

		}
	}
	if (event.type == SDL_MOUSEBUTTONUP) {
		if (event.button.button == SDL_BUTTON_RIGHT) {
			erasing = false;
            if (lastX != -1 && lastY != -1) {
                lastX = -1;
                lastY = -1;
            }

        }
        else if (event.button.button == SDL_BUTTON_LEFT) {
            lastX = -1;
            lastY = -1;
        }
	}
}

std::unique_ptr<Element> ToolHandler::createElement() const {
    switch (currentElement) {
    case ElementType::Sand: return std::make_unique<Sand>();
    case ElementType::Water: return std::make_unique<Water>();
    case ElementType::Concrete: return std::make_unique<Concrete>();
    case ElementType::Steam: return std::make_unique<Steam>();    
    case ElementType::Fire: return std::make_unique<Fire>();
    case ElementType::Smoke: return std::make_unique<Smoke>();
    case ElementType::Wood: return std::make_unique<Wood>();

        // Add more cases for other elements
    default: return nullptr;
    }
}

void ToolHandler::applyTool(Grid& grid, int mouseX, int mouseY) {

	int gridX = mouseX / 2;  // Convert to grid coordinates
	int gridY = mouseY / 2;  // Convert to grid coordinates
	
	for (int i = (-brushSize / 2); i < (brushSize / 2); i++) {
		for (int j = (-brushSize / 2); j < (brushSize / 2); j++) {
            if (i * i + j * j <= (brushSize / 2) * (brushSize / 2)) {
                if (erasing) {
                    grid.removeElement(gridX + i, gridY + j);
                }
                else {
                    grid.setElement(gridX + i, gridY + j, createElement());
                }
            }
			
		}
	}

}
void ToolHandler::drawBrushOutline(Renderer& renderer, int mouseX, int mouseY) const {
	renderer.drawBrushOutline(mouseX, mouseY, brushSize);
}

void ToolHandler::lineBrush(Grid& grid, int mouseX, int mouseY) {
    if (lastX == -1 || lastY == -1) {
        // Initialize starting point
        lastX = mouseX;
        lastY = mouseY;
    }


    int gridX1 = lastX;
    int gridY1 = lastY;
    int gridX2 = mouseX;
    int gridY2 = mouseY;

    int dx = std::abs(gridX2 - gridX1);
    int dy = std::abs(gridY2 - gridY1);
    int sx = (gridX1 < gridX2) ? 1 : -1;
    int sy = (gridY1 < gridY2) ? 1 : -1;
    int err = dx - dy;

    int longestSide = std::max(dx, dy);
    for (int i = 0; i < longestSide; i++) {
        applyTool(grid, gridX1, gridY1);
        if (gridX1 == gridX2 && gridY1 == gridY2) break;
        int e2 = 2 * err;
        if (e2 > -dy) {
            err -= dy;
            gridX1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            gridY1 += sy;
        }
    }

    // Update last position
    lastX = mouseX;
    lastY = mouseY;
}