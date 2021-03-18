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

#include <memory>
#include <string>
#include <unordered_map>
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

using ComponentArray = std::vector<std::unique_ptr<Component>>;
using ComponentMap = std::unordered_map<ObjId, unsigned int>;

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
   * @brief Add GameObject to update and draw pool, returns by reference
   *
   * @tparam T Type of GameObject
   * @tparam Args Arguments to forward to T
   * @param args Argument values which will be forwarded to T when constructing
   * a new GameObject
   * @return Reference to created GameObject
   */
  template <typename T, typename... Args>
  T& add(Args&&... args) {
    // Create the GameObject
    GameObject* obj = new T(std::forward<Args>(args)...);

    // Add to lookup
    entity_map[obj->id] = entities.size();

    // Push
    entities.emplace_back(obj);

    // Force sort on next update
    need_sort = true;

    // Return the object!
    return get<T>(obj->id);
  }

  /**
   * @brief Gets a GameObject by id and casts to type T
   *
   * @tparam T Type of GameObject
   * @param id ObjId of GameObject to look up
   * @return Reference to GameObject if found
   * @throws KeyLookupException if GameObject could not be found
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
   * @brief Gets a GameObject by id without the cast
   *
   * @param id ObjId of GameObject to look up
   * @return Reference to GameObject if found
   * @throws KeyLookupException if GameObject could not be found
   */
  GameObject& get(const ObjId id) {
    if (!has(id)) {
      throw KeyLookupException("Could not find entity by id " +
                               std::to_string(id));
    }

    unsigned int index = entity_map[id];
    return *entities.at(index);
  }

  /**
   * @brief Removes a GameObject from the scene pool
   *
   * @param id ObjId of GameObject to remove
   */
  void remove(const ObjId id);

  /**
   * @brief Check if GameObject id exists in scene
   *
   * @param id ObjId to check
   * @return true If the GameObject exists
   * @return false If the GameObject does not exist
   */
  bool has(const ObjId id);

  /**
   * @brief Add a component to the scene, linked to a GameObject by obj_id
   *
   * @tparam T Subclass of component
   * @param obj_id ObjId of GameObject to attach to
   * @return T& Reference to the component
   */
  template <typename T>
  T& addComponent(const ObjId obj_id) {
    // Get type code
    std::size_t id = typeid(T).hash_code();

    // Add to component map
    component_map[id][obj_id] = components[id].size();

    // Add component to vector
    components[id].emplace_back(new T(obj_id));

    // Get the component
    return getComponent<T>(obj_id);
  }

  /**
   * @brief Get the Component object
   *
   * @tparam T Subclass of component
   * @param obj_id ObjId of GameObject to search for component
   * @return T& Reference to the component
   */
  template <typename T>
  T& getComponent(const ObjId obj_id) {
    // Get type code
    const std::size_t id = typeid(T).hash_code();

    // Find index in component map
    unsigned int index = component_map[id][obj_id];

    // Cast and return
    return dynamic_cast<T&>(*components[id].at(index));
  }

  /**
   * @brief Remove a component from an object
   *
   * @tparam T Type of component
   * @param obj_id ObjId of GameObject to remove component from
   */
  template <typename T>
  void removeComponent(const ObjId obj_id) {
    // Get type code
    const std::size_t id = typeid(T).hash_code();

    // Remove by id
    removeComponentById(obj_id, id);
  }

  /**
   * @brief Check if a GameObject has a component attached
   *
   * @tparam T Type of component
   * @param obj_id ObjId of GameObject to check
   */
  template <typename T>
  bool hasComponent(const ObjId obj_id) const {
    // Get type code
    std::size_t id = typeid(T).hash_code();

    // Check count of id for type
    return component_map.at(id).count(obj_id) != 0;
  }

  /// Audio service reference
  AudioService& audio;

  /// Logger service reference
  LoggingService& logger;

  /// Display service reference
  DisplayService& display;

  /// Asset service reference
  AssetService& assets;

  /// Input service reference
  InputService& input;

  /// Scene service reference
  SceneService& scene;

  /// Config service reference
  ConfigService& config;

 private:
  /// Remove component by type id
  void removeComponentById(const ObjId obj_id, const std::size_t id);

  /// Holds GameObjects
  std::vector<std::unique_ptr<GameObject>> entities;

  /// Quick GameObjects lookup
  std::unordered_map<ObjId, unsigned int> entity_map;

  /// Hold GameObject Components
  std::unordered_map<std::size_t, ComponentArray> components;

  /// Quick lookup of GameObject Components
  std::unordered_map<std::size_t, ComponentMap> component_map;

  /// Store objects to be removed
  std::vector<ObjId> remove_pool;

  /// Needs sorting
  bool need_sort;
};
}  // namespace afk

#endif  // INCLUDE_SCENE_SCENE_H_
