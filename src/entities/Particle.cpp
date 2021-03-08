/**
 * @file Particle.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of Particle
 * @version 0.1
 * @date 2021-03-08
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "entities/Particle.h"

namespace afk {

// Constructor
Particle::Particle(float x,
                   float y,
                   color::Color color,
                   float velocity_x,
                   float velocity_y,
                   int size,
                   ParticleType type)
    : x(x),
      y(y),
      size(size),
      type(type),
      velocity_x(velocity_x),
      velocity_y(velocity_y),
      color(color) {}

// Logic
void Particle::update() {
  x += velocity_x;
  y += velocity_y;
}

// Draw
void Particle::draw() {
  switch (type) {
    case ParticleType::SQUARE:
      primitives::rect(x, y, size, size, color);
      break;
    case ParticleType::CIRCLE:
      primitives::circle(x, y, size, color);
      break;
    case ParticleType::PIXEL:
      primitives::pixel(x, y, color);
      break;
    default:
      break;
  }
}

}  // namespace afk
