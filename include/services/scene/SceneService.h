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
#ifndef INCLUDE_SERVICES_SCENE_SCENESERVICE_H_
#define INCLUDE_SERVICES_SCENE_SCENESERVICE_H_

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
   * @param scene_id to add to engine
   */
  template <class T>
  void addScene(const std::string& scene_id) {
    scenes.push_back({scene_id, new T()});
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
   * @param scene_id Id of next scene to load
   */
  void setNextScene(const std::string& scene_id);

 private:
  /**
   * @brief Simple struct which binds scenes to scene ids
   *
   */
  struct SceneType {
    /// Id of scene
    std::string scene_id;

    /// Scene object
    Scene* scene;
  };

  /**
   * @brief Check for new scene, and change it accordingly
   *
   */
  void changeScene();

  /// Current scene pointer
  Scene* current_scene;

  /// List of scene ids
  std::vector<SceneType> scenes;

  /// Current scene
  std::string scene_id;

  /// Next scene to load
  std::string next_scene;

  /// Last tick
  Uint32 last_tick;
};

}  // namespace afk

#endif  // INCLUDE_SERVICES_SCENE_SCENESERVICE_H_
