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
#ifndef AFK_PHYSICSSYSTEM_H
#define AFK_PHYSICSSYSTEM_H

#include "entities/Entity.h"

namespace afk::systems {

/**
 * @brief PhysicsSystem
 *
 */
void physicsSystem(Registry& registry, uint32_t delta);

}  // namespace afk::systems

#endif  // AFK_PHYSICSSYSTEM_H