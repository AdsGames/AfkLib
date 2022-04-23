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
#include "common/Color.h"

namespace afk::color {

// Create color from RGB
Color rgb(const uint8_t r, const uint8_t g, const uint8_t b) {
  return rgba(r, g, b, 255);
}

// Create color from rgba
Color rgba(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) {
  return {r, g, b, a};
}

// Create color from int
Color intToColor(const uint32_t colour) {
  Color tempCol = {};
  tempCol.r = (colour >> 16) & 0xFF;
  tempCol.g = (colour >> 8) & 0xFF;
  tempCol.b = colour & 0xFF;
  tempCol.a = 255;
  return tempCol;
}

// Convert rgb to int
uint32_t rgbToInt(const uint8_t r, const uint8_t g, const uint8_t b) {
  return rgbaToInt(r, g, b, 255);
}

// Convert rgba to int
uint32_t rgbaToInt(const uint8_t r,
                   const uint8_t g,
                   const uint8_t b,
                   const uint8_t a) {
  return (uint32_t)((a << 24) + (r << 16) + (g << 8) + (b << 0));
}

// Convert color to int
uint32_t colorToInt(const Color colour) {
  return rgbaToInt(colour.r, colour.g, colour.b, colour.a);
}

}  // namespace afk::color
