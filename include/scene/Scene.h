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

#include <entt/entt.hpp>
#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../common/Exceptions.h"
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
   * @brief Register a new entity
   *
   * @return entt::entity
   */
  entt::entity createEntity() { return registry.create(); }

  /**
   * @brief Remove an entity
   *
   * @param entity Entity to remove
   */
  void destroyEntity(entt::entity entity) { registry.destroy(entity); }

  /**
   * @brief Add a component to an entity
   *
   * @tparam T Type of component
   * @tparam Args Type of arguments to provide to component constructor
   * @param id Entity to assign to
   * @param args Arguments accepted by component
   */
  template <typename T, typename... Args>
  T& createComponent(entt::entity id, Args&&... args) {
    return registry.emplace<T>(id, std::forward<Args>(args)...);
  }

  /**
   * @brief Get a component for a given entity
   *
   * @tparam T Type of component
   * @param id Id of entity
   * @return T& Returned component reference
   */
  template <typename T>
  T& getComponent(entt::entity id) {
    return registry.get<T>(id);
  }

  /**
   * @brief Get a reference to the registry
   *
   * @return entt::registry& Registry reference
   */
  entt::registry& getRegistry() { return registry; }

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
  /// Needs sorting
  bool need_sort;

  /// Entity registry
  entt::registry registry;
};
}  // namespace afk

#endif  // INCLUDE_SCENE_SCENE_H_
