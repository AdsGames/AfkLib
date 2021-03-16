/**
 * @file ParticleEmitter.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of a particle emitter.
 * and configured.
 * @version 0.1
 * @date 2021-03-06
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "entities/ParticleEmitter.h"

#include "color/Color.h"
#include "primitives/Primitives.h"
#include "random/RandomGenerator.h"
#include "scene/Scene.h"
#include "services/Services.h"

namespace afk {

// Constructor
ParticleEmitter::ParticleEmitter(Scene& scene,
                                 const float x,
                                 const float y,
                                 const int z,
                                 const int frequency)
    : GameObject(scene, x, y, z),
      emitting(true),
      frequency(frequency),
      current_tick(0) {}

// Draw
void ParticleEmitter::draw() {
  for (auto& particle : particles) {
    particle->draw();
  }
}

// Update
void ParticleEmitter::update(Uint32 delta) {
  if (emitting) {
    current_tick += delta;
  }

  for (auto& particle : particles) {
    particle->update(delta);

    if (particle->dead() && emitting && current_tick >= frequency) {
      current_tick -= frequency;
      particle.reset();
      transform.x =
          Random::randomInt(transform.x, transform.x + transform.width);
      transform.y =
          Random::randomInt(transform.y, transform.y + transform.width);
    }
  }
}

// Add
void ParticleEmitter::addParticle(std::unique_ptr<Particle> particle) {
  particles.push_back(std::move(particle));
}

// Enable
void ParticleEmitter::enable() {
  this->emitting = true;
}

// Disable
void ParticleEmitter::disable() {
  this->emitting = false;
}

}  // namespace afk
