#ifndef ENGINE_UI_LABEL_H
#define ENGINE_UI_LABEL_H

#include "UIElement.h"

/**
 * @brief Implementation of UI Label.
 *
 * @author Danny Van Stemp and Allan Legemaate
 * @date 25/11/2018
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
  virtual void draw() override;
};

#endif  // ENGINE_UI_LABEL_H
