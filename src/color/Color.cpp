#include "color/Color.h"

ALLEGRO_COLOR Color::rgb(const unsigned char r,
                         const unsigned char g,
                         const unsigned char b) {
  return al_map_rgb(r, g, b);
}