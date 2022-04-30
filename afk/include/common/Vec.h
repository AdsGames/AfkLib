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
#ifndef AFK_VEC_H
#define AFK_VEC_H

namespace afk {

struct Vec2 {
  Vec2() = default;
  Vec2(float x, float y) : x(x), y(y) {}

  float x = 0.0f;
  float y = 0.0f;
};

struct Vec3 {
  Vec3() = default;
  Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

  float x = 0.0f;
  float y = 0.0f;
  float z = 0.0f;
};

}  // namespace afk

#endif  // AFK_VEC_H
