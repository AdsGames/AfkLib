#ifndef ENGINE_PRIMITIVES_PRIMITIVES_H
#define ENGINE_PRIMITIVES_PRIMITIVES_H

#include "../color/Color.h"

namespace afk::primitives {

void rect(const int x, const int y, const int w, const int h, SDL_Color colour);

void rectfill(const int x,
              const int y,
              const int w,
              const int h,
              SDL_Color colour);

void circle(const int cx, const int cy, const int r, SDL_Color colour);

}  // namespace afk::primitives

#endif  // ENGINE_PRIMITIVES_PRIMITIVES_H