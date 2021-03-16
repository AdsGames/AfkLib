/**
 * @file Sprite.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of Sprite
 * @version 0.1
 * @date 2020-10-20
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "entities/Sprite.h"

#include "color/Color.h"
#include "primitives/Primitives.h"
#include "scene/Scene.h"

namespace afk {

// Constructor
Sprite::Sprite(Scene& scene, const float x, const float y, const int z)
    : GameObject(scene, x, y, z) {}

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

void Sprite::setTexture(const std::string& texture) {
  this->texture = scene.assets.getImage(texture);
  transform.width = this->texture.getWidth();
  transform.height = this->texture.getHeight();
}

// Draw
void Sprite::draw() {
  // Draw image
  texture.drawEx(transform.x, transform.y, transform.width, transform.height,
                 transform.angle);

  // Draw bounding box
  if (Services::getConfigService().get<bool>("debug", false)) {
    primitives::rect(transform.x, transform.y, transform.width,
                     transform.height, color::red);
  }
}

}  // namespace afk
