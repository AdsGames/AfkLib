/**
 * @file Scene.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Parent scene class. Children can be added to scene manager.
 * @version 0.1
 * @date 2016-12-30
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_SCENE_SCENE_H_
#define INCLUDE_SCENE_SCENE_H_

#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "../common/Exceptions.h"
#include "../entities/GameObject.h"
#include "../services/Services.h"

/**
 * @brief Scene for state machine
 *
 */
namespace afk {
class Scene {
 public:
  /**
   * @brief Create a new Scene
   *
   */
  Scene();

  /**
   * @brief Destroy the Scene
   *
   */
  virtual ~Scene() {}

  /**
   * @brief Start the scene
   *
   */
  virtual void start(){};

  /**
   * @brief Update to be overridden by derived scenes
   *
   * @param delta Time since last call in ms
   *
   */
  virtual void update(Uint32 delta);

  /**
   * @brief Draw to be overridden by derived scenes
   *
   */
  virtual void draw();

  /**
   * @brief Stop the scene
   *
   */
  virtual void stop(){};

  /**
   * @brief Internall cleanup call
   *
   */
  void stopInternal();

  /**
   * @brief Add game object to update and draw pool
   *
   * @tparam T Type of game object
   * @tparam Args Arguments to forward to T
   * @param args Argument values which will be forwarded to T when constructing
   * a new game object
   * @return Unique id of created object
   */
  template <typename T, typename... Args>
  ObjId add(Args&&... args) {
    T* obj = new T(std::forward<Args>(args)...);
    update_pool.emplace_back(obj);
    sortGameObjects();
    return obj->id;
  }

  /**
   * @brief Add game object to update and draw pool, returns by reference
   *
   * @tparam T Type of game object
   * @tparam Args Arguments to forward to T
   * @param args Argument values which will be forwarded to T when constructing
   * a new game object
   * @return Reference to created game object
   */
  template <typename T, typename... Args>
  T& addObj(Args&&... args) {
    T* obj = new T(std::forward<Args>(args)...);
    update_pool.emplace_back(obj);
    sortGameObjects();
    return get<T>(obj->id);
  }

  /**
   * @brief Removes a game object from the scene pool
   *
   * @param id Id of object to remove
   */
  void remove(const ObjId id);

  /**
   * @brief Gets a game object by id and casts to type T
   *
   * @tparam T Type of game object
   * @param id Id of game object to look up
   * @return Reference to game object if found
   * @throws KeyLookupException if game object could not be found
   */
  template <class T>
  T& get(const ObjId id) {
    try {
      unsigned int index = lookup_map[id];
      return dynamic_cast<T&>(*update_pool.at(index));
    } catch (...) {
      throw KeyLookupException("Could not find entity by id " +
                               std::to_string(id));
    }
  }

  /**
   * @brief Register collider between two game objects
   *
   * @param obj1 Game object 1
   * @param obj2 Game object 2
   */
  void addCollider(const ObjId obj1, const ObjId obj2);

  /// Service references
  AudioService& audio;
  LoggingService& logger;
  DisplayService& display;
  AssetService& assets;
  InputService& input;
  SceneService& scene;
  ConfigService& config;

 private:
  /**
   * @brief Sort game object by Z index
   *
   */
  void sortGameObjects();

  /// Holds game objects
  std::vector<std::unique_ptr<GameObject>> update_pool;

  /// Quick gameobject lookup
  std::map<ObjId, unsigned int> lookup_map;

  /// Quick collider lookup
  std::map<ObjId, std::vector<ObjId>> collider_map;
};
}  // namespace afk

#endif  // INCLUDE_SCENE_SCENE_H_
