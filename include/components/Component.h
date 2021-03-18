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
#ifndef INCLUDE_COMPONENTS_COMPONENT_H_
#define INCLUDE_COMPONENTS_COMPONENT_H_

#include "entities/ObjId.h"

namespace afk {

class Component {
 public:
  explicit Component(ObjId obj_id);
  virtual ~Component() = default;

  const ObjId obj_id;
};

}  // namespace afk

#endif  // INCLUDE_COMPONENTS_COMPONENT_H_
