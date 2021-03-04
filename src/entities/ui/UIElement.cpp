#include "entities/ui/UIElement.h"

#include <string>
#include "scene/Scene.h"
#include "services/Locator.h"

// Constructor
UIElement::UIElement(Scene& scene,
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
    this->font = Locator::getAsset().getFont(text);
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

  if (Locator::getInput().mouse().down[1]) {
    bool is_colliding = Locator::getInput().mouse().x < x + width &&
                        Locator::getInput().mouse().y < y + height &&
                        Locator::getInput().mouse().x > x &&
                        Locator::getInput().mouse().y > y;

    if (is_colliding) {
      onClick();
    }
  }
}

// On click
void UIElement::setOnClick(std::function<void(void)> func) {
  this->onClick = func;
}
