/**
 * @file RenderSystem.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief System in charge of rendering components
 * @version 0.1
 * @date 2022-04-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef INCLUDE_SYSTEMS_RENDER_SYSTEM_H_
#define INCLUDE_SYSTEMS_RENDER_SYSTEM_H_

#include <entt/entt.hpp>

#include "components/Sprite.h"
#include "components/Transform.h"
#include "services/assets/AssetService.h"

namespace afk::systems {

/**
 * @brief RenderSystem
 *
 */
void renderSystem(entt::registry& registry, AssetService& assetService) {
  auto view = registry.view<const Transform, Sprite>();

  for (auto [entity, tran, sprite] : view.each()) {
    auto texture = assetService.getImage(sprite.texture);
    texture.drawEx(tran.position.x, tran.position.y, tran.size.x, tran.size.y,
                   tran.angle);
  }
}

}  // namespace afk::systems

#endif  // INCLUDE_SYSTEMS_RENDER_SYSTEM_H_