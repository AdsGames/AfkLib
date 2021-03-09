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
#include "common/math.h"
#include "scene/Scene.h"

namespace afk {

// Constructor
Particle::Particle(Scene& scene,
                   const float x,
                   const float y,
                   const float z,
                   const ParticleType type)
    : Sprite(scene, x, y, z),
      type(type),
      start_size(1),
      end_size(1),
      velocity_x(0),
      velocity_y(0),
      acceleration_x(0),
      acceleration_y(0),
      age(0),
      lifespan(1000),
      start_color(color::rgb(0, 0, 0)),
      end_color(color::rgb(0, 0, 0)) {}

// Logic
void Particle::update() {
  if (dead()) {
    return;
  }

  // Update velocity
  x += velocity_x + acceleration_x * age;
  y += velocity_y + acceleration_y * age;

  // Its dead
  this->age += 4.0f;
}

// Draw
void Particle::draw() {
  if (dead()) {
    return;
  }

  float life_percent = age / lifespan;

  // Lerp size
  float size = math::lerp(start_size, end_size, life_percent);

  // Lerp color
  Uint8 r = math::lerp(start_color.r, end_color.r, life_percent);
  Uint8 g = math::lerp(start_color.g, end_color.g, life_percent);
  Uint8 b = math::lerp(start_color.b, end_color.b, life_percent);
  Uint8 a = math::lerp(start_color.a, end_color.a, life_percent);
  color::Color color = {r, g, b, a};

  // Switch over type
  switch (type) {
    case ParticleType::SQUARE:
      primitives::rectfill(x, y, size, size, color);
      break;
    case ParticleType::CIRCLE:
      primitives::circle(x, y, size, color);
      break;
    case ParticleType::PIXEL:
      primitives::pixel(x, y, color);
      break;
    case ParticleType::IMAGE:
      texture.drawEx(x, y, size, size, 0);
    default:
      break;
  }
}

// Set the size of the particle in pixels
void Particle::setSize(const float size) {
  this->start_size = size;
  this->end_size = size;
}

// Set the size of particle over lifespan
void Particle::setSize(const float start_size, const float end_size) {
  this->start_size = start_size;
  this->end_size = end_size;
}

// Set the velocity of particle
void Particle::setVelocity(const float x, const float y) {
  this->velocity_x = x;
  this->velocity_y = y;
}

// Set the accleration of particle
void Particle::setAcceleration(const float x, const float y) {
  this->acceleration_x = x;
  this->acceleration_y = y;
}

// Set the lifespan of particle in ms, start dead
void Particle::setLifespan(const float lifespan) {
  this->lifespan = lifespan;
  this->age = lifespan;
}

// Set the particle color
void Particle::setColor(const color::Color& color) {
  this->start_color = color;
  this->end_color = color;
}

// Set the particle color over lifespan
void Particle::setColor(const color::Color& start_color,
                        const color::Color& end_color) {
  this->start_color = start_color;
  this->end_color = end_color;
}

// Reest age
void Particle::reset() {
  this->age = 0;
}

// Check if dead
bool Particle::dead() {
  return this->age >= this->lifespan;
}

}  // namespace afk
