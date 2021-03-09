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
                                 const int z)
    : GameObject(scene, x, y, z) {}

// Draw
void ParticleEmitter::draw() {
  for (auto& particle : particles) {
    particle.draw();
  }
}

// Update
void ParticleEmitter::update(Uint32 delta) {
  for (auto& particle : particles) {
    particle.update(delta);

    if (particle.dead()) {
      particle.reset();
      particle.setPosition(Random::randomInt(x, x + width),
                           Random::randomInt(y, y + width));
    }
  }
}

// Add
void ParticleEmitter::addParticle(const Particle& particle,
                                  const Uint32 count) {
  for (Uint32 i = 0; i < count; i++) {
    particles.push_back(Particle(particle));
  }
}

}  // namespace afk
