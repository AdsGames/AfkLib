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
}

// Draw
void GameObject::draw() {}

// Add child
void GameObject::setParent(const ObjId parent_id) {
  this->parent_id = parent_id;
}

// Is colliding with game object
bool GameObject::colliding(const GameObject& other) {
  return x < other.x + other.width && y < other.y + other.width &&
         other.x < x + width && other.y < y + width;
}

// On collide can be overriden
void GameObject::onCollide(const GameObject& other) {
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
  return width;
}

// Get z index
int GameObject::getHeight() const {
  return height;
}

// Get z index
float GameObject::getX() const {
  return x;
}

// Get z index
float GameObject::getY() const {
  return y;
}

// Get z index
int GameObject::getZ() const {
  return z;
}

// Get z index
float GameObject::getAngle() const {
  return angle;
}

// Get visibility
bool GameObject::getVisible() const {
  return visible;
}

// Get enabled
bool GameObject::getEnabled() const {
  return enabled;
}

// Get hooked
bool GameObject::getHooked() const {
  return hooked;
}

}  // namespace afk
