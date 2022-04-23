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
  /// Constructor
  explicit Particle(ParticleType type = ParticleType::Pixel)
      : type(type),
        startSize(1),
        endSize(1),
        age(0),
        lifespan(1000),
        startColor(color::black),
        endColor(color::black){};

  Particle(const Particle& part)
      : type(part.type),
        startSize(part.startSize),
        endSize(part.endSize),
        age(0),
        lifespan(part.lifespan),
        startColor(part.startColor),
        endColor(part.endColor),
        texture(part.texture){};

  /**
   * @brief Set the type
   *
   * @param type Type of particle
   */
  void setType(ParticleType type) { this->type = type; }

  /**
   * @brief Set the size of the particle in pixels
   *
   * @param size Size of particle
   */
  void setSize(const float size) {
    this->startSize = size;
    this->endSize = size;
  }

  /**
   * @brief Set the size of particle over lifespan
   *
   * @param startSize Size to start at
   * @param endSize Size to end at
   */
  void setSize(const float startSize, const float endSize) {
    this->startSize = startSize;
    this->endSize = endSize;
  }

  /**
   * @brief Set the lifespan of particle in ms
   *
   * @param lifespan Number of ms to stay alive
   */
  void setLifespan(const float lifespan) {
    this->lifespan = lifespan;
    this->age = lifespan;
  }

  /**
   * @brief Set the particle color
   *
   * @param color Color to set to
   */
  void setColor(const color::Color& color) {
    this->startColor = color;
    this->endColor = color;
  }

  /**
   * @brief Set the particle color over lifespan
   *
   * @param startColor Starting color
   * @param endColor Ending color
   */
  void setColor(const color::Color& startColor, const color::Color& endColor) {
    this->startColor = startColor;
    this->endColor = endColor;
  }

  /**
   * @brief Set the texture id of the particle
   *
   * @param texture Texture id
   */
  void setTexture(const std::string& texture) { this->texture = texture; }

  /// Type of particle
  ParticleType type;

  /// Starting size
  float startSize;

  /// Ending size
  float endSize;

  /// Current age
  uint32_t age;

  /// Max lifespan
  float lifespan;

  /// Start color
  color::Color startColor;

  /// End color
  color::Color endColor;

  /// String
  std::string texture;
};

}  // namespace afk

#endif  // AFK_PARTICLE_H
