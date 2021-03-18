

/**
 * @file Component.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Base component
 * @version 0.1
 * @date 2021-03-15
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_COMPONENTS_COLLIDER_H_
#define INCLUDE_COMPONENTS_COLLIDER_H_

#include <vector>
#include "components/Component.h"

namespace afk {

class Collider : public Component {
 public:
  explicit Collider(ObjId obj_id);

  std::vector<ObjId> collisions;
};

}  // namespace afk

#endif  // INCLUDE_COMPONENTS_COLLIDER_H_
