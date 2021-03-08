/**
 * @file Label.cpp
 * @author
 *   Allan Legemaate (alegemaate@gmail.com)
 *   Danny Van Stemp (dannyvanstemp@gmail.com)
 * @brief Implementation of Label class
 * @version 0.1
 * @date 2018-11-25
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "entities/ui/Label.h"

#include "color/Color.h"

namespace afk {

// Detailed constructor
Label::Label(const Scene& scene,
             const int x,
             const int y,
             const int z,
             const std::string& text,
             const std::string& font)
    : UIElement(scene, x, y, z, text, font) {
  this->height = this->font.getHeight();
  this->width = this->font.getWidth(text);
}

// Draw label
void Label::draw() {
  // Do not draw if not visible
  if (!visible)
    return;

  // Text
  font.draw(x, y, text, color::rgb(0, 0, 0));
}

}  // namespace afk
