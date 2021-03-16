/**
 * @file Button.cpp
 * @author
 *   Allan Legemaate (alegemaate@gmail.com)
 *   Danny Van Stemp (dannyvanstemp@gmail.com)
 * @brief Implementation of Button
 * @version 0.1
 * @date 2017-04-11
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "entities/ui/Button.h"

#include "color/Color.h"
#include "primitives/Primitives.h"
#include "scene/Scene.h"
#include "services/Services.h"

namespace afk {

const int DEFAULT_HEIGHT = 20;
const int DEFAULT_WIDTH = 20;
const int DEFAULT_PADDING = 5;

// Ctor
Button::Button(Scene& scene, const float x, const float y, const int z)
    : UIElement(scene, x, y, z) {
  transform.width = DEFAULT_WIDTH;
  transform.height = DEFAULT_HEIGHT;
}

// Draw button
void Button::draw() {
  // Draw button background
  primitives::rectfill(transform.x, transform.y, transform.width,
                       transform.height, color::white);

  // Draw button border
  primitives::rect(transform.x, transform.y, transform.width, transform.height,
                   color::black);

  // Text
  font.draw(transform.x + DEFAULT_PADDING, transform.y + DEFAULT_PADDING, text,
            color::black, text_align);
}

// Override text setter
void Button::sizeToText() {
  if (!font.exists()) {
    return;
  }
  transform.height = font.getHeight() + DEFAULT_PADDING * 2;
  transform.width = font.getWidth(text) + DEFAULT_PADDING * 2;
}

}  // namespace afk
