/**
 * @file GameObject.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief A general purpose game object, generally absctracted in sub classes.
 * @see Sprite
 * @see Button
 * @version 0.1
 * @date 2017-01-03
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_ENTITIES_GAMEOBJECT_H_
#define INCLUDE_ENTITIES_GAMEOBJECT_H_

#include <SDL2/SDL.h>
#include <vector>

#include "../components/Component.h"
#include "../components/Transform.h"

/// Unique id type alias
using ObjId = Uint32;

namespace afk {

// Forward declare scene class
class Scene;

/**
 * @brief A collidable object! Parent class for many others
 *
 */
class GameObject {
 public:
  /**
   * @brief Construct a new GameObject
   *
   * @param scene Reference to scene which is stored in game object
   * @param x X position
   * @param y Y position
   * @param z Z position (for sorting)
   */
  explicit GameObject(Scene& scene,
                      const float x = 0.0f,
                      const float y = 0.0f,
                      const int z = 0);

  /**
   * @brief Destroy the GameObject
   *
   */
  virtual ~GameObject();

  /**
   * @brief Update loop to be overriden by derived classes. Automatically called
   * by Scene.
   *
   * @param delta Time since last call in ms
   */
  virtual void update(Uint32 delta);

  /**
   * @brief Internal game object management
   *
   */
  void updateInternal();

  /**
   * @brief Draw loop to be overriden by derived classes. Automatically called
   * by Scene.
   *
   * Do not add other game objects in the draw loop! This will cause undefined
   * behaviour.
   *
   */
  virtual void draw();

  /**
   * @brief Set gameobject parent
   *
   * @param parent_id
   */
  void setParent(const ObjId parent_id);

  /**
   * @brief Add a collider with a game object
   *
   */
  void addCollider(const ObjId obj_id);

  /**
   * @brief Remove a collider with a game object
   *
   */
  void removeCollider(const ObjId obj_id);

  /**
   * @brief Checks collision between this game object and another.
   *
   * @param other Some other game object
   * @return True on collision, else false
   */
  bool isColliding(GameObject& other);

  /**
   * @brief Checks collision between this game object and another.
   * Calls on collide on both objects if there is a collision
   *
   * @param other Some other game object
   * @return True on collision, else false
   */
  bool collide(GameObject& other);

  /**
   * @brief Callback which is triggered on collision with another game object if
   * registered with the Scene.
   *
   * @param other The game object which is being collided with.
   */
  virtual void onCollide(GameObject& other);

  /**
   * @brief Set the visibility of the GameObject. Will not draw when not
   * visible.
   *
   * @param visible Visibility to set to
   */
  void setVisible(const bool visible);

  /**
   * @brief Set the enabled of the GameObject. Will not update when not enabled.
   *
   * @param enabled Enabled to set to
   */
  void setEnabled(const bool enabled);

  /**
   * @brief Set hooked state. This removes the GameObject from the draw and
   * update loop as well as its children.
   *
   * @param hooked Enabled to set to
   */
  void setHooked(const bool hooked);

  /**
   * @brief Get the visibility of game object
   *
   * @return true If visible
   * @return false If not visible
   */
  bool getVisible() const;

  /**
   * @brief Check if enabled
   *
   * @return true If enabled
   * @return false If not enabled
   */
  bool getEnabled() const;

  /**
   * @brief Check if enabled
   *
   * @return true If enabled
   * @return false If not enabled
   */
  bool getHooked() const;

  /// Components
  Transform& transform;

  /// Autoassigned unique id
  const ObjId id;

 protected:
  /// Reference to registered scene
  Scene& scene;

  /// Visibility
  bool visible;

  /// Enabled
  bool enabled;

  /// Hooked
  bool hooked;

 private:
  /// Parent Id
  ObjId parent_id;

  /// Colliders
  std::vector<ObjId> colliders;

  /// Static id counter
  static ObjId index;
};

}  // namespace afk

#endif  // INCLUDE_ENTITIES_GAMEOBJECT_H_
