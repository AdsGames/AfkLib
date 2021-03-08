#include "entities/ParticleEmitter.h"

#include "color/Color.h"
#include "primitives/Primitives.h"
#include "scene/Scene.h"

#include "services/Services.h"

namespace afk {

// Constructor
ParticleEmitter::ParticleEmitter(const Scene& scene,
                                 Particle particle,
                                 const float x,
                                 const float y,
                                 const int z)
    : GameObject(scene, x, y, z), particle(particle) {}

// Destructor
ParticleEmitter::~ParticleEmitter() {}

// Draw
void ParticleEmitter::draw() {
  // Draw particles
  for (auto& particle : particles) {
    particle.draw();
  }
}

// Update
void ParticleEmitter::update() {
  particles.push_back(Particle(particle));

  // Draw particles
  for (auto& particle : particles) {
    particle.update();
  }
}

}  // namespace afk
