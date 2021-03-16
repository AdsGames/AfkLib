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

#include "entities/ui/Checkbox.h"

#include "color/Color.h"
#include "primitives/Primitives.h"
#include "scene/Scene.h"
#include "services/Services.h"

const int DEFAULT_HEIGHT = 20;
const int DEFAULT_WIDTH = 20;

namespace afk {

// Ctor
Checkbox::Checkbox(Scene& scene, const float x, const float y, const int z)
    : UIElement(scene, x, y, z), checked(false), onCheck(nullptr) {
  transform.height = DEFAULT_HEIGHT;
  transform.width = DEFAULT_WIDTH;
}

// Draw checkbox
void Checkbox::draw() {
  // Draw checkbox background
  primitives::rectfill(transform.x, transform.y, transform.width,
                       transform.height, color::white);

  // Draw checkbox border
  primitives::rect(transform.x, transform.y, transform.width, transform.height,
                   color::black);

  if (checked) {
    primitives::rectfill(transform.x + transform.width / 4,
                         transform.y + transform.height / 4,
                         transform.width - transform.width / 2,
                         transform.height - transform.height / 2, color::black);
  }

  // Draw text label
  font.draw(transform.x + transform.width + 10,
            transform.y + transform.height - font.getHeight(), text,
            color::black);
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
  if (onCheck) {
    onCheck(checked);
  }
  if (onClick) {
    onClick();
  }
}

}  // namespace afk
