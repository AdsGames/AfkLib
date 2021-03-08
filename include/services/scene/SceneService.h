#ifndef SERVICES_SCENE_SCENE_SERVICE_H
#define SERVICES_SCENE_SCENE_SERVICE_H

#include <string>
#include <vector>

#include "../Service.h"

namespace afk {

class Scene;

/**
 * @brief Manages scenes (updates)
 *
 * @author Allan Legemaate
 * @date 28/11/2020
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
  Scene* current_scene = nullptr;

  /// List of scene ids
  std::vector<SceneType> scenes;

  /// Current scene
  std::string scene_id;

  /// Next scene to load
  std::string next_scene;
};

}  // namespace afk

#endif  // SERVICES_SCENE_SCENE_SERVICE_H