/**
 * @file Label.h
 * @author
 *   Allan Legemaate (alegemaate@gmail.com)
 *   Danny Van Stemp (dannyvanstemp@gmail.com)
 * @brief UI Label that simply displays text.
 * @version 0.1
 * @date 2018-11-25
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_ENTITIES_UI_LABEL_H_
#define INCLUDE_ENTITIES_UI_LABEL_H_

#include "UIElement.h"

#include <string>
namespace afk {

/**
 * @brief Implementation of Label class
 */
class Label : public UIElement {
 public:
  /**
   * @brief Construct a new Label object
   *
   * @param scene Scene to add element to
   * @param x X position of element
   * @param y Y position of element
   * @param z Z position of element (for sorting)
   * @param text Text to display, if applicable
   * @param font Font to use to display text
   */
  Label(Scene& scene,
        const int x,
        const int y,
        const int z,
        const std::string& text,
        const std::string& font);

  /**
   * @brief Draw the label to the screen.
   *
   */
  void draw() override;
};

}  // namespace afk

#endif  // INCLUDE_ENTITIES_UI_LABEL_H_
