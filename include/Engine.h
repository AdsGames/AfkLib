#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include <allegro5/allegro5.h>
#include <string>
#include <vector>

#include "scene/Scene.h"

/// Struct containing scene id and scene type
struct SceneType {
  std::string scene_id;
  Scene* scene;
};

/**
 * @brief Core engine class, manages scenes and sets up locator and allegro
 *
 * @author Allan Legemaate
 * @date 7/11/2020
 */
class Engine {
 public:
  /**
   * @brief Construct a new Engine object
   *
   */
  Engine();

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
   * @brief Starts the main game loop
   *
   * @param scene_id Initial scene to start with
   */
  void start(const std::string& scene_id);

 private:
  /**
   * @brief Check for new scene, and change it accordingly
   *
   */
  void changeScene();

  /**
   * @brief Sets up core engine features and allegro 5
   *
   */
  void setup();

  /**
   * @brief Update scenes, and event queue checks
   *
   */
  void update();

  /// Main event queue
  ALLEGRO_EVENT_QUEUE* event_queue = nullptr;

  /// Main timer
  ALLEGRO_TIMER* timer = nullptr;

  /// Set to true on close from escape or x button
  bool closing = false;

  /// Current scene pointer
  Scene* current_scene = nullptr;

  /// List of scene ids
  std::vector<SceneType> scenes;
};

#endif  // ENGINE_ENGINE_H