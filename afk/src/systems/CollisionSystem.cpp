/**
 * @file CollisionSystem.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of CollisionSystem
 * @version 0.1
 * @date 2022-04-22
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "systems/CollisionSystem.h"

#include "components/Collider.h"
#include "components/Transform.h"

namespace afk::systems {

void collisionSystem(Registry& registry) {
  auto view = registry.view<const Transform, Collider>();

  for (auto [entity, tran, collider] : view.each()) {
    // Reset state
    collider.colliding = false;

    for (auto [entityOther, tranOther, colliderOther] : view.each()) {
      // Check if is entity
      if (entity == entityOther) {
        continue;
      }

      // Check if colliding
      if (tran.position.x > tranOther.position.x + tranOther.size.x ||
          tran.position.x + tran.size.x < tranOther.position.x ||
          tran.position.y > tranOther.position.y + tranOther.size.y ||
          tran.position.y + tran.size.y < tranOther.position.y) {
        continue;
      }

      collider.colliding = true;
    }
  }
}

}  // namespace afk::system