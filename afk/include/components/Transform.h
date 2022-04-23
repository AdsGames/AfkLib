/**
 * @file Transform.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Transform, stores positioning
 * @version 0.1
 * @date 2021-03-15
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef AFK_TRANSFORM_H
#define AFK_TRANSFORM_H

#include "../common/Vec.h"

namespace afk {

struct Transform {
  /// Position on x y z plane
  Vec3 position;

  /// Size
  Vec2 size;

  /// Rotation
  float angle = 0.0f;
};

}  // namespace afk

#endif  // AFK_TRANSFORM_H
