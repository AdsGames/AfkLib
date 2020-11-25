#include "ui/Button.h"

#include <allegro5/allegro_primitives.h>

#include "scene/Scene.h"

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
  this->image = this->scene.getAsset().getImage(textureId);
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
    al_draw_filled_rectangle(x, y, x + width, y + height,
                             al_map_rgb(255, 255, 255));

    // Text
    font.draw(x, y, text, al_map_rgb(0, 0, 0));
  }
}
