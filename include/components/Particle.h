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
#ifndef INCLUDE_COMPONENTS_PARTICLE_H_
#define INCLUDE_COMPONENTS_PARTICLE_H_

#include <string>
#include "../color/Color.h"
#include "../common/Vec.h"

namespace afk {

enum class ParticleType : int {
  PIXEL,
  SQUARE,
  CIRCLE,
  IMAGE,
  NONE,
};

struct Particle {
  /// Constructor
  Particle(ParticleType type = ParticleType::PIXEL)
      : type(type),
        start_size(1),
        end_size(1),
        age(0),
        lifespan(1000),
        start_color(color::black),
        end_color(color::black),
        texture(""){};

  Particle(const Particle& part)
      : type(part.type),
        start_size(part.start_size),
        end_size(part.end_size),
        age(0),
        lifespan(part.lifespan),
        start_color(part.start_color),
        end_color(part.end_color),
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
    this->start_size = size;
    this->end_size = size;
  }

  /**
   * @brief Set the size of particle over lifespan
   *
   * @param start_size Size to start at
   * @param end_size Size to end at
   */
  void setSize(const float start_size, const float end_size) {
    this->start_size = start_size;
    this->end_size = end_size;
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
    this->start_color = color;
    this->end_color = color;
  }

  /**
   * @brief Set the particle color over lifespan
   *
   * @param start_color Starting color
   * @param end_color Ending color
   */
  void setColor(const color::Color& start_color,
                const color::Color& end_color) {
    this->start_color = start_color;
    this->end_color = end_color;
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
  float start_size;

  /// Ending size
  float end_size;

  /// Current age
  float age;

  /// Max lifespan
  float lifespan;

  /// Start color
  color::Color start_color;

  /// End color
  color::Color end_color;

  /// String
  std::string texture;
};

}  // namespace afk

#endif  // INCLUDE_COMPONENTS_PARTICLE_H_
