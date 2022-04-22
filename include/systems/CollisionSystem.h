/**
 * @file CollisionSystem.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief System in charge of updating transforms
 * @version 0.1
 * @date 2022-04-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef INCLUDE_SYSTEMS_COLLISION_SYSTEM_H_
#define INCLUDE_SYSTEMS_COLLISION_SYSTEM_H_

#include <entt/entt.hpp>

#include "components/Collider.h"
#include "components/Transform.h"
#include "services/assets/AssetService.h"

namespace afk::systems {

/**
 * @brief CollisionSystem
 *
 */
void collisionSystem(entt::registry& registry) {
  auto view = registry.view<const Transform, Collider>();

  for (auto [entity, tran, collider] : view.each()) {
    // Reset state
    collider.colliding = false;

    for (auto [entity_other, tran_other, collider_other] : view.each()) {
      // Check if is entity
      if (entity == entity_other) {
        continue;
      }

      // Check if colliding
      if (tran.position.x > tran_other.position.x + tran_other.size.x ||
          tran.position.x + tran.size.x < tran_other.position.x ||
          tran.position.y > tran_other.position.y + tran_other.size.y ||
          tran.position.y + tran.size.y < tran_other.position.y) {
        continue;
      }

      collider.colliding = true;
    }
  }
}

}  // namespace afk::systems

#endif  // INCLUDE_SYSTEMS_COLLISION_SYSTEM_H_