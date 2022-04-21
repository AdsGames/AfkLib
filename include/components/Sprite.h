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

#include <string>

namespace afk {

struct SpriteComponent {
  /// Texture of Sprite
  std::string texture;
};

}  // namespace afk

#endif  // INCLUDE_COMPONENTS_SPRITE_H_
