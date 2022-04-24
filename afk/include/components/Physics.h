/**
 * @file Physics.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Physics data component
 * @version 0.1
 * @date 2022-04-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#ifndef AFK_PHYSICS_H
#define AFK_PHYSICS_H

#include "../common/Vec.h"

namespace afk {

struct Physics {
  /// X and Y velocity
  Vec2 velocity = {0.0f, 0.0f};

  /// X and Y acceleration
  Vec2 acceleration = {0.0f, 0.0f};
};

}  // namespace afk

#endif  // AFK_PHYSICS_H
