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
#ifndef AFK_SPRITE_H
#define AFK_SPRITE_H

#include <string>

namespace afk {

struct Sprite {
  /// Texture of Sprite
  std::string texture;
};

}  // namespace afk

#endif  // AFK_SPRITE_H
