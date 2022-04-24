/**
 * @file Entity.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Entity identifier alias
 * @version 0.1
 * @date 2022-04-22
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef AFK_ENTITY_H
#define AFK_ENTITY_H

#include "../../lib/entt/src/entt/entt.hpp"

namespace afk {

using Entity = entt::entity;
using Registry = entt::registry;

}  // namespace afk

#endif  // AFK_ENTITY_H
