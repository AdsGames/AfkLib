/**
 * @file Button.h
 * @author
 *   Allan Legemaate (alegemaate@gmail.com)
 *   Danny Van Stemp (dannyvanstemp@gmail.com)
 * @brief Implementation of clickable UI Button
 * @version 0.1
 * @date 2017-04-11
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_ENTITIES_UI_BUTTON_H_
#define INCLUDE_ENTITIES_UI_BUTTON_H_

#include "UIElement.h"

#include <string>

#include "../../assets/Texture.h"

namespace afk {

/**
 * @brief Implementation of clickable UI Button
 *
 */
class Button : public UIElement {
 public:
  /**
   * @brief Construct a new Button object
   *
   * @param scene Scene to add element to
   * @param x X position of element
   * @param y Y position of element
   * @param z Z position of element (for sorting)
   * @param text Text to display, if applicable
   * @param font Font to use to display text
   */
  Button(const Scene& scene,
         const int x,
         const int y,
         const int z,
         const std::string& text,
         const std::string& font);

  /**
   * @brief Construct a new textured Button object
   *
   * @param scene Scene to add element to
   * @param x X position of element
   * @param y Y position of element
   * @param z Z position of element (for sorting)
   * @param image_id Id of image to assign to button
   */
  Button(const Scene& scene,
         const int x,
         const int y,
         const int z,
         const std::string& image_id);

  /**
   * @brief Draw the button to the screen.
   *
   */
  void draw() override;

 private:
  /// Texture for textured buttons
  Texture image;
};

}  // namespace afk

#endif  // INCLUDE_ENTITIES_UI_BUTTON_H_
