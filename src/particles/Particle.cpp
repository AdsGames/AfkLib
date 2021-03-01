#include "particles/Particle.h"

// Constructor
Particle::Particle(float x,
                   float y,
                   SDL_Color color,
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

// Scroll by
void Particle::scroll(float x, float y) {
  this->x += x;
  this->y += y;
}

// Draw
void Particle::draw() {
  switch (type) {
    case ParticleType::SQUARE:
      Primitives::rect(x, y, x + size, y + size, color, 1);
      break;
    case ParticleType::CIRCLE:
      Primitives::circle(x, y, size, color, 1);
      break;
    case ParticleType::PIXEL:
      Primitives::rect(x, y, x, y, color, 1);
      break;
    default:
      break;
  }
}
