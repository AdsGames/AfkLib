#ifndef ENGINE_COLOR_COLOR_H
#define ENGINE_COLOR_COLOR_H

#include <SDL2/SDL2_gfxPrimitives.h>

namespace Color {

SDL_Color rgb(const unsigned char r,
              const unsigned char g,
              const unsigned char b);
SDL_Color rgba(const unsigned char r,
               const unsigned char g,
               const unsigned char b,
               const unsigned char a);
}  // namespace Color

#endif  // ENGINE_COLOR_COLOR_H