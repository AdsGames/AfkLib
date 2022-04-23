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
#include "systems/UISystem.h"

#include "components/Transform.h"
#include "components/ui/Button.h"
#include "components/ui/Label.h"
#include "primitives/Primitives.h"

namespace afk::systems {

/**
 * @brief UISystem
 *
 */
void uiSystem(Registry& registry,
              AssetService& assetService,
              InputService& inputService) {
  auto viewLabels = registry.view<const Transform, Label>();
  for (auto [entity, tran, label] : viewLabels.each()) {
    auto font = assetService.getFont(label.font);
    font.draw(tran.position.x, tran.position.y, label.text);
  }

  auto viewButtons = registry.view<const Transform, Button>();
  for (auto [entity, tran, button] : viewButtons.each()) {
    // Draw button background
    primitives::rectfill(tran.position.x, tran.position.y, tran.size.x,
                         tran.size.y, color::white);

    // Draw button border
    primitives::rect(tran.position.x, tran.position.y, tran.size.x, tran.size.y,
                     color::black);

    // Draw text
    auto font = assetService.getFont(button.font);
    font.draw(tran.position.x, tran.position.y, button.text);

    if (button.onClick) {
      if (inputService.mouseDown(MouseButtons::Left)) {
        if (inputService.mouseOver(Vec2(tran.position.x, tran.position.y),
                                   Vec2(tran.size.x, tran.size.y))) {
          button.onClick();
        }
      }
    }
  }
}

}  // namespace afk::systems
