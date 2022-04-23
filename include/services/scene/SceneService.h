/**
 * @file SceneService.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Service in charge of managing scenes
 * @version 0.1
 * @date 2020-11-28
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef AFK_SCENESERVICE_H
#define AFK_SCENESERVICE_H

#include <string>
#include <vector>

#include "../Service.h"

namespace afk {

// Forward declare scene
class Scene;

/**
 * @brief Manages scenes (updates)
 */
class SceneService {
 public:
  /**
   * @brief Construct a new SceneService object
   *
   */
  SceneService();

  /**
   * @brief Destroy the SceneService object
   *
   */
  virtual ~SceneService();

  /**
   * @brief Add scene to engine
   *
   * @param sceneId to add to engine
   */
  template <class T>
  void addScene(const std::string& sceneId) {
    scenes.push_back({sceneId, new T()});
  }

  /**
   * @brief Update state
   */
  void update();

  /**
   * @brief Draw state
   */
  void draw();

  /**
   * @brief Get the current scene
   *
   * @return pointer to current scene
   */
  Scene* getSceneService();

  /**
   * @brief Set the next scene to be loaded in. Upon calling, deletes current
   * scene
   *
   * @param sceneId Id of next scene to load
   */
  void setNextScene(const std::string& sceneId);

 private:
  /**
   * @brief Simple struct which binds scenes to scene ids
   *
   */
  struct SceneType {
    /// Id of scene
    std::string sceneId;

    /// Scene object
    Scene* scene;
  };

  /**
   * @brief Check for new scene, and change it accordingly
   *
   */
  void changeScene();

  /// Current scene pointer
  Scene* currentScene;

  /// List of scene ids
  std::vector<SceneType> scenes;

  /// Current scene
  std::string sceneId;

  /// Next scene to load
  std::string nextScene;

  /// Last tick
  uint32_t lastTick;
};

}  // namespace afk

#endif  // AFK_SCENESERVICE_H
