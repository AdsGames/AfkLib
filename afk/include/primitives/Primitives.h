/**
 * @file Primitives.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Wrapper for SDL_GFX primitive types. Allows drawing without knowing
 * about SDL
 * @version 0.1
 * @date 2021-03-06
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef AFK_PRIMITIVES_H
#define AFK_PRIMITIVES_H

#include <cstdint>

#include "../common/Color.h"

namespace afk::primitives {

/**
 * @brief Draw a rectangle border
 *
 * @param x X position of top left corner
 * @param y Y position of top left corner
 * @param w Width of rect
 * @param h Height of rect
 * @param colour Colour of rect
 */
void rect(int32_t x, int32_t y, int32_t w, int32_t h, color::Color colour);

/**
 * @brief Draw a filled rectangle
 *
 * @param x X position of top left corner
 * @param y Y position of top left corner
 * @param w Width of rect
 * @param h Height of rect
 * @param colour Colour of rect
 */
void rectfill(int32_t x, int32_t y, int32_t w, int32_t h, color::Color colour);

/**
 * @brief Draw a circle
 *
 * @param cx Centre x
 * @param cy Centre y
 * @param r Radius
 * @param colour Colour of circle
 */
void circle(Sint16 cx, Sint16 cy, Sint16 r, color::Color colour);

/**
 * @brief Draw a single pixel
 *
 * @param x X position of pixel
 * @param y Y position of pixel
 * @param colour Colour of pixel
 */
void pixel(Sint16 x, Sint16 y, color::Color colour);

/**
 * @brief Draw line between two points
 *
 * @param x1 X start position of line
 * @param y1 Y start position of line
 * @param x2 X end position of line
 * @param y2 Y end position of line
 * @param colour Colour of line
 */
void line(Sint16 x1, Sint16 y1, Sint16 x2, Sint16 y2, color::Color colour);

}  // namespace afk::primitives

#endif  // AFK_PRIMITIVES_H
