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
Label::Label(Scene& scene, const float x, const float y, const int z)
    : UIElement(scene, x, y, z) {}

// Draw label
void Label::draw() {
  // Text
  font.draw(transform.x, transform.y, text, color::black, text_align);
}

}  // namespace afk
