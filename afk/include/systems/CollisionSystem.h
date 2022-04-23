/**
 * @file CollisionSystem.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief System in charge of updating transforms
 * @version 0.1
 * @date 2022-04-22
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef AFK_COLLISIONSYSTEM_H
#define AFK_COLLISIONSYSTEM_H

#include "entities/Entity.h"

namespace afk::systems {

/**
 * @brief CollisionSystem
 *
 */
void collisionSystem(Registry& registry);

}  // namespace afk::systems

#endif  // AFK_COLLISIONSYSTEM_H