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
ObjId GameObject::index = 0;

// Constructor
GameObject::GameObject(const Scene& scene,
                       const float x,
                       const float y,
                       const int z)
    : scene(scene), x(x), y(y), z(z), height(0), width(0), angle(180.0f) {
  this->id = GameObject::index;
  GameObject::index += 1;
}

// Destructor
GameObject::~GameObject() {}

// Update
void GameObject::update() {}

// Draw
void GameObject::draw() {}

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

// Get unique id
ObjId GameObject::getId() const {
  return id;
}

}  // namespace afk
