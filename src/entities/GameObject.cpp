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

#include "scene/Scene.h"

namespace afk {

// Set incrementing index count
ObjId GameObject::index = 1;

// Constructor
GameObject::GameObject(Scene& scene, const float x, const float y, const int z)
    : transform(scene.addComponent<Transform>(GameObject::index)),
      id(GameObject::index),
      scene(scene),
      visible(true),
      enabled(true),
      hooked(true),
      parent_id(0) {
  GameObject::index += 1;

  // Set transform
  transform.x = x;
  transform.y = y;
  transform.z = z;
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
  if (parent_id != 0) {
    // Autoremove if parent is dead
    try {
      auto& parent = scene.get<GameObject>(parent_id);

      // Set hooked state
      hooked = parent.getHooked();

      // Set position
      transform.x += parent.transform.x - parent.transform.last_x;
      transform.y += parent.transform.y - parent.transform.last_y;
    } catch (const KeyLookupException&) {
      scene.remove(id);
    }
  }

  // Colliders
  std::remove_if(colliders.begin(), colliders.end(),
                 [&](const auto& obj_id) { return !scene.has(obj_id); });
  for (auto& obj_id : colliders) {
    collide(scene.get(obj_id));
  }
}

// Draw
void GameObject::draw() {}

// Add child
void GameObject::setParent(const ObjId parent_id) {
  this->parent_id = parent_id;
}

// Add a collider with a game object
void GameObject::addCollider(const ObjId obj_id) {
  colliders.push_back(obj_id);
}

// Remove a collider with a game object
void GameObject::removeCollider(const ObjId obj_id) {
  auto it = std::find(colliders.begin(), colliders.end(), obj_id);
  if (it != colliders.end()) {
    colliders.erase(it);
  }
}

// Is colliding with game object
bool GameObject::isColliding(GameObject& other) {
  return transform.x < other.transform.x + other.transform.width &&
         transform.x + transform.width > other.transform.x &&
         transform.y < other.transform.y + other.transform.height &&
         transform.y + transform.height > other.transform.y;
}

// Collide game objects
bool GameObject::collide(GameObject& other) {
  bool colliding = isColliding(other);

  if (colliding) {
    this->onCollide(other);
    other.onCollide(*this);
  }

  return colliding;
}

// On collide can be overriden
void GameObject::onCollide(GameObject& other) {
  (void)(other);
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
