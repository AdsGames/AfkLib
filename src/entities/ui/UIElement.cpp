/**
 * @file UIElement.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of UIElement
 * @version 0.1
 * @date 2020-11-01
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "entities/ui/UIElement.h"

#include <string>
#include "scene/Scene.h"
#include "services/Services.h"

namespace afk {

// Static
ObjId UIElement::focused = 0;

// Constructor
UIElement::UIElement(Scene& scene, const float x, const float y, const int z)
    : GameObject(scene, x, y, z),
      text_align(TextAlign::LEFT),
      text(""),
      onClick(nullptr) {}

// Set font of element
void UIElement::setFont(const std::string& font) {
  if (font != "") {
    this->font = Services::getAssetService().getFont(font);
  }
}

// Set text align
void UIElement::setTextAlign(const TextAlign align) {
  text_align = align;
}

// Set text of element
void UIElement::setText(const std::string& text) {
  this->text = text;
}

// Draw
void UIElement::draw() {}

// Update
void UIElement::update(Uint32 delta) {
  InputService& input = Services::getInputService();

  if (input.mousePressed(MouseButtons::LEFT)) {
    bool is_colliding = input.mouseX() < x + width &&
                        input.mouseY() < y + height && input.mouseX() > x &&
                        input.mouseY() > y;

    if (is_colliding) {
      UIElement::focused = id;
      handleOnClick();
    }
  }
}

// Set on click
void UIElement::setOnClick(std::function<void(void)> func) {
  this->onClick = func;
}

// Get text
std::string UIElement::getText() const {
  return text;
}

// Intermediate on click hanlder
void UIElement::handleOnClick() {
  if (onClick) {
    onClick();
  }
}

}  // namespace afk
