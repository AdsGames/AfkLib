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
#ifndef AFK_RENDERSYSTEM_H
#define AFK_RENDERSYSTEM_H

#include "../../lib/entt/src/entt/entt.hpp"

#include "entities/Entity.h"
#include "services/assets/AssetService.h"

namespace afk::systems {

/**
 * @brief RenderSystem
 *
 */
void renderSystem(Registry& registry, AssetService& assetService);

}  // namespace afk::systems

#endif  // AFK_RENDERSYSTEM_H