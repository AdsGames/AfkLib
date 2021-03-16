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

namespace afk {

class Component {
 public:
  Component();
  virtual ~Component() = default;
};

}  // namespace afk

#endif  // INCLUDE_COMPONENTS_COMPONENT_H_
