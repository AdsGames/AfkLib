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
  width = DEFAULT_WIDTH;
  height = DEFAULT_HEIGHT;
}

// Draw button
void Button::draw() {
  // Draw button background
  primitives::rectfill(x, y, width, height, color::white);

  // Draw button border
  primitives::rect(x, y, width, height, color::black);

  // Text
  font.draw(x + DEFAULT_PADDING, y + DEFAULT_PADDING, text, color::black,
            text_align);
}

// Override text setter
void Button::sizeToText() {
  if (!font.exists()) {
    return;
  }
  height = font.getHeight() + DEFAULT_PADDING * 2;
  width = font.getWidth(text) + DEFAULT_PADDING * 2;
}

}  // namespace afk
