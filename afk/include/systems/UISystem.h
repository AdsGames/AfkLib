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
#ifndef AFK_UISYSTEM_H
#define AFK_UISYSTEM_H

#include "entities/Entity.h"
#include "services/assets/AssetService.h"
#include "services/input/InputService.h"

namespace afk::systems {

/**
 * @brief UISystem
 *
 */
void uiSystem(Registry& registry,
              AssetService& assetService,
              InputService& inputService);

}  // namespace afk::systems

#endif  // AFK_UISYSTEM_H