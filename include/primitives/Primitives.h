#ifndef ENGINE_PRIMITIVES_PRIMITIVES_H
#define ENGINE_PRIMITIVES_PRIMITIVES_H

#include "color/Color.h"

namespace Primitives {
void rect(const float x1,
          const float y1,
          const float x2,
          const float y2,
          SDL_Color color,
          const float thickness);
void rectfill(const float x1,
              const float y1,
              const float x2,
              const float y2,
              SDL_Color color);
void circle(const float cx,
            const float cy,
            const float r,
            SDL_Color color,
            const float thickness);
}  // namespace Primitives

#endif  // ENGINE_PRIMITIVES_PRIMITIVES_H