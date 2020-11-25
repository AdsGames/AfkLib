#ifndef ENGINE_ENTITIES_SPRITE_H
#define ENGINE_ENTITIES_SPRITE_H

#include <vector>

#include "../particles/Particle.h"
#include "../textures/Texture.h"
#include "GameObject.h"

/**
 * @brief A simple texturable game object
 *
 * @author Allan Legemaate
 * @date 30/10/2020
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
   * @override
   */
  virtual void draw() override;

  /**
   * @brief Set the visibility of the sprite. Will not draw when not visible.
   *
   * @param visible Visibility to set to
   */
  void setVisible(const bool visible);

  /**
   * @brief Set the Texture of the sprite
   *
   * @param texture Id of texture to assign
   */
  void setTexture(const std::string& texture);

 protected:
  /// Texture of Sprite
  Texture texture;

  /// Visibility
  bool visible;

  /// Particles
  std::vector<Particle> parts;
};

#endif  // ENGINE_ENTITIES_SPRITE_H
