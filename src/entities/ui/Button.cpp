#include "entities/ui/Button.h"

#include "color/Color.h"
#include "primitives/Primitives.h"
#include "scene/Scene.h"
#include "services/Locator.h"

// Ctor
Button::Button(Scene& scene,
               const int x,
               const int y,
               const int z,
               const std::string& text,
               const std::string& font)
    : UIElement(scene, x, y, z, text, font) {
  this->height = this->font.getHeight();
  this->width = this->font.getWidth(text);
}

Button::Button(Scene& scene,
               const int x,
               const int y,
               const int z,
               const std::string& textureId)
    : UIElement(scene, x, y, z, "", "") {
  this->image = Locator::getAsset().getImage(textureId);
  this->height = this->image.getHeight();
  this->width = this->image.getWidth();
}

// Draw button
void Button::draw() {
  // Do not draw if not visible
  if (!visible) {
    return;
  }

  if (image.exists()) {
    // Draw image
    image.draw(x, y);
  } else {
    // Draw button background
    Primitives::rectfill(x, y, x + width, y + height,
                         Color::rgb(255, 255, 255));

    // Text
    font.draw(x, y, text, Color::rgb(0, 0, 0));
  }
}
