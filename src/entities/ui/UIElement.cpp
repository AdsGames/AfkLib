#include "entities/ui/UIElement.h"

#include <string>
#include "scene/Scene.h"
#include "services/Services.h"

namespace afk {

// Constructor
UIElement::UIElement(const Scene& scene,
                     const float x,
                     const float y,
                     const int z,
                     const std::string& text,
                     const std::string& font)
    : GameObject(scene, x, y, z), visible(true), text(text) {
  setFont(font);
}

void UIElement::setVisible(const bool visible) {
  this->visible = visible;
}

void UIElement::setFont(const std::string& text) {
  if (text != "") {
    this->font = Services::getAssetService().getFont(text);
  }
}

void UIElement::setText(const std::string& text) {
  this->text = text;
}

// Draw
void UIElement::draw() {}

// Update
void UIElement::update() {
  if (!onClick) {
    return;
  }

  InputService& input = Services::getInputService();

  if (input.mousePressed(MouseButtons::BUTTON_LEFT)) {
    bool is_colliding = input.mouseX() < x + width &&
                        input.mouseY() < y + height && input.mouseX() > x &&
                        input.mouseY() > y;

    if (is_colliding) {
      onClick();
    }
  }
}

// On click
void UIElement::setOnClick(std::function<void(void)> func) {
  this->onClick = func;
}

}  // namespace afk
