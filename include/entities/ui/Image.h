/**
 * @file Image.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief UI Image
 * @version 0.1
 * @date 2021-03-12
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_ENTITIES_UI_IMAGE_H_
#define INCLUDE_ENTITIES_UI_IMAGE_H_

#include <string>

#include "../../assets/Texture.h"
#include "UIElement.h"

namespace afk {

/**
 * @brief A simple texturable game object
 *
 */
class Image : public UIElement {
 public:
  /**
   * @brief Construct a new Image object
   *
   * @param scene Reference to scene which is stored in game object
   * @param x X position
   * @param y Y position
   * @param z Z position (for sorting)
   */
  explicit Image(Scene& scene,
                 const float x = 0.0f,
                 const float y = 0.0f,
                 const int z = 0);

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
  /// Texture of Image
  Texture texture;
};

}  // namespace afk

#endif  // INCLUDE_ENTITIES_UI_IMAGE_H_

/**
 * @example ex_ui.cpp
 * This example shows how to use various ui elements
 */
