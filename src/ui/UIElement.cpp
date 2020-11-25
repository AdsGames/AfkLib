#include "ui/UIElement.h"

#include "scene/Scene.h"

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
    this->font = scene.getAsset().getFont(text);
  }
}

void UIElement::setText(const std::string& text) {
  this->text = text;
}

// Draw
void UIElement::draw() {}

// Update
void UIElement::update() {
  if (onClick && scene.getInput().mouse().down[1]) {
    bool is_colliding = scene.getInput().mouse().x < x + width &&
                        scene.getInput().mouse().y < y + width &&
                        x < scene.getInput().mouse().x &&
                        y < scene.getInput().mouse().y;

    if (is_colliding) {
      onClick();
    }
  }
}

// On click
void UIElement::setOnClick(std::function<void(void)> func) {
  this->onClick = func;
}
