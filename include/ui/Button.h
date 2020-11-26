#ifndef ENGINE_UI_BUTTON_H
#define ENGINE_UI_BUTTON_H

#include "UIElement.h"

#include "../textures/Texture.h"

/**
 * @brief Implementation of clickable UI button.
 *
 * @author Danny Van Stemp and Allan Legemaate
 * @date 11/04/2017
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
  Button(Scene& scene,
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
  Button(Scene& scene,
         const int x,
         const int y,
         const int z,
         const std::string& image_id);

  /**
   * @brief Draw the button to the screen.
   *
   */
  virtual void draw() override;

 private:
  /// Texture for textured buttons
  Texture image;
};

#endif  // ENGINE_UI_BUTTON_H
