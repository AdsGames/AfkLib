/**
 * @file Color.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Helpers for creating colors without accessing SDL api directly
 * @version 0.1
 * @date 2021-03-05
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_COLOR_COLOR_H_
#define INCLUDE_COLOR_COLOR_H_

#include <SDL2/SDL2_gfxPrimitives.h>

namespace afk {
namespace color {

// Color
struct Color {
  Uint8 r;
  Uint8 g;
  Uint8 b;
  Uint8 a;
};

// Color defenitions
static const Color black = {0, 0, 0, 255};
static const Color white = {255, 255, 255, 255};
static const Color red = {255, 0, 0, 255};
static const Color orange = {255, 0, 255, 255};
static const Color yellow = {255, 255, 0, 255};
static const Color green = {0, 255, 0, 255};
static const Color blue = {0, 0, 255, 255};
static const Color purple = {0, 255, 255, 255};

/**
 * @brief Create SDL Color from rgb values
 *
 * @param r Red value
 * @param g Green value
 * @param b Blue value
 * @return Color
 */
Color rgb(const Uint8 r, const Uint8 g, const Uint8 b);

/**
 * @brief Create SDL Color from rgba values
 *
 * @param r Red value
 * @param g Green value
 * @param b Blue value
 * @param a Alpha value
 * @return Color
 */
Color rgba(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a);

/**
 * @brief Convert int representation of color to an Color
 *
 * @param colour Integer representation of color
 * @return Color
 */
Color intToColor(const Uint32 colour);

/**
 * @brief Convert rgb values to an integer color
 *
 * @param r Red value
 * @param g Green value
 * @param b Blue value
 * @return Uint32
 */
Uint32 rgbToInt(const Uint8 r, const Uint8 g, const Uint8 b);

/**
 * @brief Convert rgba values to an integer color
 *
 * @param r Red value
 * @param g Green value
 * @param b Blue value
 * @param a Alpha value
 * @return Uint32
 */
Uint32 rgbaToInt(const Uint8 r, const Uint8 g, const Uint8 b, const Uint8 a);

/**
 * @brief Convert Color to Uint32 representation
 *
 * @param colour Color to convert
 * @return Uint32
 */
Uint32 colorToInt(const Color colour);

}  // namespace color
}  // namespace afk

#endif  // INCLUDE_COLOR_COLOR_H_
