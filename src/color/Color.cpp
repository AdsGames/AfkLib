#include "color/Color.h"

namespace afk::color {

SDL_Colour rgb(const unsigned char r,
               const unsigned char g,
               const unsigned char b) {
  return rgba(r, g, b, 255);
}

SDL_Colour rgba(const unsigned char r,
                const unsigned char g,
                const unsigned char b,
                const unsigned char a) {
  SDL_Colour tempcol;
  tempcol.r = r;
  tempcol.g = g;
  tempcol.b = b;
  tempcol.a = a;
  return tempcol;
}

SDL_Color intToColor(const Uint32 colour) {
  SDL_Colour tempcol;
  tempcol.r = (colour >> 16) & 0xFF;
  tempcol.g = (colour >> 8) & 0xFF;
  tempcol.b = colour & 0xFF;
  tempcol.a = 255;
  return tempcol;
}

Uint32 rgbToInt(const Uint8 r, const Uint8 g, const Uint8 b) {
  return rgbaToInt(r, g, b, 255);
}

Uint32 rgbaToInt(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a) {
  return (Uint32)((a << 24) + (r << 16) + (g << 8) + (b << 0));
}

Uint32 colorToInt(const SDL_Color colour) {
  return rgbaToInt(colour.r, colour.g, colour.b, colour.a);
}

}  // namespace afk::color