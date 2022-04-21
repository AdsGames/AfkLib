/**
 * @file Primitives.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of Primitives namespace helpers
 * @version 0.1
 * @date 2021-03-06
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <SDL2/SDL2_gfxPrimitives.h>

#include "primitives/Primitives.h"
#include "services/Services.h"

namespace afk::primitives {

// Draw a rectangle
void rect(const Sint32 x,
          const Sint32 y,
          const Sint32 w,
          const Sint32 h,
          color::Color colour) {
  SDL_Renderer* renderer = Services::getDisplayService().getRenderer();

  SDL_Rect bounds = {x, y, w, h};
  SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
  SDL_RenderDrawRect(renderer, &bounds);
}

// Draw a filled rectangle
void rectfill(const Sint32 x,
              const Sint32 y,
              const Sint32 w,
              const Sint32 h,
              color::Color colour) {
  SDL_Renderer* renderer = Services::getDisplayService().getRenderer();

  SDL_Rect bounds = {x, y, w, h};
  SDL_SetRenderDrawColor(renderer, colour.r, colour.g, colour.b, colour.a);
  SDL_RenderFillRect(renderer, &bounds);
}

// Draw a circle
void circle(const Sint16 cx,
            const Sint16 cy,
            const Sint16 r,
            color::Color colour) {
  SDL_Renderer* renderer = Services::getDisplayService().getRenderer();
  circleRGBA(renderer, cx, cy, r, colour.r, colour.g, colour.b, colour.a);
}

// Draw a pixel
void pixel(const Sint16 x, const Sint16 y, color::Color colour) {
  SDL_Renderer* renderer = Services::getDisplayService().getRenderer();
  pixelRGBA(renderer, x, y, colour.r, colour.g, colour.b, colour.a);
}

// Draw a line
void line(const Sint16 x1,
          const Sint16 y1,
          const Sint16 x2,
          const Sint16 y2,
          color::Color colour) {
  SDL_Renderer* renderer = Services::getDisplayService().getRenderer();
  lineRGBA(renderer, x1, y1, x2, y2, colour.r, colour.g, colour.b, colour.a);
}

}  // namespace afk::primitives
