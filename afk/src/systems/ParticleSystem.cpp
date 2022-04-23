/**
 * @file ParticleSystem.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief System in charge of updating and rendering particles
 * @version 0.1
 * @date 2022-04-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "systems/ParticleSystem.h"

#include "common/math.h"
#include "common/random.h"
#include "components/Particle.h"
#include "components/ParticleEmitter.h"
#include "components/Transform.h"
#include "primitives/Primitives.h"

namespace afk::systems {

/**
 * @brief ParticleSystem
 *
 */
void particleSystem(Registry& registry, uint32_t delta) {
  auto particleView = registry.view<Transform, Particle>();

  int count = 0;
  for (auto [entity, tran, particle] : particleView.each()) {
    tran.size.x = math::lerp(particle.startSize, particle.endSize,
                             particle.age / particle.lifespan);
    tran.size.y = tran.size.x;

    particle.age += delta;
    if (particle.age > particle.lifespan) {
      registry.destroy(entity);
    }

    count++;
  }

  auto systemView = registry.view<Transform, ParticleEmitter>();

  for (auto [entity, tran, emitter] : systemView.each()) {
    emitter.counter += delta;

    while (emitter.counter > emitter.frequency &&
           !emitter.templates.empty()) {
      int index = random::randomInt(0, emitter.templates.size() - 1);
      auto& [particle, physics] = emitter.templates.at(index);

      emitter.counter -= emitter.frequency;

      const float startX =
          tran.position.x + random::randomFloat(0, tran.size.x);
      const float startY =
          tran.position.y + random::randomFloat(0, tran.size.y);

      const auto& particleId = registry.create();
      registry.emplace<Particle>(particleId, particle);
      registry.emplace<Physics>(particleId, physics);
      registry.emplace<Transform>(
          particleId, Vec3(startX, startY, tran.position.z),
          Vec2(particle.startSize, particle.startSize));
    }
  }
}

void particleRenderSystem(Registry& registry, AssetService& assetService) {
  auto view = registry.view<Transform, Particle>();

  for (auto [entity, tran, particle] : view.each()) {
    float lifePercent = particle.age / particle.lifespan;

    // Lerp size
    float size =
        math::lerp(particle.startSize, particle.endSize, lifePercent);

    // Lerp color
    uint8_t r =
        math::lerp(particle.startColor.r, particle.endColor.r, lifePercent);
    uint8_t g =
        math::lerp(particle.startColor.g, particle.endColor.g, lifePercent);
    uint8_t b =
        math::lerp(particle.startColor.b, particle.endColor.b, lifePercent);
    uint8_t a =
        math::lerp(particle.startColor.a, particle.endColor.a, lifePercent);
    color::Color color = {r, g, b, a};

    // Switch over type
    switch (particle.type) {
      case ParticleType::Square:
        primitives::rectfill(tran.position.x, tran.position.y, size, size,
                             color);
        break;
      case ParticleType::Circle:
        primitives::circle(tran.position.x, tran.position.y, size, color);
        break;
      case ParticleType::Pixel:
        primitives::pixel(tran.position.x, tran.position.y, color);
        break;
      case ParticleType::Image: {
        auto texture = assetService.getImage(particle.texture);
        texture.drawEx(tran.position.x, tran.position.y, tran.size.x,
                       tran.size.y, tran.angle);
        break;
      }
      default:
        break;
    }
  }
}

}  // namespace afk::systems
