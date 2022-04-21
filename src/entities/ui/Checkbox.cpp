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
  transform.size.y = DEFAULT_HEIGHT;
  transform.size.x = DEFAULT_WIDTH;
}

// Draw checkbox
void Checkbox::draw() {
  // Draw checkbox background
  primitives::rectfill(transform.position.x, transform.position.y,
                       transform.size.x, transform.size.y, color::white);

  // Draw checkbox border
  primitives::rect(transform.position.x, transform.position.y, transform.size.x,
                   transform.size.y, color::black);

  if (checked) {
    primitives::rectfill(transform.position.x + transform.size.x / 4,
                         transform.position.y + transform.size.y / 4,
                         transform.size.x - transform.size.x / 2,
                         transform.size.y - transform.size.y / 2, color::black);
  }

  // Draw text label
  font.draw(transform.position.x + transform.size.x + 10,
            transform.position.y + transform.size.y - font.getHeight(), text,
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
