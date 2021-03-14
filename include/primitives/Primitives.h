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
#ifndef INCLUDE_PRIMITIVES_PRIMITIVES_H_
#define INCLUDE_PRIMITIVES_PRIMITIVES_H_

#include "../color/Color.h"

namespace afk {
namespace primitives {

/**
 * @brief Draw a rectangle border
 *
 * @param x X position of top left corner
 * @param y Y position of top left corner
 * @param w Width of rect
 * @param h Height of rect
 * @param colour Colour of rect
 */
void rect(const Sint32 x,
          const Sint32 y,
          const Sint32 w,
          const Sint32 h,
          color::Color colour);

/**
 * @brief Draw a filled rectangle
 *
 * @param x X position of top left corner
 * @param y Y position of top left corner
 * @param w Width of rect
 * @param h Height of rect
 * @param colour Colour of rect
 */
void rectfill(const Sint32 x,
              const Sint32 y,
              const Sint32 w,
              const Sint32 h,
              color::Color colour);

/**
 * @brief Draw a circle
 *
 * @param cx Centre x
 * @param cy Centre y
 * @param r Radius
 * @param colour Colour of circle
 */
void circle(const Sint16 cx,
            const Sint16 cy,
            const Sint16 r,
            color::Color colour);

/**
 * @brief Draw a single pixel
 *
 * @param x X position of pixel
 * @param y Y position of pixel
 * @param colour Colour of pixel
 */
void pixel(const Sint16 x, const Sint16 y, color::Color colour);

/**
 * @brief Draw line between two points
 *
 * @param x1 X start position of line
 * @param y1 Y start position of line
 * @param x2 X end position of line
 * @param y2 Y end position of line
 * @param colour Colour of line
 */
void line(const Sint16 x1,
          const Sint16 y1,
          const Sint16 x2,
          const Sint16 y2,
          color::Color colour);

}  // namespace primitives
}  // namespace afk

#endif  // INCLUDE_PRIMITIVES_PRIMITIVES_H_
