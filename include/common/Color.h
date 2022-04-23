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
#ifndef AFK_COLOR_H
#define AFK_COLOR_H

#include <cstdint>

namespace afk::color {

// Color
struct Color {
  uint8_t r;
  uint8_t g;
  uint8_t b;
  uint8_t a;
};

// Color definitions
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
Color rgb(uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief Create SDL Color from rgba values
 *
 * @param r Red value
 * @param g Green value
 * @param b Blue value
 * @param a Alpha value
 * @return Color
 */
Color rgba(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

/**
 * @brief Convert int representation of color to an Color
 *
 * @param colour Integer representation of color
 * @return Color
 */
Color intToColor(uint32_t colour);

/**
 * @brief Convert rgb values to an integer color
 *
 * @param r Red value
 * @param g Green value
 * @param b Blue value
 * @return uint32_t
 */
uint32_t rgbToInt(uint8_t r, uint8_t g, uint8_t b);

/**
 * @brief Convert rgba values to an integer color
 *
 * @param r Red value
 * @param g Green value
 * @param b Blue value
 * @param a Alpha value
 * @return uint32_t
 */
uint32_t rgbaToInt(uint8_t r, uint8_t g, uint8_t b, uint8_t a);

/**
 * @brief Convert Color to uint32_t representation
 *
 * @param colour Color to convert
 * @return uint32_t
 */
uint32_t colorToInt(Color colour);

}  // namespace afk::color

#endif  // AFK_COLOR_H
