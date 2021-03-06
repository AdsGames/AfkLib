#ifndef SERVICES_SCENE_SCENE_SERVICE_H
#define SERVICES_SCENE_SCENE_SERVICE_H

#include <SDL2/SDL_timer.h>
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
class SceneService : public Service {
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
   * @brief Get the name of service
   *
   * @return name
   */
  std::string getName() const;

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
   * @brief Notify about changes in queue
   *
   * @param ev event to be processed
   */
  void notify(const SDL_Event& ev);

  /**
   * @brief Get the current scene
   *
   * @return pointer to current scene
   */
  afk::Scene* getSceneService();

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
    afk::Scene* scene;
  };

  /**
   * @brief Check for new scene, and change it accordingly
   *
   */
  void changeScene();

  /// Current scene pointer
  afk::Scene* current_scene = nullptr;

  /// List of scene ids
  std::vector<SceneType> scenes;

  /// Current scene
  std::string scene_id;

  /// Next scene to load
  std::string next_scene;

  /// Timer id
  SDL_TimerID update_timer = 0;
};

}  // namespace afk

#endif  // SERVICES_SCENE_SCENE_SERVICE_H