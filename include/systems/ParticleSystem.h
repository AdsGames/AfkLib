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
#ifndef AFK_PARTICLESYSTEM_H
#define AFK_PARTICLESYSTEM_H

#include <cstdint>
#include "entities/Entity.h"
#include "services/assets/AssetService.h"

namespace afk::systems {

/**
 * @brief ParticleSystem
 *
 */
void particleSystem(Registry& registry, uint32_t delta);

void particleRenderSystem(Registry& registry, AssetService& assetService);

}  // namespace afk::systems

#endif  // AFK_PARTICLESYSTEM_H