#include "entities/ui/Button.h"

#include "color/Color.h"
#include "primitives/Primitives.h"
#include "scene/Scene.h"
#include "services/Services.h"

namespace afk {

// Ctor
Button::Button(const Scene& scene,
               const int x,
               const int y,
               const int z,
               const std::string& text,
               const std::string& font)
    : UIElement(scene, x, y, z, text, font) {
  this->height = this->font.getHeight();
  this->width = this->font.getWidth(text);
}

Button::Button(const Scene& scene,
               const int x,
               const int y,
               const int z,
               const std::string& textureId)
    : UIElement(scene, x, y, z, "", "") {
  this->image = Services::getAssetService().getImage(textureId);
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
    primitives::rectfill(x, y, width, height, color::rgb(255, 255, 255));

    // Draw button border
    primitives::rect(x, y, width, height, color::rgb(0, 0, 0));

    // Text
    font.draw(x, y, text, color::rgb(0, 0, 0));
  }
}

}  // namespace afk
