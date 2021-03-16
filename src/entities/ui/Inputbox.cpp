/**
 * @file Inputbox.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of UI Inputbox
 * @version 0.1
 * @date 2021-03-12
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <functional>
#include <iostream>

#include "entities/ui/Inputbox.h"

#include "color/Color.h"
#include "primitives/Primitives.h"
#include "scene/Scene.h"
#include "services/Services.h"

namespace afk {

const int NUMBER_OFFSET = 19;
const int LOWER_OFFSET = 93;
const int UPPER_OFFSET = 61;

const int DEFAULT_HEIGHT = 20;
const int DEFAULT_WIDTH = 100;
const int DEFAULT_PADDING = 5;

// Ctor
Inputbox::Inputbox(Scene& scene, const float x, const float y, const int z)
    : UIElement(scene, x, y, z), iter(text.end()), onChange(nullptr) {
  transform.height = DEFAULT_HEIGHT;
  transform.width = DEFAULT_WIDTH;
}

// Draw checkbox
void Inputbox::draw() {
  // Draw checkbox background
  primitives::rectfill(transform.x, transform.y, transform.width,
                       transform.height, color::white);

  // Draw checkbox border
  primitives::rect(transform.x, transform.y, transform.width, transform.height,
                   color::black);

  // Focus border
  if (id == UIElement::focused) {
    primitives::rect(transform.x + 1, transform.y + 1, transform.width - 2,
                     transform.height - 2, color::black);
  }

  // Draw text label
  font.draw(transform.x + DEFAULT_PADDING,
            transform.y + transform.height - font.getHeight(), text,
            color::black);

  // Draw the caret
  std::string edit_pos = text.substr(0, std::distance(text.begin(), iter));
  int line_x = font.getWidth(edit_pos);

  afk::primitives::line(line_x + transform.x + DEFAULT_PADDING, transform.y + 2,
                        line_x + transform.x + DEFAULT_PADDING,
                        transform.y + transform.height - 2, afk::color::black);
}

// Update loop
void Inputbox::update(Uint32 delta) {
  // Update parent
  UIElement::update(delta);

  // Ensure focused
  if (id != UIElement::focused) {
    return;
  }

  int lastKeyInt = scene.input.lastKeyPressed();
  afk::Keys lastKey = static_cast<afk::Keys>(lastKeyInt);
  bool shiftDown = scene.input.keyDown(afk::Keys::LSHIFT) ||
                   scene.input.keyDown(afk::Keys::RSHIFT);
  bool ctrlDown = scene.input.keyDown(afk::Keys::LCTRL) ||
                  scene.input.keyDown(afk::Keys::RCTRL);

  // Ignore blank key
  if (lastKey == afk::Keys::UNKNOWN) {
    return;
  }

  // Letters
  if (lastKey >= afk::Keys::A && lastKey <= afk::Keys::Z) {
    if (shiftDown) {
      iter = text.insert(iter, lastKeyInt + UPPER_OFFSET);
    } else {
      iter = text.insert(iter, lastKeyInt + LOWER_OFFSET);
    }
    std::advance(iter, 1);
  }

  // Numbers
  else if (lastKey >= afk::Keys::ONE && lastKey <= afk::Keys::NINE) {
    iter = text.insert(iter, lastKeyInt + NUMBER_OFFSET);
    std::advance(iter, 1);
  }

  // Special zero case
  else if (lastKey == afk::Keys::ZERO) {
    iter = text.insert(iter, 48);
    std::advance(iter, 1);
  }

  // Space
  else if (lastKey == afk::Keys::SPACE) {
    iter = text.insert(iter, 32);
    std::advance(iter, 1);
  }

  // Backspace
  else if (lastKey == afk::Keys::BACKSPACE && iter != text.begin()) {
    if (ctrlDown) {
      iter = text.erase(text.begin(), iter);
    } else {
      std::advance(iter, -1);
      iter = text.erase(iter);
    }
  }

  // Delete
  else if (lastKey == afk::Keys::DELETE && iter != text.end()) {
    iter = text.erase(iter);
  }

  // Right
  else if (lastKey == afk::Keys::RIGHT && iter != text.end()) {
    std::advance(iter, 1);
  }

  // Left
  else if (lastKey == afk::Keys::LEFT && iter != text.begin()) {
    std::advance(iter, -1);
  }
}

// Set text
void Inputbox::setText(const std::string& text) {
  this->text = text;
  iter = this->text.end();
}

// Set on click
void Inputbox::setOnChange(std::function<void(const std::string& text)> func) {
  this->onChange = func;
}

}  // namespace afk
