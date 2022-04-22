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
#ifndef INCLUDE_SYSTEMS_PARTICLE_SYSTEM_H_
#define INCLUDE_SYSTEMS_PARTICLE_SYSTEM_H_

#include <algorithm>
#include <entt/entt.hpp>
#include <vector>

#include "common/math.h"
#include "common/random.h"
#include "components/Particle.h"
#include "components/ParticleEmitter.h"
#include "components/Transform.h"
#include "primitives/Primitives.h"
#include "services/assets/AssetService.h"

namespace afk::systems {

/**
 * @brief ParticleSystem
 *
 */
void particleSystem(registry& registry, float delta) {
  auto particle_view = registry.view<Transform, Particle>();

  int count = 0;
  for (auto [entity, tran, particle] : particle_view.each()) {
    tran.size.x = math::lerp(particle.start_size, particle.end_size,
                             particle.age / particle.lifespan);
    tran.size.y = tran.size.x;

    particle.age += delta;
    if (particle.age > particle.lifespan) {
      registry.destroy(entity);
    }

    count++;
  }

  auto system_view = registry.view<Transform, ParticleEmitter>();

  for (auto [entity, tran, emitter] : system_view.each()) {
    emitter.counter += delta;

    while (emitter.counter > emitter.frequency &&
           emitter.templates.size() > 0) {
      int index = random::randomInt(0, emitter.templates.size() - 1);
      auto& [particle, physics] = emitter.templates.at(index);

      emitter.counter -= emitter.frequency;

      const float start_x =
          tran.position.x + random::randomFloat(0, tran.size.x);
      const float start_y =
          tran.position.y + random::randomFloat(0, tran.size.y);

      const auto& particle_id = registry.create();
      registry.emplace<Particle>(particle_id, particle);
      registry.emplace<Physics>(particle_id, physics);
      registry.emplace<Transform>(
          particle_id, Vec3(start_x, start_y, tran.position.z),
          Vec2(particle.start_size, particle.start_size));
    }
  }
}

void particleRenderSystem(registry& registry, AssetService& assetService) {
  auto view = registry.view<Transform, Particle>();

  for (auto [entity, tran, particle] : view.each()) {
    float life_percent = particle.age / particle.lifespan;

    // Lerp size
    float size =
        math::lerp(particle.start_size, particle.end_size, life_percent);

    // Lerp color
    Uint8 r =
        math::lerp(particle.start_color.r, particle.end_color.r, life_percent);
    Uint8 g =
        math::lerp(particle.start_color.g, particle.end_color.g, life_percent);
    Uint8 b =
        math::lerp(particle.start_color.b, particle.end_color.b, life_percent);
    Uint8 a =
        math::lerp(particle.start_color.a, particle.end_color.a, life_percent);
    color::Color color = {r, g, b, a};

    // Switch over type
    switch (particle.type) {
      case ParticleType::SQUARE:
        primitives::rectfill(tran.position.x, tran.position.y, size, size,
                             color);
        break;
      case ParticleType::CIRCLE:
        primitives::circle(tran.position.x, tran.position.y, size, color);
        break;
      case ParticleType::PIXEL:
        primitives::pixel(tran.position.x, tran.position.y, color);
        break;
      case ParticleType::IMAGE: {
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

#endif  // INCLUDE_SYSTEMS_PARTICLE_SYSTEM_H_