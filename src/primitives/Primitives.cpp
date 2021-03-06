#include <SDL2/SDL2_gfxPrimitives.h>

#include "primitives/Primitives.h"
#include "services/Services.h"

namespace afk::primitives {

void rect(const int x,
          const int y,
          const int w,
          const int h,
          SDL_Color colour) {
  SDL_Renderer* renderer = Services::getDisplayService().getRenderer();

  SDL_Rect bounds = {x, y, w, h};
  SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
  SDL_RenderDrawRect(renderer, &bounds);
}

void rectfill(const int x,
              const int y,
              const int w,
              const int h,
              SDL_Color colour) {
  SDL_Renderer* renderer = Services::getDisplayService().getRenderer();

  SDL_Rect bounds = {x, y, w, h};
  SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
  SDL_RenderFillRect(renderer, &bounds);
}

void circle(const int cx, const int cy, const int r, SDL_Color colour) {
  SDL_Renderer* renderer = Services::getDisplayService().getRenderer();
  circleColor(renderer, cx, cy, r, Color::colorToInt(colour));
}

}  // namespace afk::primitives