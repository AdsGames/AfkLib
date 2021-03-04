#include "entities/Sprite.h"

#include "color/Color.h"
#include "primitives/Primitives.h"
#include "scene/Scene.h"

#include "services/Locator.h"

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
  this->texture = Locator::getAsset().getImage(texture);
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

  // Draw particles
  if (Locator::getConfig().get<int>("particleType", 0) != 3) {
    for (unsigned int i = 0; i < parts.size(); i++) {
      parts.at(i).draw();
    }
  }

  // Draw bounding box
  if (Locator::getConfig().get<bool>("debug", false)) {
    Primitives::rect(x, y, width, height, Color::rgb(88, 88, 88));
  }
}
