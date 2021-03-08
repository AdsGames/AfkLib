#ifndef INCLUDE_ENTITIES_PARTICLEEMITTER_H_
#define INCLUDE_ENTITIES_PARTICLEEMITTER_H_

#include <vector>

#include "GameObject.h"
#include "Particle.h"

namespace afk {

/**
 * @brief Particle Emitter
 *
 * @author Allan Legemaate
 * @date 06/03/2021
 */
class ParticleEmitter : public GameObject {
 public:
  /**
   * @brief Construct a new ParticleEmitter object
   *
   * @param scene Reference to scene which is stored in game object
   * @param particle Particle to emit
   * @param x X position
   * @param y Y position
   * @param z Z position (for sorting)
   */
  explicit ParticleEmitter(const Scene& scene,
                           const Particle particle,
                           const float x = 0.0f,
                           const float y = 0.0f,
                           const int z = 0);

  /**
   * @brief Destroy the ParticleEmitter object
   *
   */
  virtual ~ParticleEmitter();

  /**
   * @brief Hook into draw loop
   *
   */
  void draw() override;

  /**
   * @brief Hook into update loop
   *
   */
  void update() override;

 protected:
  /// Particles
  std::vector<Particle> particles;

  /// Particle type
  Particle particle;
};

}  // namespace afk

#endif  // INCLUDE_ENTITIES_PARTICLEEMITTER_H_
