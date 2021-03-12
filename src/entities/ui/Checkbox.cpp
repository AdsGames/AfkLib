/**
 * @file Checkbox.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of UI Checkbox
 * @version 0.1
 * @date 2021-03-12
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <functional>
#include <iostream>

#include "entities/ui/Checkbox.h"

#include "color/Color.h"
#include "primitives/Primitives.h"
#include "scene/Scene.h"
#include "services/Services.h"

const int DEFAULT_HEIGHT = 20;
const int DEFAULT_WIDTH = 20;

namespace afk {

// Ctor
Checkbox::Checkbox(Scene& scene, const int x, const int y, const int z)
    : UIElement(scene, x, y, z), checked(false), onCheck(nullptr) {
  this->height = DEFAULT_HEIGHT;
  this->width = DEFAULT_WIDTH;
}

// Draw checkbox
void Checkbox::draw() {
  // Draw checkbox background
  primitives::rectfill(x, y, width, height, color::white);

  // Draw checkbox border
  primitives::rect(x, y, width, height, color::black);

  if (checked) {
    primitives::rectfill(x + width / 4, y + height / 4, width - width / 2,
                         height - height / 2, color::black);
  }

  // Draw text label
  font.draw(x + width + 10, y + height - font.getHeight(), text, color::black);
}

// Check checkbox stat
bool Checkbox::getChecked() const {
  return checked;
}

// Set checked state
void Checkbox::setChecked(const bool checked) {
  this->checked = checked;
}

// Set on click
void Checkbox::setOnCheck(std::function<void(bool)> func) {
  this->onCheck = func;
}

// On click interceptor
void Checkbox::handleOnClick() {
  checked = !checked;
  std::cout << checked << std::endl;
  if (onCheck) {
    onCheck(checked);
  }
  if (onClick) {
    onClick();
  }
}

}  // namespace afk
