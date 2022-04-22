/**
 * @file ParticleEmitter.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Manage particles
 * @version 0.1
 * @date 2022-04-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef INCLUDE_COMPONENTS_PARTICLE_EMITTER_H_
#define INCLUDE_COMPONENTS_PARTICLE_EMITTER_H_

#include <string>
#include <utility>
#include <vector>

#include "../common/Color.h"
#include "../common/Vec.h"
#include "./Particle.h"
#include "./Physics.h"

namespace afk {

using ParticleTemplate = std::pair<Particle, Physics>;

struct ParticleEmitter {
  /// Constructor
  ParticleEmitter(float frequency) : frequency(frequency), counter(0){};

  /**
   * @brief Add a particle to the emitter pool
   *
   * @param particle Particle template to add
   * @return Particle& Reference to added particle
   */
  ParticleTemplate& addParticle() {
    templates.emplace_back(std::make_pair(Particle(), Physics()));
    return templates.back();
  }

  /// Particle templates
  std::vector<ParticleTemplate> templates;

  /// Frequency of emit
  float frequency;

  /// Counter
  float counter;
};

}  // namespace afk

#endif  // INCLUDE_COMPONENTS_PARTICLE_EMITTER_H_
