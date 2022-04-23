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
#include "systems/PhysicsSystem.h"
#include "components/Physics.h"
#include "components/Transform.h"
#include "services/assets/AssetService.h"

namespace afk::systems {

/**
 * @brief PhysicsSystem
 *
 */
void physicsSystem(Registry& registry, uint32_t delta) {
  auto view = registry.view<Transform, Physics>();

  const float deltaSeconds = static_cast<float>(delta) / 1000.0f;

  for (auto [entity, tran, physics] : view.each()) {
    tran.position.x += physics.velocity.x * deltaSeconds;
    tran.position.y += physics.velocity.y * deltaSeconds;
    physics.velocity.x += physics.acceleration.x * deltaSeconds;
    physics.velocity.y += physics.acceleration.y * deltaSeconds;
  }
}

}  // namespace afk::systems
