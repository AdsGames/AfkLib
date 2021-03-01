#include <SDL2/SDL2_gfxPrimitives.h>

#include "primitives/Primitives.h"

void Primitives::rect(const float x1,
                      const float y1,
                      const float x2,
                      const float y2,
                      SDL_Color color,
                      const float thickness) {
  SDL_Rect fillRect = {x1, y1, x2, y2};
  SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, color.a);
  SDL_RenderFillRect(gRenderer, &fillRect);
}

void Primitives::rectfill(const float x1,
                          const float y1,
                          const float x2,
                          const float y2,
                          SDL_Color color) {
  SDL_Rect fillRect = {x1, y1, x2, y2};
  SDL_SetRenderDrawColor(gRenderer, color.r, color.g, color.b, color.a);
  SDL_RenderDrawRect(gRenderer, &fillRect);
}

void Primitives::circle(const float cx,
                        const float cy,
                        const float r,
                        SDL_Color color,
                        const float thickness) {
    al_draw_circle(cx, cy, r, color, thickness);
}