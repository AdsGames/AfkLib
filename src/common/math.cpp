/**
 * @file math.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of math functions
 * @version 0.1
 * @date 2021-03-08
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "common/math.h"

namespace afk {
namespace math {

// Lerp between two values
float lerp(float start, float end, float progress) {
  return start + progress * (end - start);
}

// Clamp a value between a min and a max
float clamp(float value, float min, float max) {
  if (value < min) {
    return min;
  }
  if (value > max) {
    return max;
  }
  return value;
}

}  // namespace math
}  // namespace afk
