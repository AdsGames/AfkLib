/**
 * @file GameObject.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of GameObject class
 * @version 0.1
 * @date 2017-01-03
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "entities/GameObject.h"

#include <algorithm>

namespace afk {

// Set incrementing index count
ObjId GameObject::index = 1;

// Constructor
GameObject::GameObject(Scene& scene, const float x, const float y, const int z)
    : id(GameObject::index),
      scene(scene),
      visible(true),
      enabled(true),
      hooked(true),
      parent_id(0) {
  GameObject::index += 1;

  // Set transform
  transform.position.x = x;
  transform.position.y = y;
  transform.position.z = z;
}

// Destructor, remove components
GameObject::~GameObject() {}

// Update
void GameObject::update(Uint32 delta) {
  (void)delta;
}

// Update
void GameObject::updateInternal() {
  // Parent functions
  // if (parent_id != 0) {
  //   // Autoremove if parent is dead
  //   try {
  //     auto& parent = scene.getComponent<GameObject>(parent_id);

  //     // Set hooked state
  //     hooked = parent.getHooked();

  //     // Set position
  //     transform.position.x += parent.transform.position.x -
  //     parent.transform.last_x; transform.position.y +=
  //     parent.transform.position.y - parent.transform.last_y;
  //   } catch (const KeyLookupException&) {
  //     // scene.remove(id);
  //   }
  // }
}

// Draw
void GameObject::draw() {}

// Add child
void GameObject::setParent(const ObjId parent_id) {
  this->parent_id = parent_id;
}

// Set visibility
void GameObject::setVisible(const bool visible) {
  this->visible = visible;
}

// Set enabled
void GameObject::setEnabled(const bool enabled) {
  this->enabled = enabled;
}

// Set hooked
void GameObject::setHooked(const bool hooked) {
  this->hooked = hooked;
}

// Get visibility
bool GameObject::getVisible() const {
  return this->visible;
}

// Get enabled
bool GameObject::getEnabled() const {
  return this->enabled;
}

// Get hooked
bool GameObject::getHooked() const {
  return this->hooked;
}

}  // namespace afk
