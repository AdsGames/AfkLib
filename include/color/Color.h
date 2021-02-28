#ifndef ENGINE_COLOR_COLOR_H
#define ENGINE_COLOR_COLOR_H

#include <allegro5/allegro_color.h>

namespace Color {
ALLEGRO_COLOR rgb(const unsigned char r,
                  const unsigned char g,
                  const unsigned char b);
}

#endif  // ENGINE_COLOR_COLOR_H