/**
 * @file math.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief General purpose math functions
 * @version 0.1
 * @date 2021-03-08
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_COMMON_MATH_H_
#define INCLUDE_COMMON_MATH_H_

namespace afk {
namespace math {

/**
 * @brief Lerp between two values
 *
 * @param start Start value
 * @param end End value
 * @param progress Progress from 0.0-1.0
 * @return float Lerped value
 */
float lerp(float start, float end, float progress);

/**
 * @brief Clamp a value between a min and a max
 *
 * @param value Value to clamp
 * @param min Min allowed value
 * @param max Max allowed value
 * @return float clamped value
 */
float clamp(float value, float min, float max);

}  // namespace math
}  // namespace afk

#endif  // INCLUDE_COMMON_MATH_H_
