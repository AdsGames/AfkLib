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
  texture.drawEx(x, y, width, height, angle);
}

void Image::setTexture(const std::string& texture) {
  this->texture = scene.assets.getImage(texture);
  this->width = this->texture.getWidth();
  this->height = this->texture.getHeight();
}

}  // namespace afk
