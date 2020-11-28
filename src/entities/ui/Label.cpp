#include "entities/ui/Label.h"

// Detailed constructor
Label::Label(Scene& scene,
             const int x,
             const int y,
             const int z,
             const std::string& text,
             const std::string& font)
    : UIElement(scene, x, y, z, text, font) {
  this->height = this->font.getHeight();
  this->width = this->font.getWidth(text);
}

// Draw label
void Label::draw() {
  // Do not draw if not visible
  if (!visible)
    return;

  // Text
  font.draw(x, y, text, al_map_rgb(255, 255, 255));
}
