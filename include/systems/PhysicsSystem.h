/**
 * @file PhysicsSystem.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief System in charge of updating transforms
 * @version 0.1
 * @date 2022-04-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef INCLUDE_SYSTEMS_PHYSICS_SYSTEM_H_
#define INCLUDE_SYSTEMS_PHYSICS_SYSTEM_H_

#include <entt/entt.hpp>

#include "components/Physics.h"
#include "components/Transform.h"
#include "services/assets/AssetService.h"

/**
 * @brief PhysicsSystem
 *
 */
namespace afk::systems {

void physicsSystem(entt::registry& registry, Uint32 delta) {
  auto view = registry.view<Transform, Physics>();

  const float delta_seconds = delta / 1000.0f;

  for (auto [entity, tran, physics] : view.each()) {
    tran.position.x += physics.velocity.x * delta_seconds;
    tran.position.y += physics.velocity.y * delta_seconds;
    physics.velocity.x += physics.acceleration.x * delta_seconds;
    physics.velocity.y += physics.acceleration.y * delta_seconds;
  }
}

}  // namespace afk::systems

#endif  // INCLUDE_SYSTEMS_PHYSICS_SYSTEM_H_