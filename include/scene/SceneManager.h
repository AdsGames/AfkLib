#ifndef ENGINE_SCENE_MANAGER_H
#define ENGINE_SCENE_MANAGER_H

#include <allegro5/allegro.h>
#include <string>
#include <vector>

#include "Service.h"

class Scene;

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
 * @brief Manages scenes (updates)
 *
 * @author Allan Legemaate
 * @date 28/11/2020
 */
class SceneManager : public Service {
 public:
  /**
   * @brief Construct a new SceneManager object
   *
   */
  SceneManager();

  /**
   * @brief Destroy the SceneManager object
   *
   */
  virtual ~SceneManager();

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
  void notify(const ALLEGRO_EVENT& ev);

  /**
   * @brief Get the current scene
   *
   * @return pointer to current scene
   */
  Scene* getScene();

  /**
   * @brief Set the next scene to be loaded in. Upon calling, deletes this scene
   *
   * @param scene_id Id of next scene to load
   */
  void setNextScene(const std::string& scene_id);

 private:
  /**
   * @brief Check for new scene, and change it accordingly
   *
   */
  void changeScene();

  /// Current scene pointer
  Scene* current_scene = nullptr;

  /// List of scene ids
  std::vector<SceneType> scenes;

  /// Update timer
  ALLEGRO_TIMER* update_timer = nullptr;

  /// Current scene
  std::string scene_id;

  /// Next scene to load
  std::string next_scene;
};

#endif  // ENGINE_SCENE_MANAGER_H