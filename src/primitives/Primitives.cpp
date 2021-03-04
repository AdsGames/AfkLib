#include <SDL2/SDL2_gfxPrimitives.h>

#include "primitives/Primitives.h"
#include "services/Locator.h"

void Primitives::rect(const int x,
                      const int y,
                      const int w,
                      const int h,
                      SDL_Color colour) {
  SDL_Renderer* renderer = Locator::getDisplay().getRenderer();

  SDL_Rect bounds = {x, y, w, h};
  SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
  SDL_RenderDrawRect(renderer, &bounds);
}

void Primitives::rectfill(const int x,
                          const int y,
                          const int w,
                          const int h,
                          SDL_Color colour) {
  SDL_Renderer* renderer = Locator::getDisplay().getRenderer();

  SDL_Rect bounds = {x, y, w, h};
  SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
  SDL_RenderFillRect(renderer, &bounds);
}

void Primitives::circle(const int cx,
                        const int cy,
                        const int r,
                        SDL_Color colour) {
  SDL_Renderer* renderer = Locator::getDisplay().getRenderer();
  circleColor(renderer, cx, cy, r, Color::colorToInt(colour));
}