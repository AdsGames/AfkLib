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

#include "scene/Scene.h"

#include <algorithm>

namespace afk {

// Set incrementing index count
ObjId GameObject::index = 1;

// Constructor
GameObject::GameObject(Scene& scene, const float x, const float y, const int z)
    : id(GameObject::index),
      scene(scene),
      x(x),
      y(y),
      z(z),
      height(0),
      width(0),
      angle(0.0f),
      visible(true),
      enabled(true),
      hooked(true),
      last_x(0),
      last_y(0),
      parent_id(0) {
  GameObject::index += 1;
}

// Destructor
GameObject::~GameObject() {}

// Update
void GameObject::update(Uint32 delta) {
  (void)delta;
}

// Update
void GameObject::updateInternal() {
  // Update delta position
  last_x = x;
  last_y = y;

  // Parent functions
  if (parent_id != 0) {
    // Autoremove if parent is dead
    try {
      auto& parent = scene.get<GameObject>(parent_id);

      // Set hooked state
      hooked = parent.getHooked();

      // Set position
      x += parent.x - parent.last_x;
      y += parent.y - parent.last_y;

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
bool GameObject::isColliding(const GameObject& other) {
  return x < other.x + other.width && x + width > other.x &&
         y < other.y + other.height && y + height > other.y;
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

// Set the size of game object in pixels
void GameObject::setSize(const unsigned int width, const unsigned int height) {
  this->width = width;
  this->height = height;
}

// Set the position of game object in pixels
void GameObject::setPosition(const float x, const float y) {
  this->x = x;
  this->y = y;
}

// Set angle of game object in degrees
void GameObject::setAngle(const float angle) {
  this->angle = angle;
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

// Get z index
int GameObject::getWidth() const {
  return this->width;
}

// Get z index
int GameObject::getHeight() const {
  return this->height;
}

// Get z index
float GameObject::getX() const {
  return this->x;
}

// Get z index
float GameObject::getY() const {
  return this->y;
}

// Get z index
int GameObject::getZ() const {
  return this->z;
}

// Get z index
float GameObject::getAngle() const {
  return this->angle;
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
