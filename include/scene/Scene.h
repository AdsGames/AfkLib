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
   * @brief Add game object to update and draw pool, returns by reference
   *
   * @tparam T Type of game object
   * @tparam Args Arguments to forward to T
   * @param args Argument values which will be forwarded to T when constructing
   * a new game object
   * @return Reference to created game object
   */
  template <typename T, typename... Args>
  T& add(Args&&... args) {
    // Create the game object
    GameObject* obj = new T(std::forward<Args>(args)...);

    // Add to lookup
    lookup_map[obj->id] = update_pool.size();

    // Push
    update_pool.emplace_back(obj);

    // Force sort on next update
    need_sort = true;

    // Return the object!
    return get<T>(obj->id);
  }

  /**
   * @brief Removes a game object from the scene pool
   *
   * @param id Id of object to remove
   */
  void remove(const ObjId id);

  /**
   * @brief Check if obj id exists in scene
   *
   * @param id Object id to check
   * @return true If the object exists
   * @return false If the object does not exist
   */
  bool has(const ObjId id);

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
    GameObject& obj = get(id);
    try {
      return dynamic_cast<T&>(obj);
    } catch (...) {
      throw KeyLookupException("Could not cast entity " + std::to_string(id) +
                               " to type");
    }
  }

  /**
   * @brief Gets a game object by id without the cast
   *
   * @param id Id of game object to look up
   * @return Reference to game object if found
   * @throws KeyLookupException if game object could not be found
   */
  GameObject& get(const ObjId id) {
    if (!has(id)) {
      throw KeyLookupException("Could not find entity by id " +
                               std::to_string(id));
    }

    unsigned int index = lookup_map[id];
    return *update_pool.at(index);
  }

  /// Service references
  AudioService& audio;
  LoggingService& logger;
  DisplayService& display;
  AssetService& assets;
  InputService& input;
  SceneService& scene;
  ConfigService& config;

 private:
  /// Holds game objects
  std::vector<std::unique_ptr<GameObject>> update_pool;

  /// Quick gameobject lookup
  std::map<ObjId, unsigned int> lookup_map;

  /// Store objects to be removed
  std::vector<ObjId> remove_pool;

  /// Needs sorting
  bool need_sort;
};
}  // namespace afk

#endif  // INCLUDE_SCENE_SCENE_H_
