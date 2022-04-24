/**
 * @file Particle.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Particle
 * @version 0.1
 * @date 2022-04-20
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef AFK_PARTICLE_H
#define AFK_PARTICLE_H

#include <string>
#include "../common/Color.h"
#include "../common/Vec.h"

namespace afk {

enum class ParticleType : int {
  Pixel,
  Square,
  Circle,
  Image,
  None,
};

struct Particle {
  /// Type of particle
  ParticleType type = ParticleType::Pixel;

  /// Starting size
  float startSize = 1;

  /// Ending size
  float endSize = 1;

  /// Current age
  uint32_t age = 0;

  /// Max lifespan
  float lifespan = 1000;

  /// Start color
  color::Color startColor = color::black;

  /// End color
  color::Color endColor = color::black;

  /// String
  std::string texture;
};

}  // namespace afk

#endif  // AFK_PARTICLE_H
