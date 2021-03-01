#include "color/Color.h"

SDL_Colour Color::rgb(const unsigned char r,
                      const unsigned char g,
                      const unsigned char b) {
  return {r, g, b, 255};
}

SDL_Colour Color::rgba(const unsigned char r,
                       const unsigned char g,
                       const unsigned char b,
                       const unsigned char a) {
  return {r, g, b, a};
}