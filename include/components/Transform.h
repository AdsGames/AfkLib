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
#ifndef INCLUDE_COMPONENTS_TRANSFORM_H_
#define INCLUDE_COMPONENTS_TRANSFORM_H_

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

#endif  // INCLUDE_COMPONENTS_TRANSFORM_H_
