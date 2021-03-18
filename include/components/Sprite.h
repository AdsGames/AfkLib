/**
 * @file Sprite.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Stores sprite information for rendering engine
 * @version 0.1
 * @date 2021-03-15
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_COMPONENTS_SPRITE_H_
#define INCLUDE_COMPONENTS_SPRITE_H_

#include "../assets/Texture.h"
#include "Component.h"

namespace afk {

class Sprite : public Component {
 public:
  /**
   * @brief Construct a new Sprite object
   *
   */
  explicit Sprite(ObjId obj_id);

  /// Texture of Sprite
  Texture texture;
};

}  // namespace afk

#endif  // INCLUDE_COMPONENTS_SPRITE_H_
