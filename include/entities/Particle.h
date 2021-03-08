/**
 * @file Particle.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Just little blips that make things look cool
 * @version 0.1
 * @date 2021-03-08
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_ENTITIES_PARTICLE_H_
#define INCLUDE_ENTITIES_PARTICLE_H_

#include "../primitives/Primitives.h"

namespace afk {

/**
 * @brief Possible types of particles
 *
 */
enum class ParticleType : int {
  PIXEL,
  SQUARE,
  CIRCLE,
  NONE,
};

/**
 * @brief Represents a single Particle
 *
 */
class Particle {
 public:
  Particle(float x,
           float y,
           SDL_Color color,
           float velocity_x,
           float velocity_y,
           int size,
           ParticleType type);

  void update();

  void draw();

 private:
  float x, y;

  int size;
  ParticleType type;

  float velocity_x, velocity_y;

  SDL_Color color;
};

}  // namespace afk

#endif  // INCLUDE_ENTITIES_PARTICLE_H_
