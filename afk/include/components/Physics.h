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
  /// Constructors
  Physics() = default;

  Physics(Vec2 velocity, Vec2 acceleration)
      : velocity(velocity), acceleration(acceleration) {}

  explicit Physics(Vec2 velocity) : velocity(velocity) {}

  void setVelocity(Vec2 velocity) { this->velocity = velocity; }

  void setVelocity(float x, float y) { this->velocity = Vec2(x, y); }

  void setAcceleration(Vec2 acceleration) { this->acceleration = acceleration; }

  void setAcceleration(float x, float y) { this->acceleration = Vec2(x, y); }

  /// X and Y velocity
  Vec2 velocity;

  /// X and Y acceleration
  Vec2 acceleration;
};

}  // namespace afk

#endif  // AFK_PHYSICS_H
