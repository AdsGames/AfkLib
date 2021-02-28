#include <allegro5/allegro_primitives.h>

#include "primitives/Primitives.h"

void Primitives::rect(const float x1,
                      const float y1,
                      const float x2,
                      const float y2,
                      ALLEGRO_COLOR color,
                      const float thickness) {
  al_draw_rectangle(x1, y1, x2, y2, color, thickness);
}

void Primitives::rectfill(const float x1,
                          const float y1,
                          const float x2,
                          const float y2,
                          ALLEGRO_COLOR color) {
  al_draw_filled_rectangle(x1, y1, x2, y2, color);
}

void Primitives::circle(const float cx,
                        const float cy,
                        const float r,
                        ALLEGRO_COLOR color,
                        const float thickness) {
  al_draw_circle(cx, cy, r, color, thickness);
}