/*
 * Particle
 * Just little blips that make things look cool
 * A.D.S. Games
 */
#ifndef ENGINE_PARTICLES_PARTICLE_H
#define ENGINE_PARTICLES_PARTICLE_H

#include <allegro5/allegro_primitives.h>

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
           ALLEGRO_COLOR color,
           float velocity_x,
           float velocity_y,
           int size,
           ParticleType type);

  Particle(float x,
           float y,
           ALLEGRO_COLOR color,
           float velocity_x,
           float velocity_y,
           int size,
           int type);

  ~Particle();

  void update();
  void scroll(float x, float y);
  void draw();

 private:
  float x, y;

  int size;
  ParticleType type;

  float velocity_x, velocity_y;

  ALLEGRO_COLOR color;
};

#endif  // ENGINE_PARTICLES_PARTICLE_H
