/**
 * @file Particle.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Just little blips that make things look cool
 * @version 0.1
 * @date 2021-03-08
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_ENTITIES_PARTICLE_H_
#define INCLUDE_ENTITIES_PARTICLE_H_

#include "../entities/Sprite.h"
#include "../primitives/Primitives.h"

namespace afk {

/**
 * @brief Possible types of particles
 *
 */
enum class ParticleType : int {
  PIXEL,
  SQUARE,
  CIRCLE,
  IMAGE,
  NONE,
};

/**
 * @brief Represents a single Particle
 *
 */
class Particle : public Sprite {
 public:
  /**
   * @brief Create a new particle
   *
   * @param x X position
   * @param y Y position
   * @param type Type of particle
   */
  explicit Particle(Scene& scene,
                    float x = 0.0f,
                    float y = 0.0f,
                    float z = 0,
                    ParticleType type = ParticleType::PIXEL);

  /**
   * @brief Update particle
   *
   */
  void update() override;

  /**
   * @brief Draw particle
   *
   */
  void draw() override;

  /**
   * @brief Set the size of the particle in pixels
   *
   * @param size Size of particle
   */
  void setSize(const float size);

  /**
   * @brief Set the size of particle over lifespan
   *
   * @param start_size Size to start at
   * @param end_size Size to end at
   */
  void setSize(const float start_size, const float end_size);

  /**
   * @brief Set the velocity of particle
   *
   * @param x X velocity
   * @param y Y velocity
   */
  void setVelocity(const float x, const float y);

  /**
   * @brief Set the acceleration of particle
   *
   * @param x X acceleration
   * @param y Y acceleration
   */
  void setAcceleration(const float x, const float y);

  /**
   * @brief Set the lifespan of particle in ms
   *
   * @param lifespan Number of ms to stay alive
   */
  void setLifespan(const float lifespan);

  /**
   * @brief Set the particle color
   *
   * @param color Color to set to
   */
  void setColor(const color::Color& color);

  /**
   * @brief Set the particle color over lifespan
   *
   * @param start_color Starting color
   * @param end_color Ending color
   */
  void setColor(const color::Color& start_color, const color::Color& end_color);

  /**
   * @brief Reset age
   *
   */
  void reset();

  /**
   * @brief Check if dead
   *
   */
  bool dead();

 private:
  /// Type of particle
  ParticleType type;

  /// Starting size
  float start_size;

  /// Ending size
  float end_size;

  /// Velocity x
  float velocity_x;

  /// Velocity y
  float velocity_y;

  /// Acceleration x
  float acceleration_x;

  /// Acceleration y
  float acceleration_y;

  /// Current age
  float age;

  /// Max lifespan
  float lifespan;

  /// Start color
  color::Color start_color;

  /// End color
  color::Color end_color;
};

}  // namespace afk

#endif  // INCLUDE_ENTITIES_PARTICLE_H_
