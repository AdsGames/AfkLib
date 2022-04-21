/**
 * @file UISystem.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief System in charge of rendering components
 * @version 0.1
 * @date 2022-04-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef INCLUDE_SYSTEMS_UI_SYSTEM_H_
#define INCLUDE_SYSTEMS_UI_SYSTEM_H_

#include <entt/entt.hpp>

#include "components/Transform.h"
#include "components/ui/Label.h"
#include "services/assets/AssetService.h"

/**
 * @brief UISystem
 *
 */
namespace afk::systems {

void uiSystem(entt::registry& registry, AssetService& assetService) {
  auto view = registry.view<const Transform, LabelComponent>();

  for (auto [entity, tran, label] : view.each()) {
    auto font = assetService.getFont(label.font);
    font.draw(tran.position.x, tran.position.y, label.text);
  }
}

}  // namespace afk::systems

#endif  // INCLUDE_SYSTEMS_UI_SYSTEM_H_