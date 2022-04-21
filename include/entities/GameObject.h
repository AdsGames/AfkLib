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

#include "../components/Transform.h"
#include "../scene/Scene.h"
#include "ObjId.h"

namespace afk {

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
  Transform transform;

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

  /// Static id counter
  static ObjId index;
};

}  // namespace afk

#endif  // INCLUDE_ENTITIES_GAMEOBJECT_H_
