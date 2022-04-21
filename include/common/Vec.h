/**
 * @file vec.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Vec types
 * @version 0.1
 * @date 2022-04-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef INCLUDE_COMMON_VEC_H_
#define INCLUDE_COMMON_VEC_H_

namespace afk {

struct Vec2 {
  Vec2() : x(0), y(0) {}
  Vec2(float x, float y) : x(x), y(y) {}

  float x;
  float y;
};

struct Vec3 {
  Vec3() : x(0), y(0), z(0) {}
  Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

  float x;
  float y;
  float z;
};

}  // namespace afk

#endif  // INCLUDE_COMMON_VEC_H_
