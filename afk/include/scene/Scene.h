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
#ifndef AFK_SCENE_H
#define AFK_SCENE_H

#include <memory>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

#include "../common/Exceptions.h"
#include "../components/Transform.h"
#include "../entities/Entity.h"
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
  virtual ~Scene() = default;

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
  virtual void update(uint32_t delta);

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
   * @brief Internal cleanup call
   *
   */
  void stopInternal();

  /**
   * @brief Register a new entity
   *
   * @return entity
   */
  Entity createEntity();

  /**
   * @brief Remove an entity
   *
   * @param entity Entity to remove
   */
  void destroyEntity(Entity entity);

  /**
   * @brief Add a component to an entity
   *
   * @tparam T Type of component
   * @tparam Args Type of arguments to provide to component constructor
   * @param id Entity to assign to
   * @param args Arguments accepted by component
   */
  template <typename T, typename... Args>
  T& createComponent(Entity id, Args&&... args) {
    auto& component = registry.emplace<T>(id, std::forward<Args>(args)...);

    // Sort always (inefficient!)
    registry.sort<afk::Transform>([](const auto& lhs, const auto& rhs) {
      return lhs.position.z < rhs.position.z;
    });

    return component;
  }

  /**
   * @brief Add a component to an entity without args
   *
   * @tparam T Type of component
   * @param id Entity to assign to
   */
  template <typename T>
  T& createComponent(Entity id) {
    return registry.emplace<T>(id);
  }

  /**
   * @brief Get a component for a given entity
   *
   * @tparam T Type of component
   * @param id Id of entity
   * @return T& Returned component reference
   */
  template <typename T>
  T& getComponent(Entity id) {
    return registry.get<T>(id);
  }

  /**
   * @brief Get a reference to the registry
   *
   * @return registry& Registry reference
   */
  Registry& getRegistry();

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
  /// Entity registry
  Registry registry;
};
}  // namespace afk

#endif  // AFK_SCENE_H
