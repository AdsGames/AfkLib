/*
 * Particle
 * Just little blips that make things look cool
 * A.D.S. Games
 */
#ifndef PARTICLES_PARTICLE_H
#define PARTICLES_PARTICLE_H

#include "primitives/Primitives.h"

enum class ParticleType : int {
  PIXEL,
  SQUARE,
  CIRCLE,
  NONE,
};

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
  void scroll(float x, float y);
  void draw();

 private:
  float x, y;

  int size;
  ParticleType type;

  float velocity_x, velocity_y;

  SDL_Color color;
};

#endif  // PARTICLES_PARTICLE_H
