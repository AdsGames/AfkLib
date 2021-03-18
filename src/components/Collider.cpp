/**
 * @file Sprite.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of Collider component
 * @version 0.1
 * @date 2021-03-15
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "components/Collider.h"

#include "services/Services.h"

namespace afk {

// Construct component
Collider::Collider(ObjId obj_id) : Component(obj_id) {}

}  // namespace afk
