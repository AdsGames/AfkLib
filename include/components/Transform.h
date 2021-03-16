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

#include "Component.h"

namespace afk {

class Transform : public Component {
 public:
  /**
   * @brief Construct a new Transform object
   *
   */
  Transform();

  virtual ~Transform() = default;

  /// X position on x y plane
  float x;

  /// Y position on x y plane
  float y;

  /// Z position, used for sorting
  int z;

  /// Height in pixels of game object
  int height;

  /// Width in pixels of game object
  int width;

  /// Rotation
  float angle;

  /// Last position y
  int last_x;

  /// Last position x
  int last_y;
};

}  // namespace afk

#endif  // INCLUDE_COMPONENTS_TRANSFORM_H_
