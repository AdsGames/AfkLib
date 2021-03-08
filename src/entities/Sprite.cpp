#include "entities/Sprite.h"

#include "color/Color.h"
#include "primitives/Primitives.h"
#include "scene/Scene.h"

#include "services/Services.h"

namespace afk {

// Constructor
Sprite::Sprite(Scene& scene, const float x, const float y, const int z)
    : GameObject(scene, x, y, z), visible(true) {}

// Constructor
Sprite::Sprite(Scene& scene,
               const std::string& texture,
               const float x,
               const float y,
               const int z)
    : Sprite(scene, x, y, z) {
  setTexture(texture);
}

// Destructor
Sprite::~Sprite() {}

void Sprite::setVisible(const bool visible) {
  this->visible = visible;
}

void Sprite::setTexture(const std::string& texture) {
  this->texture = Services::getAssetService().getImage(texture);
  this->width = this->texture.getWidth();
  this->height = this->texture.getHeight();
}

// Draw
void Sprite::draw() {
  // Don't show if not visible
  if (!visible) {
    return;
  }

  // Draw image
  texture.drawScaled(x, y, width, height);

  // Draw bounding box
  if (Services::getConfigService().get<bool>("debug", false)) {
    primitives::rect(x, y, width, height, color::rgb(88, 88, 88));
  }
}

}