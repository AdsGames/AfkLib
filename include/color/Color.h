#ifndef ENGINE_COLOR_COLOR_H
#define ENGINE_COLOR_COLOR_H

#include <SDL2/SDL2_gfxPrimitives.h>

namespace afk::color {

SDL_Color rgb(const Uint8 r, const Uint8 g, const Uint8 b);

SDL_Color rgba(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a);

SDL_Color intToColor(const Uint32 colour);

Uint32 rgbToInt(const Uint8 r, const Uint8 g, const Uint8 b);

Uint32 rgbaToInt(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a);

Uint32 colorToInt(const SDL_Color colour);

}  // namespace afk::color

#endif  // ENGINE_COLOR_COLOR_H