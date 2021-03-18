/**
 * @file Transform.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of transform component
 * @version 0.1
 * @date 2021-03-15
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "components/Transform.h"

namespace afk {

Transform::Transform(ObjId obj_id)
    : Component(obj_id),
      x(0),
      y(0),
      z(0),
      height(0),
      width(0),
      angle(0),
      last_x(0),
      last_y(0) {}

}  // namespace afk
