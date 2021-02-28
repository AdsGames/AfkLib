#ifndef ENGINE_PRIMITIVES_PRIMITIVES_H
#define ENGINE_PRIMITIVES_PRIMITIVES_H

#include <allegro5/allegro_color.h>

namespace Primitives {
void rect(const float x1,
          const float y1,
          const float x2,
          const float y2,
          ALLEGRO_COLOR color,
          const float thickness);
void rectfill(const float x1,
              const float y1,
              const float x2,
              const float y2,
              ALLEGRO_COLOR color);
void circle(const float cx,
            const float cy,
            const float r,
            ALLEGRO_COLOR color,
            const float thickness);
}  // namespace Primitives

#endif  // ENGINE_PRIMITIVES_PRIMITIVES_H