/**
 * @file Color.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of color helper functions
 * @version 0.1
 * @date 2021-03-05
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "color/Color.h"

namespace afk {
namespace color {

// Create color from RGB
Color rgb(const Uint8 r, const Uint8 g, const Uint8 b) {
  return rgba(r, g, b, 255);
}

// Create color from rgba
Color rgba(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a) {
  return {r, g, b, a};
}

// Create color from int
Color intToColor(const Uint32 colour) {
  Color tempcol;
  tempcol.r = (colour >> 16) & 0xFF;
  tempcol.g = (colour >> 8) & 0xFF;
  tempcol.b = colour & 0xFF;
  tempcol.a = 255;
  return tempcol;
}

// Convert rgb to int
Uint32 rgbToInt(const Uint8 r, const Uint8 g, const Uint8 b) {
  return rgbaToInt(r, g, b, 255);
}

// Convert rgba to int
Uint32 rgbaToInt(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a) {
  return (Uint32)((a << 24) + (r << 16) + (g << 8) + (b << 0));
}

// Convert color to int
Uint32 colorToInt(const Color colour) {
  return rgbaToInt(colour.r, colour.g, colour.b, colour.a);
}

}  // namespace color
}  // namespace afk
