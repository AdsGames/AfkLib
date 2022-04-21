/**
 * @file Image.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Texturable ui element
 * @version 0.1
 * @date 2021-03-12
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "entities/ui/Image.h"

#include "scene/Scene.h"

namespace afk {

// Detailed constructor
Image::Image(Scene& scene, const float x, const float y, const int z)
    : UIElement(scene, x, y, z) {}

// Draw image
void Image::draw() {
  texture.drawEx(transform.position.x, transform.position.y, transform.size.x,
                 transform.size.y, transform.angle);
}

void Image::setTexture(const std::string& texture) {
  this->texture = scene.assets.getImage(texture);

  transform.size.x = this->texture.getWidth();
  transform.size.y = this->texture.getHeight();
}

}  // namespace afk
