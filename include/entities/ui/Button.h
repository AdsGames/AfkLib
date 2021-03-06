/**
 * @file Button.h
 * @author
 *   Allan Legemaate (alegemaate@gmail.com)
 *   Danny Van Stemp (dannyvanstemp@gmail.com)
 * @brief A ui elemenent that accepts a click callback.
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
   */
  explicit Button(Scene& scene,
                  const float x = 0,
                  const float y = 0,
                  const int z = 0);

  /**
   * @brief Draw the button to the screen.
   *
   */
  void draw() override;

  /**
   * @brief Helper to size button to text
   *
   */
  void sizeToText();
};

}  // namespace afk

#endif  // INCLUDE_ENTITIES_UI_BUTTON_H_

/**
 * @example ex_ui.cpp
 * This example shows how to use various ui elements
 */
