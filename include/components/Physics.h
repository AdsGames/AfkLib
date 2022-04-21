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
#ifndef INCLUDE_COMPONENTS_PHYSICS_H_
#define INCLUDE_COMPONENTS_PHYSICS_H_

#include "../common/Vec.h"

namespace afk {

struct Physics {
  /// Constructors
  Physics(Vec2 velocity, Vec2 acceleration)
      : velocity(velocity), acceleration(acceleration) {}

  Physics(Vec2 velocity) : velocity(velocity) {}

  Physics() {}

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

#endif  // INCLUDE_COMPONENTS_PHYSICS_H_
