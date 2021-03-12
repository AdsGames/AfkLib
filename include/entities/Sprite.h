/**
 * @file Sprite.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Simple textured GameObject
 * @version 0.1
 * @date 2020-10-20
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_ENTITIES_SPRITE_H_
#define INCLUDE_ENTITIES_SPRITE_H_

#include <string>
#include <vector>

#include "../assets/Texture.h"
#include "GameObject.h"

namespace afk {

/**
 * @brief A simple texturable game object
 *
 */
class Sprite : public GameObject {
 public:
  /**
   * @brief Construct a new Sprite object
   *
   * @param scene Reference to scene which is stored in game object
   * @param x X position
   * @param y Y position
   * @param z Z position (for sorting)
   */
  explicit Sprite(Scene& scene,
                  const float x = 0.0f,
                  const float y = 0.0f,
                  const int z = 0);

  /**
   * @brief Construct a new Sprite object
   *
   * @param scene Reference to scene which is stored in game object
   * @param texture Id of texture to assign to sprite
   * @param x X position
   * @param y Y position
   * @param z Z position (for sorting)
   */
  Sprite(Scene& scene,
         const std::string& texture,
         const float x = 0.0f,
         const float y = 0.0f,
         const int z = 0);

  /**
   * @brief Destroy the Sprite object
   *
   */
  virtual ~Sprite();

  /**
   * @brief Hook into draw loop
   *
   */
  void draw() override;

  /**
   * @brief Set the Texture of the sprite
   *
   * @param texture Id of texture to assign
   */
  void setTexture(const std::string& texture);

 protected:
  /// Texture of Sprite
  Texture texture;
};

}  // namespace afk

#endif  // INCLUDE_ENTITIES_SPRITE_H_

/**
 * @example ex_sprite.cpp
 * This example shows basic usage of a sprite
 */

/**
 * @example ex_fps.cpp
 * This example shows a stress test of sprites
 */
