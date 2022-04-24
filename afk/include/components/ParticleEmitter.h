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
#ifndef AFK_PARTICLEEMITTER_H
#define AFK_PARTICLEEMITTER_H

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
  /**
   * @brief Add a particle to the emitter pool
   *
   * @param particle Particle template to add
   * @return Particle& Reference to added particle
   */
  ParticleTemplate& addPrefab() {
    prefabs.emplace_back(std::make_pair(Particle(), Physics()));
    return prefabs.back();
  }

  /// Frequency of emit
  float frequency = 0.0f;

  /// Counter
  float counter = 0.0f;

  /// Particle prefabs
  std::vector<ParticleTemplate> prefabs{};
};

}  // namespace afk

#endif  // AFK_PARTICLEEMITTER_H
